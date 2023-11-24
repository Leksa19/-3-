#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <iostream>
#include <tuple>
#include <numeric>
#include <omp.h>
using namespace std;
class curves
{
public:
    double x, y, z, dx, dy, dz;
    virtual tuple<double, double,double> point(double t) const=0;
    virtual tuple<double, double, double> proizvod(double t) const = 0;
};
class Circle:public curves
{
    
public:
    Circle(double rad) :radius(rad)
    {}
    tuple<double,double,double> point(double t) const override // функция с параметрическим уравнением
    {
        double x = radius * cos(t);
        double y = radius * sin(t);
        double z = 0.0;
        return make_tuple(x, y,z);
    }
    tuple<double, double, double> proizvod(double t) const override // функция с производной от параметрического уравнения
    {
        double dx = -radius * std::sin(t);
        double dy = radius * std::cos(t);
        double dz = 0.0;
        return make_tuple(dx, dy,dz);
    }
private:
    double radius;
};
class Elipse :public curves
{
public:
    Elipse(double srad, double brad) :sradii(srad), bradii(brad)
    {}
   
    tuple<double, double, double> point(double t) const override // функция с параметрическим уравнением
    {
        double x = bradii * std::cos(t);
        double y = sradii * std::sin(t);
        double z = 0.0;
        return make_tuple(x, y,z);
    }
    tuple<double, double, double> proizvod(double t) const override // функция с производной от параметрического уравнения
    {
        double dx = -bradii * std::sin(t);
        double dy = sradii * std::cos(t);
        double dz = 0.0;
        return make_tuple(dx, dy, dz);
    }
private:
    double sradii;
    double bradii;
};
class Helixe :public curves
{
public:
    Helixe(double rad, double st) :radius(rad), step(st)
    {}
    tuple<double, double,double> point (double t) const override // функция с параметрическим уравнением
    {
        double x = radius * std::cos(t);
        double y = radius * std::sin(t);
        double z = step * t / (2 * 3.141592653589793);
        return make_tuple(x, y,z);
    }
    tuple<double, double, double> proizvod(double t) const override // функция с производной от параметрического уравнения
    {
        double dx = -radius * std::sin(t);
        double dy = radius * std::cos(t);
        double dz = step / (2 * 3.141592653589793);
        return make_tuple(dx, dy,dz);
    }
private:
    double radius;
    double step;
};
int main()
{
    int count = 10; //задаем кол-во случайно генерируемых фигур
    double t = 3.141592653589793/4;
    vector<double> allcurv(count*2+count);//вектор со случайно созданными значениями
    vector<double*> circlvec;// вектор с радиусами круга
    mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    uniform_int_distribution<int> intrand(1, 3);
    uniform_real_distribution<double> dublrand(0.1, 10.0);
    int curve=0 ;
    double temp;
    double rad=0.1;
    double parametr ;
    double parametr2;
    int place = 0;
    for (int i = 0; i < count; i++)
    {
        curve = intrand(rng);
        allcurv[place] = curve;
        place++;
        if (curve == 1)// круг
        {
            parametr = dublrand(rng);
            allcurv[place] = parametr;
            double& value = allcurv[place];
            circlvec.push_back(&value);
            place++;
            Circle cir(parametr);
            auto returnedValues = cir.point(t);
            cout << "3d point of circle: " << "(" << get<0>(returnedValues) << ";" << get<1>(returnedValues) << ";" << get<2>(returnedValues) << ")" << endl;
            returnedValues = cir.proizvod(t);
            cout << "First derivative of circle: " << "(" << get<0>(returnedValues) << ";" << get<1>(returnedValues) << ";" << get<2>(returnedValues) << ")" << endl;
            
        }
        if (curve == 2)// эллипс
        {
            parametr = dublrand(rng);
            allcurv[place] = parametr;
            place++;
            parametr2 = dublrand(rng);
            allcurv[place] = parametr2;
            place++;
            if (parametr < parametr2)
            {
                temp = parametr;
                parametr = parametr2;
                parametr2 = temp;
            }
            Elipse eli(parametr,parametr2);
            auto returnedValues = eli.point(t);
            cout << "3d point of elipse: " << "(" << get<0>(returnedValues) << ";" << get<1>(returnedValues) << ";" << get<2>(returnedValues) << ")" << endl;
            returnedValues = eli.proizvod(t);
            cout << "First derivative of elipse: " << "(" << get<0>(returnedValues) << ";" << get<1>(returnedValues) << ";" << get<2>(returnedValues) << ")" << endl;
        }
        if (curve == 3)// спираль
        {
            parametr = dublrand(rng);
            allcurv[place] = parametr;
            place++;
            parametr2 = dublrand(rng);
            allcurv[place] = parametr2;
            place++;
            Helixe hel(parametr, parametr2);
            auto returnedValues = hel.point(t);
            cout << "3d point of helixe: " << "(" << get<0>(returnedValues) << ";" << get<1>(returnedValues) << ";" << get<2>(returnedValues) << ")" << endl;
            returnedValues = hel.proizvod(t);
            cout << "First derivative of helixe: " << "(" << get<0>(returnedValues) << ";" << get<1>(returnedValues) << ";" << get<2>(returnedValues) << ")" << endl;
        }
           
    }
    auto comparator = [](const double* a, const double* b) {
        return *a < *b;
    };
    sort(circlvec.begin(), circlvec.end(), comparator);
    double sum = 0.0;
    for (auto& val : circlvec)
        sum += *val;
    cout << "Sum of circle radii: " << sum << endl;
    for (auto& ptr : circlvec) {
        delete ptr;
    }
    circlvec.clear();

}


