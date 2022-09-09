#pragma once
#include "vector2D.h"
#include "Material.h"

//Creation of photon moving into the Scintillator
class Photon : public Material
{
private:

	Vector3D pos{ 0, 0, 0 };

	//Distance (in cm) traveled by the photon at each step 
	static constexpr float leng = 0.05;

public:

	Photon(float x, float y, float z);
	~Photon() = default;

	//Propagation of the photon within the material.
	void move(Material& Scint);

};

