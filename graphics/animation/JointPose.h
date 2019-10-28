#ifndef JOINTPOSE_H
#define JOINTPOSE_H

#include "../../math/Vector3.h"
#include "../../math/Quaternion.h"
#include "../../math/Matrix4x4.h"

using namespace gt::doubovik::math;

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        class JointPose
        {
        private:
          Vector3 position;
          Vector3 scale;
          Quaternion rotation;
        public:
          JointPose();
          JointPose(const Vector3&, const Vector3&, const Quaternion&);
          JointPose(const Matrix4x4&);
          JointPose(const JointPose&);
          JointPose& operator=(const JointPose&);
          Matrix4x4 getTransformation() const;
          JointPose interpolate(float, const JointPose&) const;
        };
      }
    }
  }
}

#endif
