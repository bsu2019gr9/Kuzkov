#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

class Vector3D
{
private:
    double x;
    double y;
    double z;

public:
    Vector3D();
    Vector3D(double, double, double);

    inline double length();
    inline const Vector3D& normalize();

    inline Vector3D& operator+=(const Vector3D&);
    inline Vector3D& operator*=(const int);

    friend ostream& operator<<(ostream&, const Vector3D&);
    friend istream& operator>>(istream&, Vector3D&);

    friend inline bool operator==(const Vector3D&, const Vector3D&);
    friend inline bool operator!=(const Vector3D&, const Vector3D&);

    friend inline const Vector3D operator+(const Vector3D&, const Vector3D&);
    friend inline const Vector3D operator-(const Vector3D&, const Vector3D&);

    friend inline double operator*(const Vector3D&, const Vector3D&);
    friend inline const Vector3D operator*(const double, const Vector3D&);
    friend inline const Vector3D operator*(const Vector3D&, const double);

    friend inline const Vector3D vecMult(const Vector3D&, const Vector3D&);
};

int main()
{
    Vector3D v1(1, 0, 0);
    Vector3D v2(1, -1, 1);

    cout << v1.length() << endl;
    cout << vecMult(v1, v2) << endl;

    cout << v1 << endl;
    cout << v2 << endl;

    cout << v1.normalize() << endl;

    return 0;
}

Vector3D::Vector3D() : x(0), y(0), z(0)
{}

Vector3D::Vector3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_)
{}

double Vector3D::length()
{
    return sqrt(x*x + y*y + z*z);
}

const Vector3D& Vector3D::normalize()
{
    double len = this->length();
    x = x / len;
    y = y / len;
    z = z / len;
    return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D &vec)
{
    return *this = *this + vec;
}

Vector3D& Vector3D::operator*=(const int a)
{
    return *this = a * *this;
}

ostream& operator<<(ostream &os, const Vector3D &vec)
{
    return os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
}

istream& operator>>(istream &is, Vector3D &vec)
{
    return is >> vec.x >> vec.y >> vec.z;
}

inline bool operator==(const Vector3D &v1, const Vector3D &v2)
{
    return fabs(v1.x - v2.x) < numeric_limits<double>::epsilon()
        && fabs(v1.y - v2.y) < numeric_limits<double>::epsilon()
        && fabs(v1.z - v2.z) < numeric_limits<double>::epsilon();
}

inline bool operator!=(const Vector3D &v1, const Vector3D &v2)
{
    return !(v1 == v2);
}

inline const Vector3D operator+(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline const Vector3D operator-(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline double operator*(const Vector3D &v1, const Vector3D &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline const Vector3D operator*(const double a, const Vector3D &vec)
{
    return Vector3D(vec.x * a, vec.y * a, vec.z * a);
}

inline const Vector3D operator*(const Vector3D &vec, const double a)
{
    return a * vec;
}

inline const Vector3D vecMult(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.y * v2.z - v1.z * v2.y,
                    v1.z * v2.x - v1.x * v2.z,
                    v1.x * v2.y - v1.y * v2.x);
}