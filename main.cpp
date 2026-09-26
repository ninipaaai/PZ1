#include <iostream>
#include <vector>                          
#include "Point.h"
#include "Grid_1D.h"
#include "Cubic_Interpolation_Spline_1D.h"
#include "Finite_Difference_Method.h"
#include "cmath"
#include <iomanip>
#include <windows.h>
#include <algorithm>
using namespace std;

double f(Com_Methods::Point p) { //f(x)=sin(x)
    double x = p.x();
    return sin(x);
}

double f_der(Com_Methods::Point p) { //первая производная
    double x = p.x();
    return cos(x);
}

int main() {
    SetConsoleOutputCP(65001);  
    SetConsoleCP(65001);
    const double a = 0.1; //вариант 13
    const double b = 0.44;
    const double eps = 0.01;

    //Задание равномерных сеток
    vector<Com_Methods::Point> grid1 = Com_Methods::Grid_1D(a, b, 7);
    vector<Com_Methods::Point> grid2 = Com_Methods::Grid_1D(a, b, 14);
    vector<Com_Methods::Point> grid3 = Com_Methods::Grid_1D(a, b, 28);
    vector<double> valuesF1, valuesF2, valuesF3; //Значение функции в узлах сетки
    valuesF1.reserve(3); valuesF2.reserve(5); valuesF3.reserve(9);
    for (int i = 0; i<grid1.size(); i++) {
        valuesF1.emplace_back(f(grid1[i]));
    }
    for (int i=0; i<grid2.size(); i++) {
        valuesF2.emplace_back(f(grid2[i]));
    }
    for (int i=0; i<grid3.size(); i++) {
        valuesF3.emplace_back(f(grid3[i]));
    }

    //Вывод сетки
    const int w = 14;
    cout << setw(w*1.4) << "Сетка 1" << setw(w*1.4) << "Сетка 2" << setw(w*1.4) << "Сетка 3" << endl;
    for (int i=0; i<grid3.size(); i++) {
        if (i<grid1.size()) cout << scientific << setw(w) << grid1[i].x() << scientific <<setw(w) << grid2[i].x() << scientific << setw(w) << grid3[i].x() << endl;
        else if (i<grid2.size()) cout << setw(w) << " " << setw(w) << grid2[i].x() << setw(w) << grid3[i].x() << endl;
        else cout << setw(w) << " " << setw(w) << " " << setw(w) << grid3[i].x() << endl;
    }
    cout << endl;
    
    vector<Com_Methods::Point> dots = Com_Methods::Grid_1D(a+0.0125, b-0.0125, 10); //точки отличные от узловых
    vector<double> valuesDots1, valuesDots2, valuesDots3;
    valuesDots1.reserve(dots.size()); valuesDots2.reserve(dots.size()); valuesDots3.reserve(dots.size());
    for (int i=0; i<dots.size(); i++) {
        valuesDots1.emplace_back(f(dots[i]));
        valuesDots2.emplace_back(f_der(dots[i]));
        valuesDots3.emplace_back((-1)*f(dots[i]));
    }
    cout << "Значения функции f(x)=sin(x) и её первых двух производных в точках, отличных от узловых" << endl;
    cout << setw(w) << "x" << setw(w) << "f(x)" << setw(w) << "f`(x)" << setw(w) << "f``(x)" << endl;
    for (int i=0; i<dots.size(); i++) {
        cout << scientific << setw(w) << dots[i].x() << scientific << setw(w) << valuesDots1[i] << scientific << setw(w) << valuesDots2[i] << scientific <<setw(w) << valuesDots3[i] << endl;
    }
    cout << endl;

    Com_Methods::Cubic_Interpolation_Spline_1D S; //Создание сплайна

    S.Update_Spline(grid1, valuesF1);
    vector<double> valuesS; //значение сплайна в точках, отличающихся от узловых
    vector<double> valuesS1; //значение первой производной
    vector<double> valuesS2; //значение второй производной
    double res[3];
    for (int i=0; i<dots.size(); i++) {
        S.Get_Value(dots[i], res);
        valuesS.push_back(res[0]);
        valuesS1.push_back(res[1]);
        valuesS2.push_back(res[2]);
    }

    //Вывод значений сплайна
    cout << "Значение сплайна, построенного по GRID1, и его первых двух производных в точках, отличный от узловых" << endl;
    cout << setw(w) << "x" << setw(w) << "S(x)" << setw(w) << "S`(x)" << setw(w) << "S``(x)" << endl;
    double max_delta1 = 0.0, max_delta2 = 0.0, max_delta3 = 0.0; //Погрешность
    for (int i = 0; i<dots.size(); i++) {
        cout << scientific << setw(w) << dots[i].x() << scientific << setw(w) << valuesS[i] << scientific << setw(w) << valuesS1[i] << scientific << setw(w) << valuesS2[i] << endl;
        max_delta1 = max(max_delta1, fabs(valuesS[i]-valuesDots1[i]));
        max_delta2 = max(max_delta2, fabs(valuesS1[i]-valuesDots2[i]));
        max_delta3 = max(max_delta3, fabs(valuesS2[i]-valuesDots3[i]));
    }
    cout << setw(w) << "Максимальная абсолютная разность по сравнению с теоритической фунцией:" << endl;
    cout << scientific << setw(w) << " " << scientific << setw(w) << max_delta1 << scientific << setw(w) << max_delta2 << scientific << setw(w) << max_delta3 << endl << endl;

    //Теперь для второй сетки
    S.Update_Spline(grid2, valuesF2);
    valuesS.clear(); valuesS1.clear(); valuesS2.clear();
    for (int i=0; i<dots.size(); i++) {
        S.Get_Value(dots[i], res);
        valuesS.push_back(res[0]);
        valuesS1.push_back(res[1]);
        valuesS2.push_back(res[2]);
    }

    //Вывод значений сплайна
    cout << "Значение сплайна, построенного по GRID2, и его первых двух производных в точках, отличный от узловых" << endl;
    cout << setw(w) << "x" << setw(w) << "S(x)" << setw(w) << "S`(x)" << setw(w) << "S``(x)" << endl;
    max_delta1 = 0.0; max_delta2 = 0.0; max_delta3 = 0.0;
    for (int i = 0; i<dots.size(); i++) {
        cout << scientific << setw(w) << dots[i].x() << scientific << setw(w) << valuesS[i] << scientific << setw(w) << valuesS1[i] << scientific << setw(w) << valuesS2[i] << endl;
        max_delta1 = max(max_delta1, fabs(valuesS[i]-valuesDots1[i]));
        max_delta2 = max(max_delta2, fabs(valuesS1[i]-valuesDots2[i]));
        max_delta3 = max(max_delta3, fabs(valuesS2[i]-valuesDots3[i]));
    }
    cout << setw(w) << "Максимальная абсолютная разность по сравнению с теоритической фунцией:" << endl;
    cout << scientific << setw(w) << " " << scientific << setw(w) << max_delta1 << scientific << setw(w) << max_delta2 << scientific << setw(w) << max_delta3 << endl << endl;

    //Теперь для третей сетки
    S.Update_Spline(grid3, valuesF3);
    valuesS.clear(); valuesS1.clear(); valuesS2.clear();
    for (int i=0; i<dots.size(); i++) {
        S.Get_Value(dots[i], res);
        valuesS.push_back(res[0]);
        valuesS1.push_back(res[1]);
        valuesS2.push_back(res[2]);
    }

    //Вывод значений сплайна
     cout << "Значение сплайна, построенного по GRID3, и его первых двух производных в точках, отличный от узловых" << endl;
    cout << setw(w) << "x" << setw(w) << "S(x)" << setw(w) << "S`(x)" << setw(w) << "S``(x)" << endl;
    max_delta1 = 0.0; max_delta2 = 0.0; max_delta3 = 0.0;
    for (int i = 0; i<dots.size(); i++) {
        cout << scientific << setw(w) << dots[i].x() << scientific << setw(w) << valuesS[i] << scientific << setw(w) << valuesS1[i] << scientific << setw(w) << valuesS2[i] << endl;
        max_delta1 = max(max_delta1, fabs(valuesS[i]-valuesDots1[i]));
        max_delta2 = max(max_delta2, fabs(valuesS1[i]-valuesDots2[i]));
        max_delta3 = max(max_delta3, fabs(valuesS2[i]-valuesDots3[i]));
    }
    cout << setw(w) << "Максимальная абсолютная разность по сравнению с теоритической фунцией:" << endl;
    cout << scientific << setw(w) << " " << scientific << setw(w) << max_delta1 << scientific << setw(w) << max_delta2 << scientific << setw(w) << max_delta3 << endl << endl;


    //Пункт 4: вычисление первой и второй производной
    vector<double> der1, der2; //Значение первой и второй производной с помощью метода конечных разностей
    for (int i = 0; i<grid3.size(); i++) { //первая производная
        if (i <= grid3.size()-3) der1.push_back(Com_Methods::Finite_Diffence_Method_Left(grid3[i], grid3[i+1], grid3[i+2], valuesF3[i], valuesF3[i+1], valuesF3[i+2]));
        else der1.push_back(Com_Methods::Finite_Diffence_Method_Right(grid3[i-2], grid3[i-1], grid3[i], valuesF3[i-2], valuesF3[i-1], valuesF3[i]));
    }
    for (int i = 0; i<grid3.size(); i++) {
        if (i <= grid3.size()-3) der2.push_back(Com_Methods::Finite_Diffence_Method_Left(grid3[i], grid3[i+1], grid3[i+2], der1[i], der1[i+1], der1[i+2]));
        else der2.push_back(Com_Methods::Finite_Diffence_Method_Right(grid3[i-2], grid3[i-1], grid3[i], der1[i-2], der1[i-1], der1[i]));
    }
    cout << "Разность значений производных с помощью сплайна и МКР" << endl;
    cout << setw(w*1.4) << "Сплайн1" << setw(w*1.4) << "МКР1" << setw(w*1.4) << "Сплайн2" << setw(w*1.4) << "МКР2" << endl;
    double error_Spline1 = 0.0, error_MKR1 = 0.0, error_Spline2 = 0.0, error_MKR2 = 0.0;

    vector<double> S1_nodes, S2_nodes;
    double resN[3];
    for (size_t i = 0; i < grid3.size(); i++) {
        S.Get_Value(grid3[i], resN);
        S1_nodes.push_back(resN[1]);
        S2_nodes.push_back(resN[2]);
    }

    for (int i = 0; i<grid3.size(); i++) {
        error_Spline1 = error_Spline1 + fabs(f_der(grid3[i])-S1_nodes[i]);
        error_MKR1 = error_MKR1 + fabs(f_der(grid3[i])-der1[i]);
        error_Spline2 = error_Spline2 + fabs((-1)*f(grid3[i])-S2_nodes[i]);
        error_MKR2 = error_MKR2 + fabs((-1)*f(grid3[i])-der2[i]);
        cout << scientific << setw(w) << error_Spline1 << scientific << setw(w) << error_MKR1
        << scientific << setw(w) << error_Spline2 << scientific << setw(w) << error_MKR2 << endl;
    }
    cout << "Средняя погрешность по сетке GRID3" << endl;
    cout << scientific << setw(w) << error_Spline1/grid3.size() << scientific << setw(w) << error_MKR1/grid3.size() << scientific << setw(w)
    << error_Spline2/grid3.size() << scientific << setw(w) << error_MKR2/grid3.size();

    return 0;
}