/************|HEADER|*************
* AUTHORS: - Hall Axel           *
*          - Michel Lucas        *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 2.6                   *
* FILE: Robot.h                  *
*********************************/


#ifndef ROBOT_H
#define ROBOT_H

#include "constantes.h"
#include "Particle.h"


class Robot
{
    public:
        //ctor-dtor
        Robot();
        Robot(circle cercle);
        virtual ~Robot();

        //virtual
        virtual std::string get_type() = 0;
        //méthodes
        void set_pos(s_2d pos);
        circle get_shape();//retourne le struct circle du robot
        int test = 0;
        
    protected:
        circle m_circle;
};

/** ROBOT SPATIAL**/
class Robot_S : public Robot
{
    public:
        //ctor-dtor
        Robot_S();
        Robot_S(s_2d pos, int nbUpdate, int nbNr, int nbNs,
                int nbNd, int nbRr, int nbRs);
        virtual ~Robot_S();

        //virtual
        virtual std::string get_type();

        //méthodes
        void set(s_2d pos, int nbUpdate, int nbNr, int nbNs,
                 int nbNd, int nbRr, int nbRs);
        void set_nbNp(int count);
        void set_nbNr(int count);
        void set_nbNs(int count);
        void set_nbNd(int count);
        void set_nbRr(int count);
        void set_nbRs(int count);
        void draw();
        int get_nb_update();
        int get_nbNr();
        int get_nbNs();
        int get_nbNd();
        int get_nbNp();
        int get_nbRr();
        int get_nbRs();
        void update();

    private:
        int m_nbUpdate;
        int m_nbNr;
        int m_nbNs;
        int m_nbNd;
        int m_nbRr;
        int m_nbRs;
        int m_nbNp;
        const std::string m_type = "S";
};

/**NEUTRALISEUR**/
class Robot_N : public Robot
{
    public:
        //ctor-dtor
        Robot_N();
        Robot_N(s_2d pos, double angle, int coord_type, 
                bool panne, int k_update_panne);
        virtual ~Robot_N();

        //virtual
        virtual std::string get_type();
        //bool move_to(s_2d point);
        bool move_to_target(std::vector<std::unique_ptr<Robot>> &robots);
        bool move_to_point(s_2d point, std::vector<std::unique_ptr<Robot>> &robots);
        s_2d find_safe_point(bool outside = true);
        bool back_to_base(std::vector<std::unique_ptr<Robot>> &robots);

        //méthodes
        void set(s_2d pos, double angle, int coord_type,
                 bool panne, int k_update_panne);
        void set_target(Particle* target);
        void delete_target();
        void set_panne(bool panne);
        void set_in_collision(bool in_collision);
        void set_inter_point(s_2d safe_point);
        void draw();
        int get_k_update_panne();
        double get_angle();
        bool get_panne();
        bool get_in_collision();
        int get_c_n();
        Particle* get_target();
    private:
        bool final_alignment(std::vector<std::unique_ptr<Robot>> &robots); //false si alignement terminé
        bool alignment(s_2d point);
        bool destroy_target();
        void rotate(double a);
        void translate(std::vector<std::unique_ptr<Robot>> &robots);//déplace le robot
        

        double m_angle;
        int m_coord_type;
        bool m_panne;
        int m_k_update_panne;
        const std::string m_type = "N";
        Particle* m_target = nullptr;
        bool m_in_collision = false;
        s_2d m_inter_point;
};

/**REPARATEURS**/
class Robot_R : public Robot
{
    public:
        //ctor-dtor
        Robot_R();
        Robot_R(s_2d pos);
        virtual ~Robot_R();
        //virtual
        virtual std::string get_type();
        bool move_to_target(std::vector<std::unique_ptr<Robot>> &robots,
                            std::vector<std::unique_ptr<Particle>> &particles_vect);
        bool back_to_base(std::vector<std::unique_ptr<Robot>> &robots);
        //methods
        bool translate(std::vector<std::unique_ptr<Robot>> &robots,
                        std::vector<std::unique_ptr<Particle>> &particles_vect);
        void set(s_2d pos);
        void set_target(Robot_N* target);
        Robot_N* get_target();
        void draw();

    private:
        const std::string m_type = "R";
        Robot_N* m_target = nullptr;
};





#endif // ROBOT_H
