#include "CollisionData.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        CollisionData::CollisionData(bool collision, float validTime, float penetration, const Vector3& normal)
        {
          this->collision = collision;
          this->validTime = validTime;
          this->penetration = penetration;
          this->normal = normal;
        }

        CollisionData::CollisionData(const CollisionData& data)
        {
          collision = data.collision;
          validTime = data.validTime;
          penetration = data.penetration;
          normal = data.normal;
        }

        CollisionData& CollisionData::operator=(const CollisionData& data)
        {
          collision = data.collision;
          validTime = data.validTime;
          penetration = data.penetration;
          normal = data.normal;
          return *this;
        }

        bool CollisionData::hasCollision() const
        {
          return collision;
        }

        float CollisionData::getValidTime() const
        {
          return validTime;
        }

        float CollisionData::getPenetration() const
        {
          return penetration;
        }

        Vector3 CollisionData::getNormal() const
        {
          return normal;
        }
      }
    }
  }
}
