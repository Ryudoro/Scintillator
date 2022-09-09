#pragma once

//Scintillator of 50 x 50 cm, and 1 cm of height.

//Maximum position of the scintillator.
constexpr float x_max = 50.0;
constexpr float y_max = 50.0;
constexpr float z_max = 1.0;

//Position of right cut on the scintillator.
constexpr float x2_max = 49.29;
constexpr float y2_max = 49.29;

//Minimum position of the scintillator.
constexpr float x_min = 0.0;
constexpr float y_min = 0.0;
constexpr float z_min = 0.0;

//Position of left cut on the scintillator.
constexpr float x2_min = 0.71;
constexpr float y2_min = 0.0;

//Chance to being reflected by the scintillator or the wrapping.
constexpr double absor= 0.9;
constexpr float absmax = 0.94;

//Pi constant.
constexpr double pi = 3.141592654;

//Values for the line equation.
constexpr float min_l_x = x2_min - x_min;
constexpr float min_l_y = y_max - y2_max;

constexpr float max_l_x = x2_max - x_max;
constexpr float max_l_y = y_max - y2_max;