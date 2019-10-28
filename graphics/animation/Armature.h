#ifndef ARMATURE_H
#define ARMATURE_H

#include "Joint.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        class Armature
        {
        private:
          int jointAmount;
          Joint rootJoint;
        public:
          Armature(int, const Joint&);
          Armature(const Armature&);
          Armature& operator=(const Armature&);

          Joint& getRoot();
          Joint* getJoint(int, Joint&);
          Joint* getJoint(int);
        };
      }
    }
  }
}

#endif
