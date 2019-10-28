#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "Matrix.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      class SquareMatrix : public Matrix
      {
      private:
        int getNonZeroLine(unsigned int) const;
      public:
        SquareMatrix(unsigned int);
        SquareMatrix invert() const;
      };
    }
  }
}

#endif
