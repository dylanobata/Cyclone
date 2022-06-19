#pragma once

#include <math.h>
#include "precision.h"

namespace cyclone {
    typedef float real; // Provides real number precision. Default: float but can change to double if higher precision is needed
    /* 
     * Holds a vector in three dimensions. Four data members are allocated
     * to ensure alignment in an array.
    */
    class Vec3 {
    public:
        real x; real y; real z;
        Vec3() : x(0), y(0), z(0) {}
        Vec3(const real x, const real y, const real z)
            : x(x), y(y), z(z) {}

        // changes direction of vector
        void invert()
        {
            x = -x;
            y = -y;
            z = -z;
        }

        // gets the magnitude of this vector
        real Magnitude() const
        {
            return real_sqrt(x*x + y*y + z*z);
        }

        // gets the square magnitude of this vector
        real squareMagnitude() const
        {
            return x*x + y*y + z*z;
        }
        
        // turns a non-zero vector into a vector of unit length
        void normalize()
        {
            real len = Magnitude();
            if (len > 0)
            {
                *this *= ((real)len) / len;
            }
        }
        
        // Assigns vector to this
        void operator=(const Vec3 &vec)
        {
            x = vec.x;
            y = vec.y;
            z = vec.z;
        }

        // Multiplies this vector by the given scalar
        void operator*=(const real scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
        }

        // Returns a copy of this vector scaled by scalar
        Vec3 operator*(const real scalar) const
        {
            return Vec3(x*scalar, y*scalar, z*scalar);
        }

        // Adds the given vector to this
        void operator+=(const Vec3 &vec)
        {
            x += vec.x;
            y += vec.y;
            z += vec.z;

        }
        
        // Adds and returns given vector to this
        Vec3 operator+(const Vec3 &vec) const
        {
            return Vec3(x+vec.x, y+vec.y, z+vec.z);
        }

        // Subtracts given vector from this
        void operator-=(const Vec3 &vec)
        {
            x -= vec.x;
            y -= vec.y;
            z -= vec.z;
        }

        // Subtracts and returns given vector to this
        Vec3 operator-(const Vec3 &vec) const
        {
            return Vec3(x-vec.x, y-vec.y, z-vec.z);
        }
        
        // Performs linear combination
        void addScaledVec(const Vec3 &vec, real scalar)
        {
            *this += vec*scalar;
        }
        
        // Performs component based multiplication on this
        void componentProduct(const Vec3 &vec)
        {
            x *= vec.x;
            y *= vec.y;
            z *= vec.z;
        }
        
        // Performs and returns component based multiplication to this
        Vec3 componentProductUpdate(const Vec3 &vec) const
        {
            return Vec3(x*vec.x, y*vec.y, z*vec.z);
        }

        // Returns the dot product of two same sized vectors
        real operator*(const Vec3 &vec) const
        {
            return x*vec.x + y*vec.y + z*vec.z;
        }

        Vec3 crossProduct(const Vec3 &vec) const
        {
            return Vec3(y*vec.z-z*vec.y,
                        z*vec.x-x*vec.z,
                        x*vec.y-y*vec.x);
        }

        void crossProductUpdate(const Vec3 &vec)
        {
            *this = crossProduct(vec);
        }

        void makeOrthonormalBasis(Vec3 *a, Vec3 *b, Vec3 *c)
        {
            a->normalize();
            *c = a->crossProduct(*b);

            if (c->squareMagnitude() == 0.0) return; // Or generate error
            c->normalize();
            *b = c->crossProduct(*a);
        }

    private:
        real padding; // ensure 4 word alignment
    };
}
