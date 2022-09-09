#include "Vector2D.h"
#include <cmath>


Vector3D operator *(const Vector3D& vec, double a)
{
	return Vector3D(vec.x * a, vec.y * a, vec.z * a);

}

double Vector3D::norme()
{
	return sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));
}

Vector3D& Vector3D::operator -(const Vector3D& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}


Vector3D& Vector3D::operator+=(const Vector3D& rh)
{
	x += rh.x;
	y += rh.y;
	z += rh.z;
	return *this;

}

Vector3D Vector3D::operator /(double a)
{
	return Vector3D(x / a, y / a, z / a);
}

double Vector3D::operator *(const Vector3D& vec)
{
	return double(x*vec.x+y*vec.y+z*vec.z);
}

std::ostream& operator<<(std::ostream& os, const Vector3D& vec)
{
	return os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
}