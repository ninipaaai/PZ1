#include "Finite_Difference_Method.h"
#include <cmath>

namespace Com_Methods {
    //Трёхточечный левосторонний шаблон
    double Finite_Diffence_Method_Left(Com_Methods::Point p1, Com_Methods::Point p2, 
                                            Com_Methods::Point p3, double f1, double f2, double f3) {
        double h1 = p2.x()-p1.x(); double h2 = p3.x()-p2.x();
        double H = h1+h2; double r = h2/h1;
        double result = (-(2+r)*f1+pow((1+r), 2)*f2/r-f3/r)/H;
        return result;
    }

    double Finite_Diffence_Method_Right(Com_Methods::Point p1, Com_Methods::Point p2, 
                                            Com_Methods::Point p3, double f1, double f2, double f3) {
        double h1 = p2.x()-p1.x(); double h2 = p3.x()-p2.x();
        double H = h1+h2; double r = h2/h1;
        double result = (r*f1-pow((1+r), 2)*f2/r+(2+r)*f3/r)/H;
        return result;
    }
}