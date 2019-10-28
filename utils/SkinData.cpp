#include "SkinData.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      SkinData::SkinData(int amount, int* jointIds, float* weights)
      {
        this->amount = amount;
        this->jointIds = new int[amount];
        this->weights = new float[amount];
        for(int i=0;i<amount;i++)
        {
          *(this->jointIds + i) = *(jointIds + i);
          *(this->weights + i) = *(weights + i);
        }
      }

      SkinData::~SkinData()
      {
        delete [] jointIds;
        delete [] weights;
      }

      SkinData::SkinData(const SkinData& skinData)
      {
        amount = skinData.amount;
        jointIds = new int[amount];
        weights = new float[amount];
        for(int i=0;i<amount;i++)
        {
          *(jointIds + i) = *(skinData.jointIds + i);
          *(weights + i) = *(skinData.weights + i);
        }
      }

      SkinData& SkinData::operator=(const SkinData& skinData)
      {
        delete [] jointIds;
        delete [] weights;

        amount = skinData.amount;
        jointIds = new int[amount];
        weights = new float[amount];
        for(int i=0;i<amount;i++)
        {
          *(jointIds + i) = *(skinData.jointIds + i);
          *(weights + i) = *(skinData.weights + i);
        }
        return *this;
      }

      int* SkinData::getJointIds() const
      {
        return jointIds;
      }

      float* SkinData::getWeights() const
      {
        return weights;
      }
    }
  }
}
