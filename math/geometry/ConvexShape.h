#ifndef CONVEXSHAPE_H
#define CONVEXSHAPE_H

#include "../Vector3.h"
#include "../Matrix4x4.h"
#include "SupportVertex.h"
#include "CollisionData.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        class ConvexShape
        {
        private:
          int amount;
          Vector3* positions;
          float radius;
        public:
          ConvexShape(int, Vector3*);
          ~ConvexShape();
          ConvexShape(const ConvexShape&);
          ConvexShape& operator=(const ConvexShape&);
          float getRadius() const;
          Vector3 support(const Vector3&) const;
          bool isColliding(float, const Matrix4x4&, const Matrix4x4&, float, const ConvexShape&, const Matrix4x4&, const Matrix4x4&, float);
          Vector3 getDistance(Vector3*, const Matrix4x4&, const Matrix4x4&, float, const ConvexShape&, const Matrix4x4&, const Matrix4x4&, float);
          void getCAHitParameters(const Vector3&, float, const Matrix4x4&, const Matrix4x4&, float, const ConvexShape&, const Matrix4x4&, const Matrix4x4&, float, bool*, float*, Vector3*);

          SupportVertex support(const Vector3&, const Matrix4x4&, const Matrix4x4&, float, const ConvexShape&, const Matrix4x4&, const Matrix4x4&, float);
          void getHitParameters(const Vector3&, float, const Matrix4x4&, const Matrix4x4&, float, const ConvexShape&, const Matrix4x4&, const Matrix4x4&, float, bool*, float*, Vector3*);
        };
      }
    }
  }
}

#endif
