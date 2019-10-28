#include "Animation.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        Animation::Animation()
        {
          size = 0;
          duration = 0;
          jointAnimations = NULL;
        }

        Animation::Animation(const LinkedList<int>& jointAnimationIds, const LinkedList<JointAnimation>& jointAnimationsList)
        {
          size = jointAnimationIds.size();
          jointAnimations = new JointAnimation[size];

          LinkedListIterator<int> itt1 = jointAnimationIds.getIterator();
          LinkedListIterator<JointAnimation> itt2 = jointAnimationsList.getIterator();
          duration = 0;
          for(int i=0;i<size;i++)
          {
            *(jointAnimations + itt1.getElement()) = itt2.getElement();
            if(itt2.getElement().getDuration() > duration)
            {
              duration = itt2.getElement().getDuration();
            }
            itt1.next();
            itt2.next();
          }
        }

        Animation::~Animation()
        {
          if(jointAnimations != NULL)
          {
            delete [] jointAnimations;
          }
        }

        Animation::Animation(const Animation& animation)
        {
          size = animation.size;
          duration = animation.duration;
          playOnce = animation.playOnce;
          jointAnimations = new JointAnimation[size];
          for(int i=0;i<size;i++)
          {
            *(jointAnimations + i) = *(animation.jointAnimations + i);
          }
        }

        Animation& Animation::operator=(const Animation& animation)
        {
          if(jointAnimations != NULL)
          {
            delete [] jointAnimations;
          }
          size = animation.size;
          duration = animation.duration;
          playOnce = animation.playOnce;
          jointAnimations = new JointAnimation[size];
          for(int i=0;i<size;i++)
          {
            *(jointAnimations + i) = *(animation.jointAnimations + i);
          }
          return *this;
        }

        int Animation::getSize() const
        {
          return size;
        }

        void Animation::getPoseAt(float animationTime, JointPose* poses)
        {
          for(int i=0;i<size;i++)
          {
            *(poses + i) = (*(jointAnimations + i)).getPoseAt(animationTime);
          }
        }

        float Animation::getDuration() const
        {
          return duration;
        }

        bool Animation::toBeReplayed() const
        {
          return !playOnce;
        }

        void Animation::setToBeReplayed(bool playOnce)
        {
          this->playOnce = !playOnce;
        }
      }
    }
  }
}
