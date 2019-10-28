#ifndef CAMERA_H
#define CAMERA_H

#include "../math/Vector3.h"
#include "../math/Quaternion.h"
#include "../math/Matrix4x4.h"

using namespace gt::doubovik::math;

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      class Camera
      {
      private:
        Vector3 position;
        Vector3 rotation;
      public:
        Camera(const Vector3&);
        Camera(const Camera&);
        Camera& operator=(const Camera&);
        Vector3& getPosition();
        Vector3& getRotation();
        Matrix4x4 getTransformation() const;
        Vector3 getDirection() const;
      };
    }
  }
}

#endif
