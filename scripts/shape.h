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

class Circle
{
    public:
        Circle(s_2d center, double radius): m_center(center), m_radius(radius){}
    protected:
    private:
        s_2d m_center();
        double m_radius;

};

class Square
{
    public:
        Square(s_2d center, double size): m_center(center), m_size(size){}
    protected:
    private:
        s_2d m_center();
        double m_size;

};

bool circle_square_collision(s_2d circle_center, double r1, s_2d sqare_center, double d1);
bool circles_collision(s_2d center_1, double r1, s_2d center_2, double r2);
bool squares_collision(s_2d center_1, double d1, s_2d center_2, double d2);
double distance(s_2d point_1, s_2d point_2);
double norm(s_2d point);

#endif // SHAPE_H_INCLUDED
