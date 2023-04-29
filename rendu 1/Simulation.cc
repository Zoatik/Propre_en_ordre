/************|HEADER|*************
* AUTHORS: - Hall Axel           *
*          - Michel Lucas        *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 2.0                   *
* FILE: Simulation.cc            *
*********************************/

#include "Simulation.h"
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

static default_random_engine e;

//ctor-dtor
Simulation::Simulation()
{
    //ctor
}

Simulation::~Simulation()
{
    //dtor
}

///méthodes publiques

void Simulation::next_step()
{
    update();
    get_robotS().update();
}

void Simulation::update()
{

    std::bernoulli_distribution m_bernoulli(desintegration_rate/m_nbP);
    for(int i(0); i<m_nbP;i++)
    {
        if(m_bernoulli(e)==1)
        {
            if(m_particles_vect[i].separate(m_particles_vect))
            {
                cout<<"separated "<<i<<endl;
                m_particles_vect.erase(m_particles_vect.begin()+i);
                m_nbP += 3;
            }
        }
    }
}

void Simulation::draw(int xc, int yc, double ratio)
{
    draw_border(ratio, xc*2);
    for(int i(0);i<get_nb_N()+get_nb_R()+1;i++)
    {
        if(m_robots[i]->get_type()=="S") 
        {
            Robot_S robotS = dynamic_cast<Robot_S&>(*m_robots[i]);
            robotS.draw(xc, yc, ratio);
        }
        else if(m_robots[i]->get_type()=="N"){
            Robot_N robotN = dynamic_cast<Robot_N&>(*m_robots[i]);
            robotN.draw(xc, yc, ratio);
        }
        else{
            Robot_R robotR = dynamic_cast<Robot_R&>(*m_robots[i]);
            robotR.draw(xc, yc, ratio);
        }
    }
	for(int i=0;i<get_nbP();i++)
	{
		m_particles_vect[i].draw(xc, yc, ratio);
	};
}

bool Simulation::read_file(string file_path)
{
    e.seed(1);
    string line;
    vector<string> lines;
    ifstream file(file_path);
    if (file.is_open())
    {
        while (file)
        {
            getline(file, line);
            lines.push_back(line);
            cout<<line<<endl;
        }
    }
    else
    {
        cout << "Could not open file : " << file_path << endl;
        return false;
    }
    file.close();
    return sep_file_infos(lines);

}

bool Simulation::write_file(std::string file_path)
{
    cout<<"on entre"<<endl;
    string file_text;
    file_text += "# Custom file text saved\n\n";
    file_text += to_string(m_nbP) + "\n";
    for(unsigned int i(0); i < m_nbP; i++)
    {
        string tmp_x = to_string(m_particles_vect[i].get_shape().m_center.m_x);
        string tmp_y = to_string(m_particles_vect[i].get_shape().m_center.m_y);
        string tmp_d = to_string(m_particles_vect[i].get_shape().m_size);
        file_text += "\t" + tmp_x + " " + tmp_y + " " + tmp_d + "\n";
        
    }
    if(m_robots.size() > 0)
    {
        Robot_S tmp_robotS = dynamic_cast<Robot_S&>(*m_robots[0]);
        string tmp_x = to_string(tmp_robotS.get_shape().m_center.m_x);
        string tmp_y = to_string(tmp_robotS.get_shape().m_center.m_y);
        string tmp_nbUpdate = to_string(tmp_robotS.get_nb_update());
        string tmp_nbNr = to_string(tmp_robotS.get_nbNr());
        string tmp_nbNs = to_string(tmp_robotS.get_nbNs());
        string tmp_nbNd = to_string(tmp_robotS.get_nbNd());
        string tmp_nbRr = to_string(tmp_robotS.get_nbRr());
        string tmp_nbRs = to_string(tmp_robotS.get_nbRs());
        file_text += "\n" + tmp_x + " " + tmp_y + " " + tmp_nbUpdate + " "
                  + tmp_nbNr + " " + tmp_nbNs + " " + tmp_nbNd + " "
                  + tmp_nbNr + " " + tmp_nbRs + "\n";

        for(unsigned int i(1); i <= tmp_robotS.get_nbRs(); i++)
        {
            if(m_robots[i]->get_type() == "R")
            {
                string tmp_x = to_string(m_robots[i]->get_shape().m_center.m_x);
                string tmp_y = to_string(m_robots[i]->get_shape().m_center.m_y);
                file_text += "\t" + tmp_x + " " + tmp_y + "\n";
            }
        }
        file_text += "\n";
        for(unsigned int i(tmp_robotS.get_nbRs()+1); i-tmp_robotS.get_nbRs() <= tmp_robotS.get_nbNs(); i++)
        {
            if(m_robots[i]->get_type() == "N")
            {
                Robot_N tmp_robotN = dynamic_cast<Robot_N&>(*m_robots[i]);
                string tmp_x = to_string(m_robots[i]->get_shape().m_center.m_x);
                string tmp_y = to_string(m_robots[i]->get_shape().m_center.m_y);
                string tmp_a = to_string(tmp_robotN.get_angle());
                string tmp_c_n = to_string(tmp_robotN.get_c_n());
                string tmp_panne = "false";
                string tmp_k_update_panne = to_string(tmp_robotN.get_k_update_panne());
                if (tmp_robotN.get_panne())
                    tmp_panne = "true";

                file_text += "\t" + tmp_x + " " + tmp_y + " "+ tmp_a + " " + 
                            tmp_c_n + " " + tmp_panne  + " " + tmp_k_update_panne +"\n";
            }
        }
    }
    else return false;
    
    ofstream out(file_path, std::ofstream::out | std::ofstream::trunc);
    if (out.is_open())
    {
        out << file_text;
        out.close();
    }
    else cout<<"could not open file (writing)"<<endl;
    
    return true;
}

