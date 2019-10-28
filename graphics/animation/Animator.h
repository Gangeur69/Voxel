#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "Animation.h"
#include "Joint.h"
#include "JointPose.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        class Animator
        {
        private:
          float animationTime;
          Animation* animation;

          bool hasLooped = false;
        public:
          Animator(Animation*);
          Animator(const Animator&);
          Animator& operator=(const Animator&);

          void update(float, Joint&);
          void applyPose(Joint&, JointPose*, const Matrix4x4&);
          void setAnimation(Animation*);
          const Animation& getAnimation() const;
          bool animationHasLooped() const;
          float getCurrentTime() const;

        };
      }
    }
  }
}

#endif
