#pragma once
#include <cstdlib>
#include <math.h>
#include <vector>
#include "Material.h"
#include "Photon.h"
#include <fstream>
#include "const.h"
#include "Muons.h"
#include <cassert>

Muons::Muons()
{

	//Choosing a random y position for the incident muon.
	pos.y = double(rand()) / RAND_MAX * y_max;
	
	//Choosing a random x position for the incident muon. Here, as the corner have 45 cut, we cannot generate muon of this corners.
	if (pos.y < y2_max)
		pos.x = double(rand()) / RAND_MAX * x_max;
	else
		pos.x = double(rand()) / RAND_MAX * (x2_max-x2_min)+x2_min;
	
}

void Muons::beam(Material& Scint)
{

	//Adding ; separation in the file to distinguish each muon.
	std::fstream fichier("photons.txt", std::ios::app);
	fichier << ";" << std::endl;
	fichier.close();

	//propagation of the muon until its reach the bottom of the scintillator.
	while (pos.z > z_min)
	{
		//Creation of a photon.
		Photon p(pos.x, pos.y, pos.z);

		//Checking if the photon is indeed into the scintillator.
		assert(Scint.IsIn(pos));

		//Propagation of the photon within the scintillator.
		p.move(Scint);

		//Muon going one step further. We consider only normal incidence ! If you want to change that, just generate random angle like for the photon, but with phi [pi/2,pi]
		pos.z -= lengm;

	}

}









