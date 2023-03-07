#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

constexpr double epsil_zero(0.125);
struct s_2d
{
    //ctor
    s_2d(){}
    s_2d(double x, double y): m_x(x), m_y(y){}

    double m_x = 0.;
    double m_y = 0.;
};

#endif // SHAPE_H_INCLUDED
