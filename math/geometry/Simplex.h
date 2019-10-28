#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "RaycastSupport.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        class Simplex
        {
        private:
          int amount;
          RaycastSupport* positions;
          Vector3 nearZero;
          void deleteData();
        public:
          Simplex();
          ~Simplex();

          void buildPoint(const RaycastSupport&);
          void buildLine(const RaycastSupport&, const RaycastSupport&);
          void buildTriangle(const RaycastSupport&, const RaycastSupport&, const RaycastSupport&);
          void buildTetrahedron(const RaycastSupport&, const RaycastSupport&, const RaycastSupport&, const RaycastSupport&);

          void calculateBarycentricCoords(const Vector3&, const Vector3&, float*, float*);
          void calculateBarycentricCoords(const Vector3&, const Vector3&, const Vector3&, float*, float*, float*);

          void calculateNearZero(const Vector3&);
          void calculateNearZero(const Vector3&, const Vector3&);
          void calculateNearZero(const Vector3&, const Vector3&, const Vector3&);

          void processLine(const RaycastSupport&, const RaycastSupport&);
          void processTriangle(const RaycastSupport&, const RaycastSupport&, const RaycastSupport&);
          void processTetrahedron(const RaycastSupport&, const RaycastSupport&, const RaycastSupport&, const RaycastSupport&);

          bool contains(const RaycastSupport&) const;

          void add(const RaycastSupport&);
          const Vector3& getNearZero() const;
        };
      }
    }
  }
}

#endif
