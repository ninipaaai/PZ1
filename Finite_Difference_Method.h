#pragma once

#include "Point.h"
#include <vector>

namespace Com_Methods {
    double Finite_Diffence_Method_Left(Com_Methods::Point p1, Com_Methods::Point p2,
        Com_Methods::Point p3, double f1, double f2, double f3);
    double Finite_Diffence_Method_Right(Com_Methods::Point p1, Com_Methods::Point p2,
        Com_Methods::Point p3, double f1, double f2, double f3);
}