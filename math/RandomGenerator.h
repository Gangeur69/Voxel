#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      class RandomGenerator
      {
      private:
        long seed;
        long a;
        long m;
        long c;
        long getValue(long) const;
        float interpolate(float, float, float) const;
      public:
        RandomGenerator(long);
        RandomGenerator(const RandomGenerator&);
        RandomGenerator& operator=(const RandomGenerator&);
        long getNext();
        float getNextFloat();
        float getNoise(int, int) const;
        float getSmoothNoise(int, int) const;
        float getInterpolatedNoise(float, float) const;
      };
    }
  }
}

#endif
