#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

namespace
{
    inline bool isEqual(double a, double b)
    {
        return fabs(a - b) <= numeric_limits<double>::epsilon();
    }
}

class Vector3D
{
private:
    double x;
    double y;
    double z;

public:
    Vector3D();
    Vector3D(double, double, double);
    ~Vector3D();

    inline double length();
    inline const Vector3D& normalize();

    inline Vector3D& operator+=(const Vector3D&);
    inline Vector3D& operator-=(const Vector3D&);
    inline Vector3D& operator*=(const double);

    inline const Vector3D operator-();
    inline const Vector3D operator+();

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
    Vector3D* v3 = new Vector3D(1, 3 ,4);
    Vector3D v4;

    v1 += +v2;
    v1 = -v1 + *v3;

    delete v3;

    return 0;
}



Vector3D::Vector3D() : x(0), y(0), z(0)
{
    cout << "[*] Vector3D()" << endl;
}

Vector3D::Vector3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_)
{
    cout << "[*] Vector3D(double x_, double y_, double z_)" << endl;
}

Vector3D::~Vector3D()
{
    cout << "[*] ~Vector3D()" << endl;
}



inline double Vector3D::length()
{
    return sqrt(x*x + y*y + z*z);
}

inline const Vector3D& Vector3D::normalize()
{
    double len = this->length();

    if (isEqual(len, 0))
        throw logic_error("Normalization error: null vector can't be normalized");

    x = x / len;
    y = y / len;
    z = z / len;
    return *this;
}



inline Vector3D& Vector3D::operator+=(const Vector3D &vec)
{
    return *this = *this + vec;
}

inline Vector3D& Vector3D::operator-=(const Vector3D& vec)
{
    return *this = *this - vec;
}

inline Vector3D& Vector3D::operator*=(const double a)
{
    return *this = a * *this;
}



inline const Vector3D Vector3D::operator-()
{
    return Vector3D(-this->x, -this->y, -this->z);
}

inline const Vector3D Vector3D::operator+()
{
    return *this;
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
    return isEqual(v1.x, v2.x)
        && isEqual(v1.y, v2.y)
        && isEqual(v1.z, v2.z);
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
