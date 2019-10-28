#ifndef VECTOR_H
#define VECTOR_H

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      class Vector
      {
      private:
        float* data;
        unsigned int size;
      public:
        Vector(unsigned int);
        ~Vector();
        Vector(const Vector&);
        Vector& operator=(const Vector&);
        float& get(unsigned int) const;
        void setAll(float);
        float getLength() const;
        void setLength(float);
        void normalize();
        void print() const;

        void operator*=(float);
      };
    }
  }
}

#endif
