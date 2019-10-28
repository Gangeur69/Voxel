#ifndef JOINT_H
#define JOINT_H

#include "../../utils/String.h"
#include "../../utils/LinkedList.h"
#include "../../math/Matrix4x4.h"

using namespace gt::doubovik::utils;
using namespace gt::doubovik::math;
using namespace gt::doubovik;

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        class Joint
        {
        private:
          int index;
          String name;
          LinkedList<Joint> children;

          Matrix4x4 transformation;
          Matrix4x4 localDefaultTransformation;

          Matrix4x4 defaultTransformation;
          Matrix4x4 inverseDefaultTransformation;
        public:
          Joint();
          Joint(int, const String&, const Matrix4x4&);
          Joint(const Joint&);
          Joint& operator=(const Joint&);
          LinkedList<Joint>& getChildren();
          Matrix4x4& getTransformation();
          const Matrix4x4& getDefaultTransformation() const;
          Matrix4x4& getInverseDefaultTransformation();
          int getIndex() const;
          String getName() const;
          void calculateInverseDefaultTransformation(const Matrix4x4&);
          void transform(const Matrix4x4&, const Matrix4x4&);
        };
      }
    }
  }
}

#endif
