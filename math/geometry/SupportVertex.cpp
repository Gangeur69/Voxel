#include "SupportVertex.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        SupportVertex::SupportVertex()
        {

        }

        SupportVertex::SupportVertex(const Vector3& shape1Position, const Vector3& shape2Position)
        {
          this->shape1Position = shape1Position;
          this->shape2Position = shape2Position;
          mdPoisition = shape1Position - shape2Position;
        }

        SupportVertex::SupportVertex(const SupportVertex& sv)
        {
          shape1Position = sv.shape1Position;
          shape2Position = sv.shape2Position;
          mdPoisition = sv.mdPoisition;
        }

        SupportVertex& SupportVertex::operator=(const SupportVertex& sv)
        {
          shape1Position = sv.shape1Position;
          shape2Position = sv.shape2Position;
          mdPoisition = sv.mdPoisition;
          return *this;
        }

        SupportVertex SupportVertex::operator+(const SupportVertex& sv) const
        {
          return SupportVertex(shape1Position + sv.shape1Position, shape2Position + sv.shape2Position);
        }

        SupportVertex SupportVertex::operator-(const SupportVertex& sv) const
        {
          return SupportVertex(shape1Position - sv.shape1Position, shape2Position - sv.shape2Position);
        }

        Vector3 SupportVertex::getShape1Position() const
        {
          return shape1Position;
        }

        Vector3 SupportVertex::getShape2Position() const
        {
          return shape2Position;
        }
        Vector3 SupportVertex::getMdPosition() const
        {
          return mdPoisition;
        }

        SupportVertex operator*(float x, const SupportVertex& sv)
        {
          return SupportVertex(x*sv.getShape1Position(), x*sv.getShape2Position());
        }

        SupportVertex operator*(const SupportVertex& sv, float x)
        {
          return x*sv;
        }
      }
    }
  }
}
