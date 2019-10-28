#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H

#include "../Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        class CollisionData
        {
        private:
          bool collision;
          float validTime;
          float penetration;
          Vector3 normal;
        public:
          CollisionData(bool, float, float, const Vector3&);
          CollisionData(const CollisionData&);
          CollisionData& operator=(const CollisionData&);

          bool hasCollision() const;
          float getValidTime() const;
          float getPenetration() const;
          Vector3 getNormal() const;
        };
      }
    }
  }
}

#endif
