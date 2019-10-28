#include "RaycastSupport.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        RaycastSupport::RaycastSupport()
        {

        }

        RaycastSupport::RaycastSupport(Vector3* rcpoint, const SupportVertex& support)
        {
          this->rcpoint = rcpoint;
          this->support = support;
        }

        RaycastSupport::RaycastSupport(const RaycastSupport& rcs)
        {
          rcpoint = rcs.rcpoint;
          support = rcs.support;
        }

        RaycastSupport& RaycastSupport::operator=(const RaycastSupport& rcs)
        {
          rcpoint = rcs.rcpoint;
          support = rcs.support;
          return *this;
        }

        Vector3 RaycastSupport::getMdPosition() const
        {
          return *rcpoint - support.getMdPosition();
        }

        Vector3* RaycastSupport::getRcPoint() const
        {
          return rcpoint;
        }

        SupportVertex RaycastSupport::getSupport() const
        {
          return support;
        }

        RaycastSupport RaycastSupport::operator+(const RaycastSupport& rcs) const
        {
          return RaycastSupport(rcpoint, support + rcs.support);
        }

        RaycastSupport RaycastSupport::operator-(const RaycastSupport& rcs) const
        {
          return RaycastSupport(rcpoint, support - rcs.support);
        }

        RaycastSupport operator*(float x, const RaycastSupport& rcs)
        {
          return RaycastSupport(rcs.getRcPoint(), x*rcs.getSupport());
        }

        RaycastSupport operator*(const RaycastSupport& rcs, float x)
        {
          return x*rcs;
        }
      }
    }
  }
}
