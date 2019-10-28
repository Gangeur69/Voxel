#ifndef JOINTANIMATION_H
#define JOINTANIMATION_H

#include "JointPose.h"
#include "../../math/Matrix4x4.h"
#include "../../utils/LinkedList.h"

using namespace gt::doubovik::math;

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        class JointAnimation
        {
        private:
          float* timeStamps;
          JointPose* poses;
          int size;
        public:
          JointAnimation();
          JointAnimation(const LinkedList<float>&, const LinkedList<Matrix4x4>&);
          ~JointAnimation();
          JointAnimation(const JointAnimation&);
          JointAnimation& operator=(const JointAnimation&);

          JointPose getPoseAt(float animationTime);
          void getPosesSurrounding(float, float*, JointPose*, JointPose*);
          float getDuration() const;
        };
      }
    }
  }
}

#endif
