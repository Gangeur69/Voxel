#ifndef ANIMATION_H
#define ANIMATION_H

#include "JointAnimation.h"
#include "Joint.h"
#include "../../utils/LinkedList.h"
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
        class Animation
        {
        private:
          int size;
          JointAnimation* jointAnimations;
          float duration;

          bool playOnce = false;
        public:
          Animation();
          Animation(const LinkedList<int>&, const LinkedList<JointAnimation>&);
          ~Animation();
          Animation(const Animation&);
          Animation& operator=(const Animation&);

          int getSize() const;
          void getPoseAt(float, JointPose*);
          float getDuration() const;
          bool toBeReplayed() const;
          void setToBeReplayed(bool);
        };
      }
    }
  }
}

#endif
