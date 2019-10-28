#include "Vector.h"

#include <iostream>
#include <stdlib.h>
#include <math.h>

namespace gt
{
  namespace doubovik
  {
    namespace math
    {

      Vector::Vector(unsigned int size)
      {
        this->size = size;
        data = new float[size];
        setAll(0);
      }

      Vector::~Vector()
      {
        delete [] data;
      }

      Vector::Vector(const Vector& vector)
      {
        size = vector.size;
        data = new float[size];

        for(unsigned int i=0;i<size;i++)
        {
          *(data + i) = *(vector.data + i);
        }
      }

      Vector& Vector::operator=(const Vector& vector)
      {
        delete [] data;

        size = vector.size;
        data = new float[size];

        for(unsigned int i=0;i<size;i++)
        {
          *(data + i) = *(vector.data + i);
        }
        return *this;
      }

      float& Vector::get(unsigned int i) const
      {
        if(i >= size)
        {
          std::cerr << "Error: index i = " << i << " out bounds of vector, size = " << size << std::endl;
          exit(EXIT_FAILURE);
        }
        return *(data + i);
      }

      void Vector::setAll(float x)
      {
        for(unsigned int i=0;i<size;i++)
        {
          get(i) = x;
        }
      }

      float Vector::getLength() const
      {
        float length = 0;
        for(unsigned int i=0;i<size;i++)
        {
          length+=get(i)*get(i);
        }
        return sqrt(length);
      }

      void Vector::setLength(float x)
      {
        if(x == 0)
        {
          setAll(0);
        }
        else
        {
          float length = getLength();
          if(length != 0)
          {
            (*this)*=(x/length);
          }
        }
      }

      void Vector::normalize()
      {
        setLength(1);
      }

      void Vector::print() const
      {
        std::cout << "-----" << std::endl;
        for(unsigned int i=0;i<size;i++)
        {
          std::cout << "[" << get(i) << "]" << std::endl;
        }
        std::cout << "-----" << std::endl;
      }

      void Vector::operator*=(float x)
      {
        for(unsigned int i=0;i<size;i++)
        {
          get(i)*=x;
        }
      }
    }
  }
}