int Simulation::get_nbP()
{
    return m_nbP;
}

int Simulation::get_nb_N()
{
    return get_robotS().get_nbNs();
}

int Simulation::get_nb_R()
{
    return get_robotS().get_nbRs();
}

bool Simulation::get_emptiness()
{
    return m_empty;
}

bool Simulation::sep_file_infos(vector<string> lines)
{
    int line_type(0);//0: infos particules, 1: ' robot spatial,
                     //2: '' r�parateur, 3: neutraliseur
    for (unsigned int i(0); i < lines.size(); i++)
    {
        istringstream current_line(lines[i]);
        string spec;
        current_line >> spec;
        if (spec == "#" || lines[i].size() == 0)
            //on saute la ligne si # ou si vide
            continue;
        switch (line_type)
        {
        case 0 : //particules
            if (!read_particles_prop(spec, lines, i))
            {
                m_empty = true;
                return false;
            }
            break;
        case 1 : //robot Spatial
            if(!read_robotS_prop(lines, i))
            {
                m_empty = true;
                return false;
            }
            break;
        case 2 : //robot R�parateur
            if (!read_robotR_prop(lines, i))
            {
                m_empty = true;
                return false;
            }
            break;
        case 3 : //robot Neutralisateur
            if (!read_robotN_prop(lines, i))
            {
                m_empty = true;
                return false;
            } 
            break;
        default :
            break;
        }
        line_type++; //on passe au type suivant
    }
    cout<<message::success();
    m_empty = false;
    return true;
}

bool Simulation::read_particles_prop(string spec, vector<string> lines,
                               unsigned int &i)
{
    m_nbP = stoi(spec);
    unsigned int j(i);
    i++;
    while (i <= j + m_nbP)//on boucle sur le nb de particules
    {
        istringstream current_line(lines[i]);
        current_line.imbue( std::locale( "C" ) ); //set default format
        string stmp_x(""), stmp_y(""), stmp_d("");
        double tmp_x(0.), tmp_y(0.), tmp_d(0.);
        cout<<lines[i]<<endl;
        current_line >> tmp_x >> tmp_y >> tmp_d;
        stmp_d += " ";
        cout<<"size : "<<tmp_d<<endl; // debug
        
        Particle part(square(s_2d(tmp_x, tmp_y), tmp_d));
        if (!check_particles(part))
            return false;
        i++;
    }
    return true;
}

