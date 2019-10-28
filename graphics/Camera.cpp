#include "Camera.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      Camera::Camera(const Vector3& position)
      {
        this->position = position;
      }

      Camera::Camera(const Camera& camera)
      {
        position = camera.position;
        rotation = camera.rotation;
      }

      Camera& Camera::operator=(const Camera& camera)
      {
        position = camera.position;
        rotation = camera.rotation;
        return *this;
      }

      Vector3& Camera::getPosition()
      {
        return position;
      }

      Vector3& Camera::getRotation()
      {
        return rotation;
      }

      Matrix4x4 Camera::getTransformation() const
      {
        Quaternion qx(-rotation.getX(), Vector3(1,0,0));
        Quaternion qy(-rotation.getY(), Vector3(0,1,0));
        Quaternion qz(-rotation.getZ(), Vector3(0,0,1));
        Matrix4x4 rotationm = (qz*qx*qy).toMatrix4x4();
        Matrix4x4 translation;
        translation.get(0,3) = -position.getX();
        translation.get(1,3) = -position.getY();
        translation.get(2,3) = -position.getZ();
        return rotationm*translation;
      }

      Vector3 Camera::getDirection() const
      {
        Quaternion qx(rotation.getX(), Vector3(1,0,0));
        Quaternion qy(rotation.getY(), Vector3(0,1,0));
        Quaternion qz(rotation.getZ(), Vector3(0,0,1));
        return (qy*qx*qz).toMatrix4x4()*Vector3(0,0,-1);
      }
    }
  }
}
