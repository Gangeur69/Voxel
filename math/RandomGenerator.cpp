#include "RandomGenerator.h"

#include <math.h>

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      RandomGenerator::RandomGenerator(long seed)
      {
        m = 30323;
        a = 172;
        c = 0;
        this->seed = seed;
      }

      RandomGenerator::RandomGenerator(const RandomGenerator& generator)
      {
        m = generator.m;
        a = generator.a;
        c = generator.c;
        seed = generator.seed;
      }

      RandomGenerator& RandomGenerator::operator=(const RandomGenerator& generator)
      {
        m = generator.m;
        a = generator.a;
        c = generator.c;
        seed = generator.seed;
        return *this;
      }

      long RandomGenerator::getValue(long x) const
      {
        return (a * x + c)%m;
      }

      long RandomGenerator::getNext()
      {
        seed = getValue(seed);
        return seed;
      }

      float RandomGenerator::getNextFloat()
      {
        long r = getNext();
        return ((float)r)/((float)(m-1));
      }

      float RandomGenerator::getNoise(int x, int y) const
      {
        if(x >= 0)
        {
          x = 2*x;
        }
        else
        {
          x = -2*x + 1;
        }

        if(y >= 0)
        {
          y = 2*y;
        }
        else
        {
          y = -2*y + 1;
        }
        int r = getValue(seed + 436*x + 154*y + x*y);
        return ((float)r)/((float)(m-1));
      }

      float RandomGenerator::getSmoothNoise(int x, int y) const
      {
        float corners = (getNoise(x-1,y-1) + getNoise(x+1,y-1) + getNoise(x+1,y+1) + getNoise(x-1,y+1))/16.0;
        float sides = (getNoise(x-1,y) + getNoise(x,y-1) + getNoise(x+1,y) + getNoise(x,y+1))/8.0;
        float middle = getNoise(x,y)/4.0;
        return corners + sides + middle;
      }

      float RandomGenerator::interpolate(float t, float a, float b) const
      {
        t = (1.0 - t) * M_PI;
        t = (cos(t) + 1)*0.5;
        return a + (b-a)*t;
      }

      float RandomGenerator::getInterpolatedNoise(float x, float y) const
      {
        int iX = (int)x;
        int iY = (int)y;
        float tX = x - (float)iX;
        float tY = y - (float)iY;
        if(x < 0)
        {
          tX = 1 + tX;
          iX--;
        }
        if(y < 0)
        {
          tY = 1+tY;
          iY--;
        }

        float v1 = getSmoothNoise(iX, iY);
        float v2 = getSmoothNoise(iX + 1, iY);
        float v3 = getSmoothNoise(iX + 1, iY + 1);
        float v4 = getSmoothNoise(iX, iY + 1);

        float i1 = interpolate(tX, v1, v2);
        float i2 = interpolate(tX, v4, v3);
        return interpolate(tY, i1, i2);
      }
    }
  }
}