bool Simulation::read_robotS_prop(vector<string> lines, unsigned int& i)
{
    stringstream current_line(lines[i]);
    current_line.imbue( std::locale( "C" ) ); 
    double tmp_x, tmp_y;
    int tmp_nbUpdate, tmp_nbNr, tmp_nbNs, tmp_nbNd, tmp_nbRr, tmp_nbRs;
    current_line >> tmp_x >> tmp_y >> tmp_nbUpdate >> tmp_nbNr >> tmp_nbNs >>
                    tmp_nbNd >> tmp_nbRr >> tmp_nbRs;

    m_robots.push_back(make_unique<Robot_S>(s_2d(tmp_x, tmp_y), tmp_nbUpdate, tmp_nbNr,
					   tmp_nbNs, tmp_nbNd, tmp_nbRr, tmp_nbRs));

    return check_robot(m_robots[0]);
}

bool Simulation::read_robotR_prop(vector<string> lines, unsigned int& i)
{
    unsigned int j(i);
    while (i < j + dynamic_cast<Robot_S&>(*m_robots[0]).get_nbRs())
    {
        stringstream current_line(lines[i]);
        current_line.imbue( std::locale( "C" ) ); 
        double tmp_x, tmp_y;
        current_line >> tmp_x >> tmp_y;
        m_robots.push_back(make_unique<Robot_R>(s_2d(tmp_x, tmp_y)));
        if (!check_robot(m_robots[m_robots.size()-1]))
            return false;
        i++;
    }
    return true;
}

bool Simulation::read_robotN_prop(vector<string> lines, unsigned int& i)
{
    unsigned int j(i);
    while (i < j + dynamic_cast<Robot_S&>(*m_robots[0]).get_nbNs())
    {
        istringstream current_line(lines[i]);
        current_line.imbue( std::locale( "C" ) ); 
        double tmp_x, tmp_y, tmp_a;
        int tmp_c_n, tmp_k_update_panne;
        string tmp_str_panne;
        current_line >> tmp_x >> tmp_y >> tmp_a >> tmp_c_n >>
                        tmp_str_panne >> tmp_k_update_panne;
        
        bool tmp_panne(bool(tmp_str_panne == "true"));
        m_robots.push_back(make_unique<Robot_N>(s_2d(tmp_x, tmp_y), tmp_a, tmp_c_n,
                                       tmp_panne, tmp_k_update_panne));
        if (!check_robot(m_robots[m_robots.size()-1]))
            return false;
        i++;
    }
    set_nbNp();
    return true;
}

void Simulation::clear()
{
    m_empty = true;
    m_robots.clear();
    m_nbP = 0;
    m_particles_vect.clear();
}


///méthodes privées de génération
 
bool Simulation::check_particles(Particle part)
{
   // cout<<"size : "<<part.get_shape().m_size<<endl; // debug
    if(part.get_shape().m_size<d_particule_min)
    {
        cout<<message::particle_too_small(part.get_shape().m_center.m_x,
                                            part.get_shape().m_center.m_y,
                                            part.get_shape().m_size);
        return false;
    }
    if (!check_position(part.get_shape(), dmax))//check position valide
    {
        cout<<message::particle_outside(part.get_shape().m_center.m_x,
                                    part.get_shape().m_center.m_y,
                                    part.get_shape().m_size);
        return false;
    }
    //cout<<"nb de particules : "<<m_particles_vect.size()<<endl;
    for(unsigned int i(0); i < m_particles_vect.size(); i++)
    {
        if(collision(part.get_shape(),m_particles_vect[i].get_shape(), true))
        {
            cout<<message::particle_superposition(
                                    part.get_shape().m_center.m_x,
                                    part.get_shape().m_center.m_y,
                                    m_particles_vect[i].get_shape().m_center.m_x,
                                    m_particles_vect[i].get_shape().m_center.m_y);
            return false;
        }
    }

    m_particles_vect.push_back(part);
    return true;
}

bool Simulation::check_robot(unique_ptr<Robot>& robot)
{
    for(unsigned int j(0); j<m_particles_vect.size(); j++)//check superposition N-P
    {
        if(collision(robot->get_shape(),m_particles_vect[j].get_shape(),true))
        {
            show_particle_robot_superposition(robot, j);
            return false;
        }
    }

    if(robot->get_type() == "N")
    {
        Robot_N robotN = dynamic_cast<Robot_N&>(*robot);
        return check_robotN(robotN);    
    }
    if(robot->get_type() == "R")
    {
        Robot_R robotR = dynamic_cast<Robot_R&>(*robot);
        return check_robotR(robotR);    
    }
    if(robot->get_type() == "S")
    {
        Robot_S robotS = dynamic_cast<Robot_S&>(*robot);
        return check_robotS(robotS);    
    }
    
    return true;
}

