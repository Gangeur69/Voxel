#ifndef MATRIX_H
#define MATRIX_H

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      class Matrix4x4;

      class Matrix
      {
      protected:
        float** data;
        unsigned int height;
        unsigned int width;
        float lineColumnProduct(unsigned int, unsigned int, const Matrix&) const;
      public:
        Matrix(unsigned int, unsigned int);
        ~Matrix();
        Matrix(const Matrix&);
        Matrix& operator=(const Matrix&);
        float& get(unsigned int, unsigned int) const;
        void setAll(float);
        void setDiag(float);
        void print() const;
        void toArray(float*) const;
        void swapLines(unsigned int, unsigned int);
        void multiplyLine(unsigned int, float);
        void addLineToLine(float, unsigned int, unsigned int);

        Matrix operator*(const Matrix&) const;
        operator Matrix4x4() const;
      };
    }
  }
}

#endif
