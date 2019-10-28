#include "Joint.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {

        Joint::Joint()
        {

        }

        Joint::Joint(int index, const String& name, const Matrix4x4& localDefaultTransformation)
        {
          this->index = index;
          this->name = name;
          this->localDefaultTransformation = localDefaultTransformation;
        }

        Joint::Joint(const Joint& joint)
        {
          index = joint.index;
          name = joint.name;
          children = joint.children;

          transformation = joint.transformation;
          localDefaultTransformation = joint.localDefaultTransformation;

          defaultTransformation = joint.defaultTransformation;
          inverseDefaultTransformation = joint.inverseDefaultTransformation;
        }

        Joint& Joint::operator=(const Joint& joint)
        {
          index = joint.index;
          name = joint.name;
          children = joint.children;

          transformation = joint.transformation;
          localDefaultTransformation = joint.localDefaultTransformation;

          defaultTransformation = joint.defaultTransformation;
          inverseDefaultTransformation = joint.inverseDefaultTransformation;
          return *this;
        }

        String Joint::getName() const
        {
          return name;
        }

        LinkedList<Joint>& Joint::getChildren()
        {
          return children;
        }

        Matrix4x4& Joint::getTransformation()
        {
          return transformation;
        }

        const Matrix4x4& Joint::getDefaultTransformation() const
        {
          return defaultTransformation;
        }

        Matrix4x4& Joint::getInverseDefaultTransformation()
        {
          return inverseDefaultTransformation;
        }

        int Joint::getIndex() const
        {
          return index;
        }

        void Joint::transform(const Matrix4x4& parentTransformation, const Matrix4x4& newTransformation)
        {
          transformation = parentTransformation * newTransformation * inverseDefaultTransformation;
        }

        void Joint::calculateInverseDefaultTransformation(const Matrix4x4& parentTransformation)
        {
          defaultTransformation = parentTransformation*localDefaultTransformation;
          inverseDefaultTransformation = defaultTransformation.invert();
          for(LinkedListIterator<Joint> itt=children.getIterator();itt.isValid();itt.next())
          {
            itt.getElement().calculateInverseDefaultTransformation(defaultTransformation);
          }
        }
      }
    }
  }
}