bool Simulation::check_robotS(Robot_S robotS)
{
    if(!check_position(robotS.get_shape(), dmax))//check position
    {
        cout<<message::spatial_robot_outside(robotS.get_shape().m_center.m_x,
                                             robotS.get_shape().m_center.m_y);
        return false;
    }
    return true;
}

bool Simulation::check_robotR(Robot_R robotR)
{
    return true;
    for(unsigned int i(0); i<m_robots.size()-1; i++)//check superposition
    {
        if(collision(robotR.get_shape(),m_robots[i]->get_shape(), true))
        {
            if(m_robots[i]->get_type() == "R")
            {
                cout<<message::repairers_superposition(
                                            robotR.get_shape().m_center.m_x,
                                            robotR.get_shape().m_center.m_y,
                                            m_robots[i]->get_shape().m_center.m_x,
                                            m_robots[i]->get_shape().m_center.m_y);
                return false;
            }
        }
    }
    return true;
}

bool Simulation::check_robotN(Robot_N robotN)
{
    if(robotN.get_k_update_panne() > get_robotS().get_nb_update())
    {
        show_invalid_k_update(robotN);
        return false;
    }

    for(unsigned int i(0); i<m_robots.size()-1; i++)//check superposition
    //size()-1 car on ne veut pas check avec lui-même
    {
        if(collision(robotN.get_shape(),m_robots[i]->get_shape(), true))
        {
            if(m_robots[i]->get_type() == "N")
            {
                show_neutralizers_superposition(robotN, i);
                return false;
            }
            else if(m_robots[i]->get_type() == "R")
            {
                show_repairer_neutralizer_superposition(robotN, i);
                return false;
            }
        }
    }
    return true;
}

/// méthodes privées d'affichage de messages d'erreurs
///(permet d'alléger "generate_RobotN")
void Simulation::show_invalid_k_update(Robot_N curr_robotN)
{
    cout<<message::invalid_k_update(
                curr_robotN.get_shape().m_center.m_x,
                curr_robotN.get_shape().m_center.m_y,
                curr_robotN.get_k_update_panne(),
                get_robotS().get_nb_update());
}
void Simulation::show_neutralizers_superposition(Robot_N curr_robotN, int j)
{
    cout<<message::neutralizers_superposition(
                curr_robotN.get_shape().m_center.m_x,
                curr_robotN.get_shape().m_center.m_y,
                m_robots[j]->get_shape().m_center.m_x,
                m_robots[j]->get_shape().m_center.m_y);
}
void Simulation::show_repairer_neutralizer_superposition(Robot_N curr_robotN, int j)
{
    cout<<message::repairer_neutralizer_superposition(
                m_robots[j]->get_shape().m_center.m_x,
                m_robots[j]->get_shape().m_center.m_y,
                curr_robotN.get_shape().m_center.m_x,
                curr_robotN.get_shape().m_center.m_y);
}
void Simulation::show_particle_robot_superposition(unique_ptr<Robot>& robot, int j)
{
    cout<<message::particle_robot_superposition(
                m_particles_vect[j].get_shape().m_center.m_x,
                m_particles_vect[j].get_shape().m_center.m_y,
                m_particles_vect[j].get_shape().m_size,
                robot->get_shape().m_center.m_x,
                robot->get_shape().m_center.m_y,
                robot->get_shape().m_radius);
}

Robot_S& Simulation::get_robotS()
{
    return dynamic_cast<Robot_S&>(*m_robots[0]);
}

vector<Particle> Simulation::get_particles_vect()
{
    return m_particles_vect;
}

std::vector<unique_ptr<Robot>>& Simulation::get_robots_ptr_vect()
{
    return m_robots;
}

int Simulation::get_updates()
{
    return get_robotS().get_nb_update();
}

void Simulation::set_nbNp()
{
    int count(0);
    for(int i(0);i<get_nb_N()+get_nb_R()+1;i++)
    {
cout<<"check"<<endl;
        if(m_robots[i]->get_type() == "N" and dynamic_cast<Robot_N&>(*m_robots[i]).get_panne() == true)
        {
            count+=1;
        }
    }
    get_robotS().set_nbNp(count);
}


