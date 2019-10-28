#include "Animator.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        Animator::Animator(Animation* animation)
        {
          animationTime = 0.0;
          this->animation = animation;
        }

        Animator::Animator(const Animator& animator)
        {
          animationTime = animator.animationTime;
          animation = animator.animation;
          hasLooped = animator.hasLooped;
        }

        Animator& Animator::operator=(const Animator& animator)
        {
          animationTime = animator.animationTime;
          animation = animator.animation;
          hasLooped = animator.hasLooped;
          return *this;
        }

        void Animator::update(float timePassed, Joint& root)
        {
          animationTime+=timePassed;
          if(animationTime > animation->getDuration())
          {
            animationTime = 0.0;
            hasLooped = true;
          }

          JointPose poses[animation->getSize()];
          animation->getPoseAt(animationTime, poses);

          applyPose(root, poses, Matrix4x4());
        }

        void Animator::applyPose(Joint& joint, JointPose* poses, const Matrix4x4& parentTransformation)
        {
          int index = joint.getIndex();
          Matrix4x4 newPose = (*(poses + index)).getTransformation();
          Matrix4x4 transformation = parentTransformation*newPose;
          for(LinkedListIterator<Joint> itt=joint.getChildren().getIterator();itt.isValid();itt.next())
          {
            applyPose(itt.getElement(), poses, transformation);
          }
          joint.getTransformation() = transformation*joint.getInverseDefaultTransformation();
        }

        void Animator::setAnimation(Animation* animation)
        {
          animationTime = 0.0;
          hasLooped = false;
          this->animation = animation;
        }

        const Animation& Animator::getAnimation() const
        {
          return *animation;
        }

        bool Animator::animationHasLooped() const
        {
          return hasLooped;
        }

        float Animator::getCurrentTime() const
        {
          return animationTime;
        }
      }
    }
  }
}
