#pragma once
#include "vector2D.h"
#include <cmath>

class Material
{
protected:


	//Light attenuation lenght for scintillator EJ-200
	double Lal = 425;

public:

	//Considering n=1.0 for the air, and 1.58 for the refractive index of the scintillator.
	double critangle = asin(1.0 / 1.58);

	Material();
	~Material() = default;

	//Checking if the element is indeed into the scintillator.
	bool IsIn(const Vector3D& pos);

	//Finding the angle between the normal of an edge of the scintillator and the incident beam.
	double angle(const Vector3D& pos, const Vector3D& pos_0, int& part);
	//Reflexion of the photon.
	double Reflex(const Vector3D& pos, double theta, double phi, const Vector3D& pos_0);
	//Transmission of the photon.
	double Transm(const Vector3D& pos, double theta, double phi);
};

