#include "Inc/Motion_Planing.h"

#ifndef _GLIBCXX_MATH_H
#include <math.h>
#endif

u8 Scanned_Area[100];

f32 _param_a = 0;
f32 _param_b = 0;

void Set_Param_A(f32 new_value) { _param_a = new_value; }
void Set_Param_B(f32 new_value) { _param_b = new_value; }

/*
  uses _param_a as the radius of the two circles.
  uses _param_b as the x-coord of the saddle point.
*/
f32 PaB_Path(f32 x) {
  f32 y;

  // check if given x-coord is in the first circle
  if (x <= _param_b) {
    // x-coord is on the first circle
    y = -sqrt(pow(_param_a, 2) - pow(x - _param_a, 2));
  } else {
    // x-coord is on the second circle

    // theta is the angle between the two centers and the vertical axis
    f32 sin_theta = 1 - _param_b / _param_a;

    // x_2 is the x-coord of the center of the second circle
    f32 x_2 = _param_a - 2 * _param_a * sin_theta;

    // y_2 is the y-coord of the center of the second circle
    f32 y_2 = - 2 * _param_a * sqrt(1 - pow(sin_theta, 2));

    y = sqrt(pow(_param_a, 2) - pow(x - x_2, 2)) + y_2;
  }

  return y;
}

// Perpendicular backward Path
f32 PeB_Path(f32 x) {
  // TODO: implement this.
  return -1;
}

// Perpendicular forward Path
f32 PeF_Path(f32 x) {
  // TODO: implement this.
  return -1;
}

void Scan(u8 Scanned_Area);

void Plot_The_Path(Scenario_t Scenario, ... /*path */);
