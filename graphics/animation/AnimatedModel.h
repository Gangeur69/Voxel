#ifndef ANIMATEDMODEL_H
#define ANIMATEDMODEL_H

#include "../Mesh.h"
#include "../Texture.h"

#include "Joint.h"
#include "../../math/Matrix4x4.h"
#include "Animation.h"
#include "Animator.h"
#include "Armature.h"

using namespace gt::doubovik::math;

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        class AnimatedModel
        {
        private:
          Mesh* mesh;
          Texture* texture;

          Armature armature;
          Animator animator;

          void addMatrixToArray(Matrix4x4*, Joint*);
          void transformJoint(Joint&, int, const Matrix4x4&);
        public:
          AnimatedModel(Mesh*, Texture*, const Armature&, Animation*);
          AnimatedModel(const AnimatedModel&);
          AnimatedModel& operator=(const AnimatedModel&);

          void setAnimation(Animation*);
          void getMatrixArray(Matrix4x4*);
          void transformJoint(int, const Matrix4x4&);
          void update(float);
          Armature& getArmature();
          Animator& getAnimator();
        };
      }
    }
  }
}

#endif
