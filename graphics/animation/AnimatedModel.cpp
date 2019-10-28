#include "AnimatedModel.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        AnimatedModel::AnimatedModel(Mesh* mesh, Texture* texture, const Armature& armature, Animation* animation) : armature(armature), animator(animation)
        {
          this->mesh = mesh;
          this->texture = texture;
          animator.update(0.0, this->armature.getRoot());
        }

        AnimatedModel::AnimatedModel(const AnimatedModel& model) : armature(model.armature), animator(model.animator)
        {
          mesh = model.mesh;
          texture = model.texture;
        }

        AnimatedModel& AnimatedModel::operator=(const AnimatedModel& model)
        {
          mesh = model.mesh;
          texture = model.texture;
          armature = model.armature;
          animator = model.animator;
          return *this;
        }

        void AnimatedModel::setAnimation(Animation* animation)
        {
          animator.setAnimation(animation);
        }

        void AnimatedModel::getMatrixArray(Matrix4x4* list)
        {
          addMatrixToArray(list, &armature.getRoot());
        }

        void AnimatedModel::addMatrixToArray(Matrix4x4* list, Joint* joint)
        {
          *(list + joint->getIndex()) = joint->getTransformation();
          for(LinkedListIterator<Joint> itt=joint->getChildren().getIterator();itt.isValid();itt.next())
          {
            addMatrixToArray(list, &itt.getElement());
          }
        }

        void AnimatedModel::transformJoint(Joint& joint, int index, const Matrix4x4& transformation)
        {
          for(LinkedListIterator<Joint> itt=joint.getChildren().getIterator();itt.isValid();itt.next())
          {
            if(itt.getElement().getIndex() == index)
            {
              itt.getElement().transform(joint.getTransformation(), transformation);
            }
            else
            {
              transformJoint(itt.getElement(), index, transformation);
            }
          }
        }

        void AnimatedModel::transformJoint(int index, const Matrix4x4& transformation)
        {
          transformJoint(armature.getRoot(), index, transformation);
        }

        void AnimatedModel::update(float timePassed)
        {
          animator.update(timePassed, armature.getRoot());
        }

        Armature& AnimatedModel::getArmature()
        {
          return armature;
        }

        Animator& AnimatedModel::getAnimator()
        {
          return animator;
        }

      }
    }
  }
}
