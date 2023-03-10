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

struct circle
{       
    circle(){}
    circle(s_2d center, double radius): m_center(center), m_radius(radius){}

    s_2d m_center;
    double m_radius;

};

struct square
{
    square(){}
    square(s_2d center, double size): m_center(center), m_size(size){}

    s_2d m_center;
    double m_size;

};

class Shape
{
    public:
        Shape();
        ~Shape();

        bool collision(circle c1, square s1);
        bool collision(circle c1, circle c2);
        bool collision(square s1, square s2);
        double distance(s_2d point_1, s_2d point_2);
        double norm(s_2d point);
    protected:
    private:

};



#endif // SHAPE_H_INCLUDED