#pragma once

#include "vector2D.h"
#include "const.h"


//Class created to simulate the propagation of a muon throught the scintillator.
class Muons : public Material
{
private:

	//distance (in cm) traveled by the muon at each step. 
	static constexpr float lengm = 0.01;

	//As cosmic muons are coming from the sky, we start the propagation on the top of the scintillator.
	Vector3D pos{ 0, 0, z_max-lengm };

public:
	Muons();
	~Muons() = default;

	//propagation of the muon.
	void beam(Material& Scint);
};



