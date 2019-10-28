#include "Object.h"

#include "../math/Quaternion.h"

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      Object::Object(ConvexShape* hitbox, const Vector3& position)
      {
        rotation = Quaternion(0, Vector3(1,0,0));
        this->hitbox = hitbox;
        this->position = position;
        onGround = false;
      }

      Object::Object(const Object& object)
      {
        hitbox = object.hitbox;
        position = object.position;
        speed = object.speed;
        rotation = object.rotation;
        rotationSpeed = object.rotationSpeed;
        onGround = object.onGround;
      }

      Object& Object::operator=(const Object& object)
      {
        hitbox = object.hitbox;
        position = object.position;
        speed = object.speed;
        rotation = object.rotation;
        rotationSpeed = object.rotationSpeed;
        onGround = object.onGround;
        return *this;
      }

      Vector3& Object::getPosition()
      {
        return position;
      }

      Quaternion& Object::getRotation()
      {
        return rotation;
      }

      Vector3 Object::getDirection(const Vector3& v) const
      {
        Vector3 direction = rotation.rotate(v);
        direction.normalize();
        return direction;
      }

      Vector3& Object::getSpeed()
      {
        return speed;
      }

      Vector3& Object::getRotationSpeed()
      {
        return rotationSpeed;
      }

      float Object::getRotationSpeedAngle() const
      {
        return rotationSpeed.getLength();
      }

      Vector3 Object::getRotationDirection() const
      {
        Vector3 direction = rotationSpeed;
        direction.normalize();
        return direction;
      }

      Matrix4x4 Object::getTransformation() const
      {
        Matrix4x4 m = rotation.toMatrix4x4();
        m.get(0,3) = position.getX();
        m.get(1,3) = position.getY();
        m.get(2,3) = position.getZ();
        return m;
      }

      Matrix4x4 Object::getInverseRotation() const
      {
        return rotation.conjugate().toMatrix4x4();
      }

      ConvexShape& Object::getHitbox() const
      {
        return *hitbox;
      }

      CollisionData Object::getCollisionData(float timePassed, Object& object)
      {
        return CollisionData(false, timePassed, 0.0, Vector3(0,0,0));
      }

      bool Object::isOnGround() const
      {
        return onGround;
      }

      void Object::setOnGround(bool onGround)
      {
        this->onGround = onGround;
      }
    }
  }
}
