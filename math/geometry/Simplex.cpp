#include "Simplex.h"

#include <cstddef>
#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        Simplex::Simplex()
        {
          amount = 0;
          positions = NULL;
        }

        Simplex::~Simplex()
        {
          deleteData();
        }

        void Simplex::deleteData()
        {
          if(positions != NULL)
          {
            delete [] positions;
            positions = NULL;
          }
        }

        void Simplex::buildPoint(const RaycastSupport& sv)
        {
          amount = 1;
          RaycastSupport* newPositions = new RaycastSupport[amount];
          *newPositions = sv;
          deleteData();
          positions = newPositions;
        }

        void Simplex::buildLine(const RaycastSupport& sv1, const RaycastSupport& sv2)
        {
          amount = 2;
          RaycastSupport* newPositions = new RaycastSupport[amount];
          *newPositions = sv1;
          *(newPositions + 1) = sv2;
          deleteData();
          positions = newPositions;
        }

        void Simplex::buildTriangle(const RaycastSupport& sv1, const RaycastSupport& sv2, const RaycastSupport& sv3)
        {
          amount = 3;
          RaycastSupport* newPositions = new RaycastSupport[amount];
          *newPositions = sv1;
          *(newPositions + 1) = sv2;
          *(newPositions + 2) = sv3;
          deleteData();
          positions = newPositions;
        }

        void Simplex::buildTetrahedron(const RaycastSupport& sv1, const RaycastSupport& sv2, const RaycastSupport& sv3, const RaycastSupport& sv4)
        {
          amount = 4;
          RaycastSupport* newPositions = new RaycastSupport[amount];
          *newPositions = sv1;
          *(newPositions + 1) = sv2;
          *(newPositions + 2) = sv3;
          *(newPositions + 3) = sv4;
          deleteData();
          positions = newPositions;
        }

        void Simplex::calculateBarycentricCoords(const Vector3& OA, const Vector3& OB, float* u, float* v)
        {
          Vector3 AB = OB - OA;
          *v = -OA.dot(AB)/AB.dot(AB);
          *u = 1.0 - *v;
        }

        void Simplex::calculateBarycentricCoords(const Vector3& OA, const Vector3& OB, const Vector3& OC, float* u, float* v, float* w)
        {
          Vector3 AB = OB - OA;
          Vector3 AC = OC - OA;

          float ABAB = AB.dot(AB);
          float ABAC = AB.dot(AC);

          float ACAC = AC.dot(AC);

          float AOAB = -(OA.dot(AB));
          float AOAC = -(OA.dot(AC));

          float idetA = 1.0/(ABAB*ACAC - ABAC*ABAC);
          *v = (AOAB*ACAC - AOAC*ABAC)*idetA;
          *w = (ABAB*AOAC - ABAC*AOAB)*idetA;
          *u = 1.0 - *v - *w;
        }

        void Simplex::calculateNearZero(const Vector3& OA)
        {
          nearZero = OA;
        }

        void Simplex::calculateNearZero(const Vector3& OA, const Vector3& OB)
        {
          float u;
          float v;
          calculateBarycentricCoords(OA, OB, &u, &v);
          nearZero = u*OA + v*OB;
          //std::cout << "u : v : sum " << u << " : " << v << " : " << u + v << std::endl;
        }

        void Simplex::calculateNearZero(const Vector3& OA, const Vector3& OB, const Vector3& OC)
        {
          float u;
          float v;
          float w;
          calculateBarycentricCoords(OA, OB, OC, &u, &v, &w);
          nearZero = u*OA + v*OB + w*OC;
          //std::cout << "u : v : w : sum " << u << " : " << v << " : " << w << " : " << u + v + w << std::endl;
        }

        void Simplex::processLine(const RaycastSupport& rs1, const RaycastSupport& rs2)
        {
          Vector3 OA = rs1.getMdPosition();
          Vector3 OB = rs2.getMdPosition();
          Vector3 AB = OB - OA;

          if(OA.dot(AB) >= 0.0)
          {
            buildPoint(rs1);
            calculateNearZero(OA);
          }
          else if(OB.dot(AB) <= 0.0)
          {
            buildPoint(rs2);
            calculateNearZero(OB);
          }
          else
          {
            buildLine(rs1, rs2);
            calculateNearZero(OA, OB);
          }
        }

        void Simplex::processTriangle(const RaycastSupport& rs1, const RaycastSupport& rs2, const RaycastSupport& rs3)
        {
          Vector3 OA = rs1.getMdPosition();
          Vector3 OB = rs2.getMdPosition();
          Vector3 OC = rs3.getMdPosition();

          Vector3 AB = OB - OA;
          Vector3 BC = OC - OB;
          Vector3 CA = OA - OC;

          float AOAB = -OA.dot(AB);
          float AOAC = OA.dot(CA);

          float BOBA = OB.dot(AB);
          float BOBC = -OB.dot(BC);

          float COCA = -OC.dot(CA);
          float COCB = OC.dot(BC);

          if(AOAB <= 0.0 && AOAC <= 0.0) //A
          {
            buildPoint(rs1);
            calculateNearZero(OA);
          }
          else if(BOBA <= 0.0 && BOBC <= 0.0)//B
          {
            buildPoint(rs2);
            calculateNearZero(OB);
          }
          else if(COCA <= 0.0 && COCB <= 0.0) //C
          {
            buildPoint(rs3);
            calculateNearZero(OC);
          }
          else
          {
            Vector3 nABC = AB.cross(BC);
            Vector3 nAB = AB.cross(nABC);
            Vector3 nBC = BC.cross(nABC);
            Vector3 nCA = CA.cross(nABC);

            float AOnAB = -OA.dot(nAB);
            float BOnBC = -OB.dot(nBC);
            float COnCA = -OC.dot(nCA);

            if(AOnAB >= 0.0 && AOAB >= 0.0 && BOBA >= 0.0) //AB
            {
              buildLine(rs1, rs2);
              calculateNearZero(OA, OB);
            }
            else if(BOnBC >= 0.0 && BOBC >= 0.0 && COCB >= 0.0) //BC
            {
              buildLine(rs2, rs3);
              calculateNearZero(OB, OC);
            }
            else if(COnCA >= 0.0 && AOAC >= 0.0 && COCA >= 0.0) //CA
            {
              buildLine(rs3, rs1);
              calculateNearZero(OC, OA);
            }
            else //ABC
            {
              if(-OA.dot(nABC) >= 0.0)
              {
                buildTriangle(rs1, rs2, rs3);
                calculateNearZero(OA, OB, OC);
              }
              else
              {
                buildTriangle(rs1, rs3, rs2);
                calculateNearZero(OA, OC, OB);
              }
            }
          }
        }

        void Simplex::processTetrahedron(const RaycastSupport& rs1, const RaycastSupport& rs2, const RaycastSupport& rs3, const RaycastSupport& rs4)
        {
          Vector3 OA = rs1.getMdPosition();
          Vector3 OB = rs2.getMdPosition();
          Vector3 OC = rs3.getMdPosition();
          Vector3 OD = rs4.getMdPosition();

          Vector3 AB = OB - OA;
          Vector3 BC = OC - OB;
          Vector3 CA = OA - OC;

          Vector3 DA = OA - OD;
          Vector3 DB = OB - OD;
          Vector3 DC = OC - OD;

          float AOAB = -OA.dot(AB);
          float AOAC = OA.dot(CA);
          float AOAD = OA.dot(DA);

          float BOBA = OB.dot(AB);
          float BOBC = -OB.dot(BC);
          float BOBD = OB.dot(DB);

          float COCA = -OC.dot(CA);
          float COCB = OC.dot(BC);
          float COCD = OC.dot(DC);

          float DODA = -OD.dot(DA);
          float DODB = -OD.dot(DB);
          float DODC = -OD.dot(DC);

          //std::cout << "points" << std::endl;
          if(AOAB <= 0.0 && AOAC <= 0.0 && AOAD <= 0.0) //A
          {
            buildPoint(rs1);
            calculateNearZero(OA);
          }
          else if(BOBA <= 0.0 && BOBC <= 0.0 && BOBD <= 0.0) //B
          {
            buildPoint(rs2);
            calculateNearZero(OB);
          }
          else if(COCA <= 0.0 && COCB <= 0.0 && COCD <= 0.0) //C
          {
            buildPoint(rs3);
            calculateNearZero(OC);
          }
          else if(DODA <= 0.0 && DODB <= 0.0 && DODC <= 0.0) //D
          {
            buildPoint(rs4);
            calculateNearZero(OD);
          }
          else
          {
            Vector3 nDAB = DA.cross(AB);
            Vector3 nDBC = DB.cross(BC);
            Vector3 nDCA = DC.cross(CA);
            Vector3 nABC = BC.cross(AB);

            Vector3 DABnDA = DA.cross(nDAB);
            Vector3 DABnAB = AB.cross(nDAB);
            Vector3 DABnBD = nDAB.cross(DB);

            Vector3 DBCnDB = DB.cross(nDBC);
            Vector3 DBCnBC = BC.cross(nDBC);
            Vector3 DBCnCD = nDBC.cross(DC);

            Vector3 DCAnDC = DC.cross(nDCA);
            Vector3 DCAnCA = CA.cross(nDCA);
            Vector3 DCAnAD = nDCA.cross(DA);

            Vector3 ABCnAB = nABC.cross(AB);
            Vector3 ABCnBC = nABC.cross(BC);
            Vector3 ABCnCA = nABC.cross(CA);

            float AOdABCnAB = -OA.dot(ABCnAB); //AB
            float AOdDABnAB = -OA.dot(DABnAB);

            float AOdABCnCA = -OA.dot(ABCnCA); //AC
            float AOdDCAnCA = -OA.dot(DCAnCA);

            float AOdDABnDA = -OA.dot(DABnDA); //AD
            float AOdDCAnAD = -OA.dot(DCAnAD);

            float BOdABCnBC = -OB.dot(ABCnBC); //BC
            float BOdDBCnBC = -OB.dot(DBCnBC);

            float BOdDABnBD = -OB.dot(DABnBD); //BD
            float BOdDBCnDB = -OB.dot(DBCnDB);

            float COdDBCnCD = -OC.dot(DBCnCD); //CD
            float COdDCAnDC = -OC.dot(DCAnDC);

            //std::cout << "lines" << std::endl;
            if(AOAB >= 0.0 && BOBA >= 0.0 && AOdABCnAB >= 0.0 && AOdDABnAB >= 0.0) //AB
            {
              buildLine(rs1, rs2);
              calculateNearZero(OA, OB);
            }
            else if(AOAC >= 0.0 && COCA >= 0.0 && AOdABCnCA >= 0.0 && AOdDCAnCA >= 0.0) //AC
            {
              buildLine(rs1, rs3);
              calculateNearZero(OA, OC);
            }
            else if(AOAD >= 0.0 && DODA >= 0.0 && AOdDABnDA >= 0.0 && AOdDCAnAD >= 0.0) //AD
            {
              buildLine(rs1, rs4);
              calculateNearZero(OA, OD);
            }
            else if(BOBC >= 0.0 && COCB >= 0.0 && BOdABCnBC >= 0.0 && BOdDBCnBC >= 0.0) //BC
            {
              buildLine(rs2, rs3);
              calculateNearZero(OB, OC);
            }
            else if(BOBD >= 0.0 && DODB >= 0.0 && BOdDABnBD >= 0.0 && BOdDBCnDB >= 0.0) //BD
            {
              buildLine(rs2, rs4);
              calculateNearZero(OB, OD);
            }
            else if(COCD >= 0.0 && DODC >= 0.0 && COdDBCnCD >= 0.0 && COdDCAnDC >= 0.0) //CD
            {
              buildLine(rs3, rs4);
              calculateNearZero(OC, OD);
            }
            else
            {
              float DOdDAB = -OD.dot(nDAB);
              float DOdDBC = -OD.dot(nDBC);
              float DOdDCA = -OD.dot(nDCA);
              float AOdABC = -OA.dot(nABC);
              //std::cout << DOdDAB << " : " << DOdDBC << " : " << DOdDCA << " : " << AOdABC << std::endl;

              //std::cout << "triangles" << std::endl;
              if(AOdDABnDA <= 0.0 && AOdDABnAB <= 0.0 && BOdDABnBD <= 0.0 && DOdDAB >= 0.0) //DAB
              {
                //std::cout << "DAB" << std::endl;
                buildTriangle(rs4, rs1, rs2);
                calculateNearZero(OD, OA, OB);
              }
              else if(BOdDBCnDB <= 0.0 && BOdDBCnBC <= 0.0 && COdDBCnCD <= 0.0 && DOdDBC >= 0.0) //DBC
              {
                //std::cout << "DBC" << std::endl;
                buildTriangle(rs4, rs2, rs3);
                calculateNearZero(OD, OB, OC);
              }
              else if(COdDCAnDC <= 0.0 && AOdDCAnCA <= 0.0 && AOdDCAnAD <= 0.0 && DOdDCA >= 0.0) //DCA
              {
                //std::cout << "DCA" << std::endl;
                buildTriangle(rs4, rs3, rs1);
                calculateNearZero(OD, OC, OA);
              }
              else if(AOdABCnAB <= 0.0 && BOdABCnBC <= 0.0 && AOdABCnCA <= 0.0 && AOdABC >= 0.0) //ABC
              {
                //std::cout << "ABC" << std::endl;
                buildTriangle(rs1, rs3, rs2);
                calculateNearZero(OA, OC, OB);
              }
              else //ABCD
              {
                //std::cout << DOdDAB << " : " << DOdDBC << " : " << DOdDCA << " : " << AOdABC << std::endl;
                //rs1.getRcPoint()->print();
                //std::cout << "tetrahedron" << std::endl;
                buildTetrahedron(rs1, rs2, rs3, rs4);
                nearZero = Vector3(0.0, 0.0, 0.0);
              }
            }
          }
        }

        bool Simplex::contains(const RaycastSupport& rs) const
        {
          Vector3 OA = rs.getMdPosition();
          for(int i=0;i<amount;i++)
          {
            Vector3 diff = OA - (*(positions + i)).getMdPosition();
            if(diff.dot(diff) < 0.000001)
            {
              return true;
            }
          }
          return false;
        }

        void Simplex::add(const RaycastSupport& rs)
        {
          if(contains(rs))
          {
            return;
          }

          if(amount == 0)
          {
            //std::cout << "POINT" << std::endl;
            buildPoint(rs);
            calculateNearZero(rs.getMdPosition());
          }
          else if(amount == 1)
          {
            //std::cout << "LINE" << std::endl;
            processLine(*positions, rs);
          }
          else if(amount == 2)
          {
            //std::cout << "TRIANGLE" << std::endl;
            processTriangle(*positions, *(positions + 1), rs);
          }
          else if(amount == 3)
          {
            //std::cout << "TETRAHEDRON" << std::endl;
            processTetrahedron(*positions, *(positions + 1), *(positions + 2), rs);
          }
        }

        const Vector3& Simplex::getNearZero() const
        {
          return nearZero;
        }
      }
    }
  }
}
