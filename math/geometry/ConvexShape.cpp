#include "ConvexShape.h"

#include <iostream>
#include <math.h>

#include "Simplex.h"
#include "RaycastSupport.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        ConvexShape::ConvexShape(int amount, Vector3* positions)
        {
          this->amount = amount;
          this->positions = new Vector3[amount];
          radius = 0;
          for(int i=0;i<amount;i++)
          {
            *(this->positions + i) = *(positions + i);
            float length = (*(positions + i)).getLength();
            if(length > radius)
            {
              radius = length;
            }
          }
        }

        ConvexShape::~ConvexShape()
        {
          delete [] positions;
        }

        ConvexShape::ConvexShape(const ConvexShape& shape)
        {
          amount = shape.amount;
          radius = shape.radius;
          positions = new Vector3[amount];
          for(int i=0;i<amount;i++)
          {
            *(positions + i) = *(shape.positions + i);
          }
        }

        ConvexShape& ConvexShape::operator=(const ConvexShape& shape)
        {
          delete [] positions;
          amount = shape.amount;
          radius = shape.radius;
          positions = new Vector3[amount];
          for(int i=0;i<amount;i++)
          {
            *(positions + i) = *(shape.positions + i);
          }
          return *this;
        }

        float ConvexShape::getRadius() const
        {
          return radius;
        }

        Vector3 ConvexShape::support(const Vector3& v) const
        {
          Vector3 res = *positions;
          float rdot = res.dot(v);
          for(int i=1;i<amount;i++)
          {
            float dot = (*(positions + i)).dot(v);
            if(dot > rdot)
            {
              rdot = dot;
              res = *(positions + i);
            }
          }
          return res;
        }

        bool ConvexShape::isColliding(float timePassed, const Matrix4x4& t1, const Matrix4x4& invRS1, float rotationSpeed1, const ConvexShape& shape, const Matrix4x4& t2, const Matrix4x4& invRS2, float rotationSpeed2)
        {
          /*
          float angleCoef = M_PI/180.0;
          float rotationRadius1 = 2*getRadius()*abs(sin((rotationSpeed1*timePassed*angleCoef)/2));
          float rotationRadius2 = 2*shape.getRadius()*abs(sin((rotationSpeed2*timePassed*angleCoef)/2));

          Vector3 rcpoint(0,0,0);
          Simplex simplex;
          simplex.add(RaycastSupport(&rcpoint, support(Vector3(1,0,0), t1, invRS1, rotationRadius1, shape, t2, invRS2, rotationRadius2)));
          Vector3 direction = simplex.getToZero();

          int i =0;
          while(true)
          {
            RaycastSupport rs(&rcpoint, support(-direction, t1, invRS1, rotationRadius1, shape, t2, invRS2, rotationRadius2));
            if(rs.getMdPosition().dot(direction) < 0.0)
            {
              return false;
            }
            simplex.add(rs);
            direction = simplex.getToZero();
            if(direction.dot(direction) < 0.000001)
            {
              return true;
            }
            i++;
            if(i > 15)
            {
              std::cout << "INF LOOP" << std::endl;
              return true;
            }
          }
          */
          return false;
        }

        Vector3 ConvexShape::getDistance(Vector3* rcpoint, const Matrix4x4& t1, const Matrix4x4& invRS1, float rotation1, const ConvexShape& shape, const Matrix4x4& t2, const Matrix4x4& invRS2, float rotation2)
        {
          float angleCoef = M_PI/180.0;
          float rotationRadius1 = 2.0*getRadius()*abs(sin((rotation1*angleCoef)/2.0));
          float rotationRadius2 = 2.0*shape.getRadius()*abs(sin((rotation2*angleCoef)/2.0));

          Vector3 v = RaycastSupport(rcpoint, SupportVertex(support(Vector3(1,0,0), t1, invRS1, rotationRadius1, shape, t2, invRS2, rotationRadius2))).getMdPosition();
          Simplex simplex;
          RaycastSupport w = RaycastSupport(rcpoint, SupportVertex(support(v, t1, invRS1, rotationRadius1, shape, t2, invRS2, rotationRadius2)));
          int i = 0;
          while(v.dot(v) - v.dot(w.getMdPosition()) > 0.000001)
          {
            simplex.add(w);
            v = simplex.getNearZero();
            w = RaycastSupport(rcpoint, SupportVertex(support(v, t1, invRS1, rotationRadius1, shape, t2, invRS2, rotationRadius2)));
            i++;
            if(i > 15)
            {
              std::cout << "INF LOOP DIST" << std::endl;
              break;
            }
          }

          std::cout << "DISTANCE: " << v.getLength() << " value: " << v.dot(v) - v.dot(w.getMdPosition()) << std::endl;
          return v;
        }

        void ConvexShape::getCAHitParameters(const Vector3& direction, float timePassed, const Matrix4x4& t1, const Matrix4x4& invRS1, float rotation1, const ConvexShape& shape, const Matrix4x4& t2, const Matrix4x4& invRS2, float rotation2, bool* collision, float* hp, Vector3* normal)
        {
          *hp = 0.0;
          Vector3 rcpoint(0.0, 0.0, 0.0);
          *normal = Vector3(0.0, 0.0, 0.0);
          Vector3 v = getDistance(&rcpoint, t1, invRS1, rotation1*timePassed, shape, t2, invRS2, rotation2*timePassed);

          int i = 0;
          while(v.dot(v) > 0.000001)
          {
            float vr = v.dot(direction);
            if(vr >= 0.0)
            {
              *collision = false;
              return;
            }
            else
            {
              if(vr < -0.000001)
              {
                *hp = *hp - v.dot(v)/vr;
                rcpoint = (*hp)*direction;
                *normal = v;
              }
              v = getDistance(&rcpoint, t1, invRS1, rotation1*timePassed, shape, t2, invRS2, rotation2*timePassed);
            }

            i++;
            if(i > 30)
            {
              break;
              std::cout << "ERROR CA INF LOOP!" << std::endl;
            }
          }
          normal->normalize();

          float newHp = *hp;

          float nr = normal->dot(direction);

          if(nr < -0.000001)
          {
            newHp = *hp + 0.01/nr;
          }

          if(newHp > 0.0)
          {
            *hp = newHp;
          }
          else
          {
            *hp = 0.0;
          }

          *collision = true;
        }

        SupportVertex ConvexShape::support(const Vector3& v, const Matrix4x4& t1, const Matrix4x4& invRS1, float rotationRadius1, const ConvexShape& shape, const Matrix4x4& t2, const Matrix4x4& invRS2, float rotationRadius2)
        {
          Vector3 direction = v;
          direction.normalize();
          return SupportVertex(t1*support(invRS1*v) + direction*rotationRadius1, t2*shape.support(invRS2*(-v)) - direction*rotationRadius2);
        }

        void ConvexShape::getHitParameters(const Vector3& direction, float maxHP, const Matrix4x4& t1, const Matrix4x4& invRS1, float rotationSpeed1, const ConvexShape& shape, const Matrix4x4& t2, const Matrix4x4& invRS2, float rotationSpeed2, bool* collision, float* hp, Vector3* normal)
        {
          float angleCoef = M_PI/180.0;
          float rotationRadius1 = 2.0*getRadius()*abs(sin((rotationSpeed1*maxHP*angleCoef)/2.0));
          float rotationRadius2 = 2.0*shape.getRadius()*abs(sin((rotationSpeed2*maxHP*angleCoef)/2.0));

          *hp = 0;
          Vector3 rcpoint(0,0,0);
          *normal = Vector3(0.0,0.0,0.0);
          Vector3 v = RaycastSupport(&rcpoint, support(direction, t1, invRS1, rotationRadius1, shape, t2, invRS2, rotationRadius2)).getMdPosition();

          Simplex simplex;

          int i = 0;
          while(v.dot(v) > 0.000001)
          {

            RaycastSupport w = RaycastSupport(&rcpoint, support(v, t1, invRS1, rotationRadius1, shape, t2, invRS2, rotationRadius2));
            float vw = v.dot(w.getMdPosition());
            //std::cout << "vw: " << vw << std::endl;
            if(vw > 0.0)
            {
              float vr = v.dot(direction);
              //std::cout << "vr: " << vr << std::endl;
              if(vr >= 0.0)
              {
                //std::cout << "NO COLLISION" << std::endl;
                *collision = false;
                return;
              }
              else
              {
                if(vr < -0.000001)
                {
                  (*hp) -= vw/vr;
                  rcpoint = direction*(*hp);
                  *normal = v;
                }
              }
            }
            simplex.add(w);
            v = simplex.getNearZero();
            //v.print();
            //std::cout << "value: " << v.dot(v) << std::endl;

            i++;
            if(i > 25)
            {
              //std::cout << "ERROR INF LOOP: " << v.dot(v) << " : " << *hp << std::endl;
              break;
            }
          }

          *collision = true;
          normal->normalize();

          float newHp = *hp;

          float nr = normal->dot(direction);

          if(nr < -0.000001)
          {
            newHp = *hp + 0.01/nr;
          }

          if(newHp > 0.0)
          {
            *hp = newHp;
          }
          else
          {
            *hp = 0.0;
          }
        }
      }
    }
  }
}
