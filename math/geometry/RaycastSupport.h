#ifndef RAYCASTSUPPORT_H
#define RAYCASTSUPPORT_H

#include "SupportVertex.h"
#include "../Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        class RaycastSupport
        {
        private:
          Vector3* rcpoint;
          SupportVertex support;
        public:
          RaycastSupport();
          RaycastSupport(Vector3*, const SupportVertex&);
          RaycastSupport(const RaycastSupport&);
          RaycastSupport& operator=(const RaycastSupport&);

          Vector3 getMdPosition() const;
          Vector3* getRcPoint() const;
          SupportVertex getSupport() const;

          RaycastSupport operator+(const RaycastSupport&) const;
          RaycastSupport operator-(const RaycastSupport&) const;
        };
        RaycastSupport operator*(float, const RaycastSupport&);
        RaycastSupport operator*(const RaycastSupport&, float);
      }
    }
  }
}

#endif
