#include "Armature.h"

#include <iostream>
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
        Armature::Armature(int jointAmount, const Joint& rootJoint)
        {
          this->jointAmount = jointAmount;
          this->rootJoint = rootJoint;
          this->rootJoint.calculateInverseDefaultTransformation(Matrix4x4());
        }

        Armature::Armature(const Armature& armature)
        {
          jointAmount = armature.jointAmount;
          rootJoint = armature.rootJoint;
        }

        Armature& Armature::operator=(const Armature& armature)
        {
          jointAmount = armature.jointAmount;
          rootJoint = armature.rootJoint;
          return *this;
        }

        Joint& Armature::getRoot()
        {
          return rootJoint;
        }

        Joint* Armature::getJoint(int index, Joint& joint)
        {
          if(joint.getIndex() == index)
          {
            return &joint;
          }
          for(LinkedListIterator<Joint> itt=joint.getChildren().getIterator();itt.isValid();itt.next())
          {
            Joint* found = getJoint(index, itt.getElement());
            if(found != NULL)
            {
              return found;
            }
          }
          return NULL;
        }

        Joint* Armature::getJoint(int index)
        {
          Joint* joint = getJoint(index, rootJoint);
          if(joint == NULL)
          {
            std::cerr << "ERROR JOINT NOT FOUND: " << index << std::endl;
            throw("joint not found!");
          }
          return joint;
        }
      }
    }
  }
}
