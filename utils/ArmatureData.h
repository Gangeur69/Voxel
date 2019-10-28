#ifndef ARMATUREDATA_H
#define ARMATUREDATA_H

#include "../graphics/animation/Joint.h"
#include "String.h"

using namespace gt::doubovik::graphics::animation;

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class ArmatureData
      {
      private:
        int jointAmount;
        String* jointIdNames;
        Joint rootJoint;
      public:
        ArmatureData(int, String*, const Joint&);
        ~ArmatureData();
        ArmatureData(const ArmatureData&);
        ArmatureData& operator=(const ArmatureData&);
        int getJointAmount() const;
        String* getJointIdNames() const;
        const Joint& getRootJoint() const;
      };
    }
  }
}

#endif
