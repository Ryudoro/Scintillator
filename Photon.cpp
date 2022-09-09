#pragma once
#include <cstdlib>
#include <math.h>
#include <vector>
#include "Material.h"
#include "Photon.h"
#include <fstream>
#include "const.h"


//creation of the photon at the position of the muon
Photon::Photon(float x, float y, float z)
{

	pos.x = x;
	pos.y = y;
	pos.z = z;
}


void Photon::move(Material& Scint)
{

	//Chance will be randomly changed to see if the photon is absorbed or reflected.
	double chance = 0.0;

	//Generation of random spherical coordinate (isotropic production of photon).
	double theta = double(rand()) / RAND_MAX * 2 * pi;
	double phi = double(rand()) / RAND_MAX * pi;

	//Vector storing the position of the photon when touching the edge of the scintillator.
	std::vector <Vector3D> red;

	//Vector storing the distance traveled by the photon until its absorption by the material.
	std::vector <double> Path;

	//Storing the initial position of the photon.
	Vector3D pos_0 = pos;
	int part = 0;

	//Creating variable storing the distance traveled by the photon between each reflexion (each time store into the Path vector).
	double path = 0;

	//Storing the current position into the red vector.
	red.emplace_back(pos);

	//Considering absorption possible within the material.
	double stop = 0;

	//Loop until the photon is absorbed.
	while (chance < absor)
	{

		//Evolution of the photon within the scintillator until it hits an edge.
		while (Scint.IsIn(pos))
		{
			pos.x += leng * cos(theta) * sin(phi);
			pos.y += leng * sin(theta) * sin(phi);
			pos.z += leng * cos(phi);
			path += leng;
		}
		
		//Chance of being absorbed by the wrapping (in addition to chance which described the absorption by the scintillator)
		double chance2 = double(rand()) / RAND_MAX;



		//Angle between the incident photon and the normal to the plane of the interface
		double a = pi/2-Scint.angle(pos, pos_0, part);

		//If the angle is larger than the critical angle, the photon CAN be absorbed. Otherwise totally reflected.
		if (a > Scint.critangle)
		{
			chance = double(rand()) / RAND_MAX;
		}


		//Simulation of the absorption within the scintillator. If the photon make a larger distance, it get more chance to be absorbed. Depend on the Light attenuation lenght of the scintillator.
		stop = exp( -path/Lal);


		//Absorption is random but become more and more possible as the photon continues its journey.
		double chancestop = double(rand()) / RAND_MAX;

		//stop if absorbed
		if (chancestop > stop)
		{
			break;
		}

		//Storing new position of the photon as it hits and edge. Only after testing if the photon is absorbed by the material.
		red.emplace_back(pos);

		//Reflexion on the edge of the scintillator. phi change if the photon hit the top or the bottom. theta change if the photon hit the side.
		if (pos.z > z_min && pos.z < z_max)
			theta = Scint.Reflex(pos, theta, phi, pos_0);
		else
			phi = Scint.Reflex(pos, theta, phi, pos_0);

		//Going back into the scintillator if the photon touched the corner (with the 45 degree cut).
		if (!(max_l_y * (pos.x - x_max) - max_l_x * (pos.y - y2_max) < 0) &&
			max_l_y * (pos.x - x_min) - min_l_x * (pos.y - y2_max) < 0)
		{
			pos.x += 2*leng * cos(theta) * sin(phi);
			pos.y += 2*leng * sin(theta) * sin(phi);
			pos.z += 2*leng * cos(phi);
		}

		//Going back into the scintillator if the photon touched the normal edge.
		if (pos.x <= x_min)
			pos.x = x_min + 0.00001;
		if (pos.x >= x_max)
			pos.x = x_max - 0.00001;
		if (pos.y <= y_min)
			pos.y = y_min + 0.00001;
		if (pos.y >= y_max)
			pos.y = y_max - 0.00001;
		if (pos.z <= z_min)
			pos.z = z_min + 0.00001;
		if (pos.z >= z_max)
			pos.z = z_max - 0.00001;

		//The current position on the edge become the starting point for the new propagation of the photon.
		pos_0 = pos;

		//Checking if the photon is really back into the scintillator, in order to avoid any problem.
		if (!Scint.IsIn(pos))
		{
			break;
		}

	}
	
	//Storing the data of the path travelled by the photon into a file (in order to then analyse it).
	std::fstream fichier2("path.txt", std::ios::app);
	fichier2 << path << std::endl;
	fichier2.close();

	//Storing the data of all the reflexion of the photon into another file. Same goal.
	std::fstream fichier("photons.txt", std::ios::app);
	for (unsigned int i = 0; i < red.size(); i++)
	{
		fichier << red[i].x << ", " << red[i].y << ", " << red[i].z << std::endl;
	}
	//Adding : separation in the file to distinguish each photon.
	fichier << ":" << std::endl;
	fichier.close();
}