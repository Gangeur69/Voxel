#ifndef SUPPORTVERTEX_H
#define SUPPORTVERTEX_H

#include "../Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        class SupportVertex
        {
        private:
          Vector3* shape1PositionPtr;
          Vector3* shape2PositionPtr;
          Vector3 shape1Position;
          Vector3 shape2Position;
          Vector3 mdPoisition;
        public:
          SupportVertex();
          SupportVertex(const Vector3&, const Vector3&);
          SupportVertex(const SupportVertex&);
          SupportVertex& operator=(const SupportVertex&);

          SupportVertex operator+(const SupportVertex&) const;
          SupportVertex operator-(const SupportVertex&) const;
          Vector3 getShape1Position() const;
          Vector3 getShape2Position() const;
          Vector3 getMdPosition() const;
        };

        SupportVertex operator*(float, const SupportVertex&);
        SupportVertex operator*(const SupportVertex&, float);
      }
    }
  }
}

#endif
