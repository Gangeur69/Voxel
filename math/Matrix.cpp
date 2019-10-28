#include "Matrix.h"

#include <iostream>
#include <stdlib.h>
#include "Matrix4x4.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {

      Matrix::Matrix(unsigned int height, unsigned int width)
      {
        this->height = height;
        this->width = width;

        data = new float*[height];
        for(unsigned int i=0;i<height;i++)
        {
          *(data + i) = new float[width];
        }

        setAll(0);
      }

      Matrix::~Matrix()
      {
        for(unsigned int i=0;i<height;i++)
        {
          delete [] *(data + i);
        }
        delete [] data;
      }

      Matrix::Matrix(const Matrix& matrix)
      {
        height = matrix.height;
        width = matrix.width;

        data = new float*[height];
        for(unsigned int i=0;i<height;i++)
        {
          *(data + i) = new float[width];
        }

        for(unsigned int i=0;i<height;i++)
        {
          for(unsigned int j=0;j<width;j++)
          {
            *(*(data + i) + j) = *(*(matrix.data + i) + j);
          }
        }
      }

      Matrix& Matrix::operator=(const Matrix& matrix)
      {
        for(unsigned int i=0;i<height;i++)
        {
          delete [] *(data + i);
        }
        delete [] data;

        height = matrix.height;
        width = matrix.width;

        data = new float*[height];
        for(unsigned int i=0;i<height;i++)
        {
          *(data + i) = new float[width];
        }

        for(unsigned int i=0;i<height;i++)
        {
          for(unsigned int j=0;j<width;j++)
          {
            *(*(data + i) + j) = *(*(matrix.data + i) + j);
          }
        }
        return *this;
      }

      float& Matrix::get(unsigned int i, unsigned int j) const
      {
        if(i >= height)
        {
          std::cerr << "Error: index i = " << i << " is out of bounds of matrix, height = " << height << std::endl;
          exit(EXIT_FAILURE);
        }
        if(j >= width)
        {
          std::cerr << "Error: index j = " << j << " is out of bounds of matrix, width = " << width << std::endl;
          exit(EXIT_FAILURE);
        }
        return *(*(data + i) + j);
      }

      void Matrix::setAll(float x)
      {
        for(unsigned int i=0;i<height;i++)
        {
          for(unsigned int j=0;j<width;j++)
          {
            *(*(data + i) + j) = x;
          }
        }
      }

      void Matrix::setDiag(float x)
      {
        unsigned int minDim = height;
        if(width < minDim)
        {
          minDim = width;
        }

        for(unsigned int i=0;i<minDim;i++)
        {
          get(i, i) = x;
        }
      }

      void Matrix::print() const
      {
        std::cout << "----------------------------" << std::endl;
        for(unsigned int i=0;i<height;i++)
        {
          for(unsigned int j=0;j<width;j++)
          {
            std::cout << "[" << get(i,j) << "] ";
          }
          std::cout << std::endl;
        }
        std::cout << "----------------------------" << std::endl;
      }

      void Matrix::toArray(float* array) const
      {
        unsigned int k = 0;
        for(unsigned int j=0;j<width;j++)
        {
          for(unsigned int i=0;i<height;i++)
          {
            *(array + k) = get(i,j);
            k++;
          }
        }
      }

      void Matrix::swapLines(unsigned int from, unsigned int to)
      {
        if(from >= height || to >= height)
        {
          std::cerr << "Error: trying to swap lines out of bounds of matrix!" << std::endl;
          exit(EXIT_FAILURE);
        }
        float* toPtr = *(data + to);
        *(data + to) = *(data + from);
        *(data + from) = toPtr;
      }

      void Matrix::multiplyLine(unsigned int line, float x)
      {
        if(line >= height)
        {
          std::cerr << "Error: trying to get line out of bounds of matrix!" << std::endl;
          exit(EXIT_FAILURE);
        }
        for(unsigned int i=0;i<width;i++)
        {
          get(line, i)*=x;
        }
      }

      void Matrix::addLineToLine(float x, unsigned int l1, unsigned int l2)
      {
        if(l1 >= height || l2 >= height)
        {
          std::cerr << "Error: trying to add lines out of bounds of matrix!" << std::endl;
          exit(EXIT_FAILURE);
        }

        for(unsigned int i=0;i<width;i++)
        {
          get(l2, i) = get(l2, i) + get(l1 , i)*x;
        }
      }

      float Matrix::lineColumnProduct(unsigned int line, unsigned int column, const Matrix& matrix) const
      {
        if(line >= height)
        {
          std::cerr << "Error: line = " << line << " is out of bounds, height = " << height << std::endl;
          exit(EXIT_FAILURE);
        }
        if(column >= matrix.width)
        {
          std::cerr << "Error: column = " << column << " is out of bounds, width = " << matrix.width << std::endl;
          exit(EXIT_FAILURE);
        }

        float prod = 0;
        for(unsigned int i=0;i<width;i++)
        {
          prod+= get(line, i)*matrix.get(i, column);
        }
        return prod;
      }

      Matrix Matrix::operator*(const Matrix& matrix) const
      {
        if(width != matrix.height)
        {
          std::cerr << "Trying to multiply matrices of different size! " << width << " vs " << matrix.height << std::endl;
          exit(EXIT_FAILURE);
        }
        Matrix prod(height, matrix.width);
        for(unsigned int i=0;i<prod.height;i++)
        {
          for(unsigned int j=0;j<prod.width;j++)
          {
            prod.get(i,j) = lineColumnProduct(i, j, matrix);
          }
        }
        return prod;
      }

      Matrix::operator Matrix4x4() const
      {
        if(height != 4 || width != 4)
        {
          std::cerr << "Invalid conversion from matrix to matrix4x4!" << std::endl;
          exit(EXIT_FAILURE);
        }
        Matrix4x4 res;
        for(unsigned int i=0;i<4;i++)
        {
          for(unsigned int j=0;j<4;j++)
          {
            res.get(i,j) = get(i,j);
          }
        }
        return res;
      }

    }
  }
}
