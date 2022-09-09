#include "Vector2D.h"
#include "Material.h"
#include "const.h"
#include <cmath>
#include <iostream>

//Function use for the 45 degree cut
bool line(float a, float b, float x, float y)
{
	return a * x + b * y < 0;
}


Material::Material() { }


//Checking if pos is into the scintillator.
bool Material::IsIn(const Vector3D& pos)
{
	bool is = pos.x > x_min && pos.x < x_max && pos.y > y_min && pos.y < y_max && pos.z > z_min && pos.z < z_max
		&& line(max_l_y, -max_l_x, (pos.x - x_max), (pos.y - y2_max)) &&
		!line(max_l_y, -min_l_x, (pos.x - x_min), (pos.y - y2_max));


	return is;
}

//All possible case of reflexion into the scintillator.
double Material::Reflex(const Vector3D& pos, double theta, double phi, const Vector3D& pos_0)
{
	int temp = 0;

	//Left 45 degree cut.
	if (!line(max_l_y, -max_l_x, (pos.x - x_max), (pos.y - y2_max)))
	{

		double angle = Material::angle(pos, pos_0, temp);

		if(line(max_l_x, max_l_y, pos_0.x-pos.x, pos_0.y-pos.y))
		{
			std::cout << 5 * pi / 4 - angle << std::endl;
			if (5 * pi / 4 - angle > 0 && 5 * pi / 4 - angle < pi)
			{
				return 5 * pi / 4;
			}
			return 5 * pi / 4 + angle;
		}

		if (!line(max_l_x, max_l_y, pos_0.x - pos.x, pos_0.y - pos.y))
		{
			return 5 * pi / 4 - angle;
		}

	}

	//Right 45 degree cut.
	if (line(max_l_y, -min_l_x, (pos.x - x_min), (pos.y - y2_max)))
	{

		double angle = Material::angle(pos, pos_0, temp);

		if (line(min_l_x, max_l_y, pos_0.x - pos.x, pos_0.y - pos.y))
		{
			return 7 * pi / 4 + angle;
		}

		if (!line(min_l_x, max_l_y, pos_0.x - pos.x, pos_0.y - pos.y)) 
		{
			return 7 * pi / 4 - angle;
		}

	}

	//All other possible case of reflexion on the edge.
	if ((pos.y > pos_0.y && pos.x >= x_max &&
		pos.z > z_min && pos.z < z_max))
	{
		return pi - theta;
	}
	else if ((pos.y < pos_0.y && pos.x >= x_max ||
		pos.x > pos_0.x && pos.y <= y_min ||
		pos.x < pos_0.x && pos.y <= y_min ||
		pos.x < pos_0.x && pos.y >= y_max ||
		pos.x > pos_0.x && pos.y >= y_max) &&
		pos.z > z_min && pos.z < z_max)
	{
		return 2 * pi - theta;
	}
	else if (pos.y < pos_0.y && pos.x <= x_min)
	{
		return 3 * pi - theta;
	}
	else if (pos.y > pos_0.y && pos.x <= x_min)
	{
		return pi - theta;
	}
	else if (pos.z >= z_max || pos.z <= z_min)
	{
		return pi - phi;
	}
	else
	{

		return -theta;
	}
	//possible mistake here. Or very odd case.
	std::cout << "error" << std::endl;
	return -theta;
}

//transmission into the scintillator. As we didn't use it for our simulation, not developped. If you want to use it, just use snell-descartes law.
double Material::Transm(const Vector3D& pos, double theta, double phi)
{

	return theta;
}

//calculation of the angle between the normal of the edge of the scintillator and the incident beam.
double Material::angle(const Vector3D& pos, const Vector3D& pos_0, int& part)
{
	if (pos.z >= z_max)
	{
		Vector3D pos_zmax{pos_0.x - pos.x,pos_0.y - pos.y ,pos_0.z - pos.z };
		Vector3D zmax{ 0.0, 0.0, -1.0 };
		part = 7;
		return acos((pos_zmax * zmax) / (pos_zmax.norme() * zmax.norme()));
	}
	if (pos.z <= z_min)
	{
		Vector3D pos_zmin{pos_0.x - pos.x ,pos_0.y - pos.y ,pos_0.z - pos.z };
		Vector3D zmin{ 0.0, 0.0, 1.0 };
		part = 8;
		return acos((pos_zmin * zmin) / (pos_zmin.norme() * zmin.norme()));
	}
	if (!line(max_l_y, -max_l_x, (pos.x - x_max), (pos.y - y2_max)))
	{
		Vector3D pos_corner_right{pos_0.x - pos.x ,pos_0.y - pos.y ,pos_0.z - pos.z};
		Vector3D corner_right{ -max_l_y, max_l_x, 0 };
		part = 4;
		return acos((pos_corner_right * corner_right) / (pos_corner_right.norme() * corner_right.norme()));
	}

	if (line(max_l_y, -min_l_x, (pos.x - x_min), (pos.y - y2_max)))
	{
		Vector3D pos_corner_right{pos_0.x - pos.x ,pos_0.y - pos.y ,pos_0.z - pos.z };
	Vector3D corner_right{ max_l_y, -min_l_x, 0 };
	part = 2;
	return acos((pos_corner_right * corner_right) / (pos_corner_right.norme() * corner_right.norme()));

	}
	if (pos.x <= x_min)
	{
		Vector3D pos_xmin{pos_0.x - pos.x ,pos_0.y - pos.y ,pos_0.z - pos.z };
		part = 1;
		return acos(pos_xmin.x / pos_xmin.norme());
	}
	if (pos.x >= x_max)
	{
		Vector3D pos_xmax{pos_0.x - pos.x ,pos_0.y - pos.y ,pos_0.z - pos.z };
		part = 5;
		return acos((-1.0)*pos_xmax.x / pos_xmax.norme());
	}
	if (pos.y <= y_min)
	{
		Vector3D pos_ymin{pos_0.x - pos.x ,pos_0.y - pos.y ,pos_0.z - pos.z };
		part = 6;
		return acos(pos_ymin.y / pos_ymin.norme());
	}
	if (pos.y >= y_max)
	{
		Vector3D pos_ymax{pos_0.x - pos.x ,pos_0.y - pos.y ,pos_0.z - pos.z };
		part = 3;
		return acos((-1.0) * pos_ymax.y / pos_ymax.norme());
	}
	return 0;
}