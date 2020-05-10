#include <iostream>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>

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

    inline double getX();
    inline double getY();
    inline double getZ();

    inline double length();
    inline const Vector3D& normalize();
    inline Vector3D getNormalized();
    inline Vector3D project(const Vector3D&);

    inline Vector3D& operator+=(const Vector3D&);
    inline Vector3D& operator-=(const Vector3D&);
    inline Vector3D& operator*=(const double);
    inline Vector3D& operator/=(const double);

    inline Vector3D operator-();
    inline Vector3D operator+();

    friend ostream& operator<<(ostream&, const Vector3D&);
    friend istream& operator>>(istream&, Vector3D&);

    friend inline bool operator==(const Vector3D&, const Vector3D&);
    friend inline bool operator!=(const Vector3D&, const Vector3D&);

    friend inline Vector3D operator+(const Vector3D&, const Vector3D&);
    friend inline Vector3D operator-(const Vector3D&, const Vector3D&);

    friend inline double operator*(const Vector3D&, const Vector3D&);
    friend inline Vector3D operator*(const double, const Vector3D&);
    friend inline Vector3D operator*(const Vector3D&, const double);
    friend inline Vector3D operator/(const Vector3D&, const double);

    friend inline Vector3D vecMult(const Vector3D&, const Vector3D&);
};

Vector3D getResultVector(Vector3D*, Vector3D*);
void setRandomVectors(Vector3D*, Vector3D*);

int main()
{
    srand(time(NULL));  

    const int N = 2;

    Vector3D* vecArr = new Vector3D[N];
    setRandomVectors(vecArr, vecArr + N);

    Vector3D result = getResultVector(vecArr, vecArr + N);
    cout << result << endl;

    delete[] vecArr;

    return 0;
}



Vector3D getResultVector(Vector3D *beg, Vector3D *end)
{
    Vector3D result;

    for (; beg < end; beg++)
        result += *beg;
    
    return result;
}

void setRandomVectors(Vector3D *beg, Vector3D *end)
{
    for (; beg < end; beg++)
        *beg = Vector3D(rand() % 100, rand() % 100, rand() % 100);
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



inline double Vector3D::getX()
{
    return x;
}

inline double Vector3D::getY()
{
    return y;
}

inline double Vector3D::getZ()
{
    return z;
}



inline double Vector3D::length()
{
    return sqrt(x*x + y*y + z*z);
}

inline const Vector3D& Vector3D::normalize()
{
    return *this = this->getNormalized();
}

inline Vector3D Vector3D::getNormalized()
{
    double len = this->length();

    if (isEqual(len, 0))
        throw logic_error("Normalization error: null vector can't be normalized");

    return Vector3D(x / len, y / len, z / len);
}

inline Vector3D Vector3D::project(const Vector3D &vec)
{
    try
    {
        Vector3D normal = this->getNormalized();

        return normal * (vec * normal);
    }
    catch (logic_error err)
    {
        throw logic_error("Projection error: vector can't be projected onto null vector");
    }
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

inline Vector3D& Vector3D::operator/=(const double a)
{
    return *this = *this / a;
}



inline Vector3D Vector3D::operator-()
{
    return Vector3D(-this->x, -this->y, -this->z);
}

inline Vector3D Vector3D::operator+()
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



inline Vector3D operator+(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vector3D operator-(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}



inline double operator*(const Vector3D &v1, const Vector3D &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vector3D operator*(const double a, const Vector3D &vec)
{
    return Vector3D(vec.x * a, vec.y * a, vec.z * a);
}

inline Vector3D operator*(const Vector3D &vec, const double a)
{
    return a * vec;
}

inline Vector3D operator/(const Vector3D &vec, const double a)
{
    return Vector3D(vec.x / a, vec.y / a, vec.z / a);
}



inline Vector3D vecMult(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.y * v2.z - v1.z * v2.y,
                    v1.z * v2.x - v1.x * v2.z,
                    v1.x * v2.y - v1.y * v2.x);
}
