#include "SquareMatrix.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      SquareMatrix::SquareMatrix(unsigned int size) : Matrix(size, size)
      {
        setDiag(1);
      }

      int SquareMatrix::getNonZeroLine(unsigned int index) const
      {
        for(unsigned int i=index;i<height;i++)
        {
          if(get(i, index)*get(i, index) >= 0.000001)
          {
            return i;
          }
        }
        return -1;
      }

      SquareMatrix SquareMatrix::invert() const
      {
        SquareMatrix res(width);
        SquareMatrix m = *this;

        for(unsigned int i=0;i<m.height;i++)
        {
          if(m.get(i,i)*m.get(i,i) < 0.000001)
          {
            int toSwap = m.getNonZeroLine(i);
            if(toSwap < 0)
            {
              std::cerr << "ERROR: tying to invert non invertable matrix!" << std::endl;
              exit(EXIT_FAILURE);
            }
            m.swapLines(i, toSwap);
            res.swapLines(i ,toSwap);
          }
          float coefi = 1.0/m.get(i,i);
          m.multiplyLine(i, coefi);
          res.multiplyLine(i , coefi);

          for(unsigned int j=0;j<m.height;j++)
          {
            if(j != i)
            {
              float coefj = -m.get(j,i);
              m.addLineToLine(coefj, i, j);
              res.addLineToLine(coefj, i, j);
            }
          }
        }
        return res;
      }
    }
  }
}
