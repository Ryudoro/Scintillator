#pragma once
#include <ostream>


//Vector 3D with +, * and - operation, and norm.
struct Vector3D
{


		double x, y, z;
		Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}


		Vector3D& operator -(const Vector3D& vec);
		double operator *(const Vector3D& vec);
		Vector3D operator /(double a);
		Vector3D& operator+=(const Vector3D& rh);


		double norme();

};
	
Vector3D operator *(const Vector3D& vec, double a);
std::ostream& operator<<(std::ostream& os, const Vector3D& vec);


