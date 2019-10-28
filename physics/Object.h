#ifndef OBJECT_H
#define OBJECT_H

#include "../graphics/Mesh.h"
#include "../math/Vector3.h"
#include "../math/Matrix4x4.h"
#include "../math/Quaternion.h"
#include "../math/geometry/ConvexShape.h"
#include "../math/geometry/CollisionData.h"

using namespace gt::doubovik::math;
using namespace gt::doubovik::math::geometry;
using namespace gt::doubovik::graphics;

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      class Object
      {
      private:
        Vector3 position;
        Vector3 speed;
        Quaternion rotation;
        Vector3 rotationSpeed;
        ConvexShape* hitbox;
        bool onGround;
      public:
        Object(ConvexShape*, const Vector3&);
        Object(const Object&);
        Object& operator=(const Object&);

        Vector3& getPosition();
        Vector3& getSpeed();
        Quaternion& getRotation();
        Vector3 getDirection(const Vector3&) const;
        Vector3& getRotationSpeed();
        float getRotationSpeedAngle() const;
        Vector3 getRotationDirection() const;
        Matrix4x4 getTransformation() const;
        Matrix4x4 getInverseRotation() const;
        ConvexShape& getHitbox() const;
        CollisionData getCollisionData(float, Object&);
        bool isOnGround() const;
        void setOnGround(bool);
      };
    }
  }
}

#endif
