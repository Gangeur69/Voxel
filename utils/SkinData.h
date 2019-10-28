#ifndef SKINDATA_H
#define SKINDATA_H

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class SkinData
      {
      private:
        int amount;
        int* jointIds;
        float* weights;
      public:
        SkinData(int, int*, float*);
        ~SkinData();
        SkinData(const SkinData&);
        SkinData& operator=(const SkinData&);
        int* getJointIds() const;
        float* getWeights() const;
      };
    }
  }
}

#endif
