#include "ArmatureData.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      ArmatureData::ArmatureData(int jointAmount, String* jointIdNames, const Joint& rootJoint)
      {
        this->jointAmount = jointAmount;
        this->jointIdNames = new String[jointAmount];
        for(int i=0;i<jointAmount;i++)
        {
          *(this->jointIdNames + i) = *(jointIdNames + i);
        }
        this->rootJoint = rootJoint;
      }

      ArmatureData::~ArmatureData()
      {
        delete [] jointIdNames;
      }

      ArmatureData::ArmatureData(const ArmatureData& data)
      {
        jointAmount = data.jointAmount;
        jointIdNames = new String[jointAmount];
        for(int i=0;i<jointAmount;i++)
        {
          *(jointIdNames + i) = *(data.jointIdNames + i);
        }
        rootJoint = data.rootJoint;
      }

      ArmatureData& ArmatureData::operator=(const ArmatureData& data)
      {
        delete [] jointIdNames;

        jointAmount = data.jointAmount;
        jointIdNames = new String[jointAmount];
        for(int i=0;i<jointAmount;i++)
        {
          *(jointIdNames + i) = *(data.jointIdNames + i);
        }
        rootJoint = data.rootJoint;
        return *this;
      }

      int ArmatureData::getJointAmount() const
      {
        return jointAmount;
      }

      String* ArmatureData::getJointIdNames() const
      {
        return jointIdNames;
      }

      const Joint& ArmatureData::getRootJoint() const
      {
        return rootJoint;
      }
    }
  }
}
