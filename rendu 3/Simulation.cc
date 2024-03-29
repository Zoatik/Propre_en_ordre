/************|HEADER|*************
* AUTHORS: - Hall Axel (70%)     *
*          - Michel Lucas (30%)  *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 3.4                   *
* FILE: Simulation.cc            *
*********************************/

#include <algorithm>
#include "Simulation.h"


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
    if(m_nbP + get_robotS().get_nbNs()+get_robotS().get_nbRs()!=0)
    {
        update();
        get_robotS().update();
        update_movement();
        decide_deployment();
    }
}

void Simulation::update()
{

    bernoulli_distribution m_bernoulli(desintegration_rate/m_nbP);
    for(int i(0); i<m_nbP;i++)
    {
        if(m_bernoulli(e)==1)
        {
            if(m_particles_vect[i]->separate(m_particles_vect))
            {
                set_robots_state(*m_particles_vect[i]);
                m_particles_vect.erase(m_particles_vect.begin()+i);
                assign_target(true);
                m_nbP += 3;
            }
        }
    }
}

void Simulation::update_movement()
{
    for(unsigned int i(1); i<m_robots.size(); i++)
    {
        if(m_robots[i]->get_type() == "N")
        {
            Robot_N* robotN = dynamic_cast<Robot_N*>(m_robots[i].get());
            if(!robotN->get_panne())
            {
                assign_target();
                for(unsigned int j(0); j < m_particles_vect.size(); j++)
                {
                    if(collision(robotN->get_shape(),m_particles_vect[j]->get_shape()))
                    {
                        robotN->set_target(m_particles_vect[j].get());
                        robotN->set_in_collision(true);
                    }
                }
                
                if(robotN->get_target())
                {
                    if(robotN->move_to_target(m_robots))
                    {
                        remove_particle(robotN->get_target());
                        robotN->delete_target();
                        assign_target(true);
                    } 
                }
                if(m_nbP == 0 || !robotN->get_target())
                {
                    if(robotN->back_to_base(m_robots))
                        store_robot(robotN);
                }
                
            }else{
                if(get_robotS().get_nb_update() - robotN->get_k_update_panne() 
                                                >= int(max_update))
                    destroy_robot(robotN);
            }
        }
        else if(m_robots[i]->get_type() == "R")
        {
            assign_robotR_targets();
            Robot_R* robotR = dynamic_cast<Robot_R*>(m_robots[i].get());
            if(robotR->move_to_target(m_robots,m_particles_vect))
            {
                Robot_N* robotN = dynamic_cast<Robot_N*>(robotR->get_target());
                robotN->set_panne(false);
                get_robotS().set_nbNp(get_robotS().get_nbNp()-1);
                robotR->set_target(nullptr);
            }
            else if(!robotR->get_target())
            {
                if(robotR->back_to_base(m_robots, m_particles_vect))
                    store_robot(robotR);
            }

        }
    }
}

void Simulation::draw()
{
    for(int i(0);i<get_nb_N()+get_nb_R()+1;i++)
    {
        if(m_robots[i]->get_type()=="S") 
        {
            Robot_S* robotS = dynamic_cast<Robot_S*>(m_robots[i].get());
            robotS->draw();
        }
        else if(m_robots[i]->get_type()=="N"){
            Robot_N robotN = dynamic_cast<Robot_N&>(*m_robots[i]);
            robotN.draw();
        }
        else{
            Robot_R robotR = dynamic_cast<Robot_R&>(*m_robots[i]);
            robotR.draw();
        }
    }
	for(int i=0;i<get_nbP();i++)
	{
		m_particles_vect[i]->draw();
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

bool Simulation::write_file(string file_path)
{
    string file_text;
    file_text += "# Custom file text saved\n\n";
    file_text += to_string(m_nbP) + "\n";
    for(int i(0); i < m_nbP; i++)
    {
        string tmp_x = to_string(m_particles_vect[i]->get_shape().m_center.m_x);
        string tmp_y = to_string(m_particles_vect[i]->get_shape().m_center.m_y);
        string tmp_d = to_string(m_particles_vect[i]->get_shape().m_size);
        file_text += "\t" + tmp_x + " " + tmp_y + " " + tmp_d + "\n";
        
    }
    if(m_robots.size() > 0)
    {
        Robot_S* tmp_robotS = dynamic_cast<Robot_S*>(m_robots[0].get());
        string tmp_x = to_string(tmp_robotS->get_shape().m_center.m_x);
        string tmp_y = to_string(tmp_robotS->get_shape().m_center.m_y);
        string tmp_nbUpdate = to_string(tmp_robotS->get_nb_update());
        string tmp_nbNr = to_string(tmp_robotS->get_nbNr());
        string tmp_nbNs = to_string(tmp_robotS->get_nbNs());
        string tmp_nbNd = to_string(tmp_robotS->get_nbNd());
        string tmp_nbRr = to_string(tmp_robotS->get_nbRr());
        string tmp_nbRs = to_string(tmp_robotS->get_nbRs());
        file_text += "\n" + tmp_x + " " + tmp_y + " " + tmp_nbUpdate + " "
                  + tmp_nbNr + " " + tmp_nbNs + " " + tmp_nbNd + " "
                  + tmp_nbNr + " " + tmp_nbRs + "\n";

        for(int i(1); i <= tmp_robotS->get_nbRs(); i++)
        {
            if(m_robots[i]->get_type() == "R")
            {
                string tmp_x = to_string(m_robots[i]->get_shape().m_center.m_x);
                string tmp_y = to_string(m_robots[i]->get_shape().m_center.m_y);
                file_text += "\t" + tmp_x + " " + tmp_y + "\n";
            }
        }
        file_text += "\n";
        for(int i(tmp_robotS->get_nbRs()+1); i-tmp_robotS->get_nbRs()
                                            <= tmp_robotS->get_nbNs(); i++)
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

                file_text += "\t" + tmp_x + " " + tmp_y + " "+ tmp_a + " " + tmp_c_n +
                             " " + tmp_panne  + " " + tmp_k_update_panne +"\n";
            }
        }
    }
    else return false;
    
    ofstream out(file_path, ofstream::out | ofstream::trunc);
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
                return false;
            break;
        case 1 : //robot Spatial
            if(!read_robotS_prop(lines, i))
                return false;
            break;
        case 2 : //robot R�parateur
            if (!read_robotR_prop(lines, i))
                return false;
            break;
        case 3 : //robot Neutralisateur
            if (!read_robotN_prop(lines, i))
                return false;
            break;
        default :
            break;
        }
        line_type++; //on passe au type suivant
    }
    assign_target();//on assigne les targets
    assign_robotR_targets();
    cout<<message::success();

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
        current_line.imbue( locale( "C" ) ); //set default format
        double tmp_x(0.), tmp_y(0.), tmp_d(0.);

        current_line >> tmp_x >> tmp_y >> tmp_d;
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
    current_line.imbue( locale( "C" ) ); 
    double tmp_x, tmp_y;
    int tmp_nbUpdate, tmp_nbNr, tmp_nbNs, tmp_nbNd, tmp_nbRr, tmp_nbRs;
    
    current_line >> tmp_x >> tmp_y >> tmp_nbUpdate >> tmp_nbNr >> tmp_nbNs >>
                    tmp_nbNd >> tmp_nbRr >> tmp_nbRs;

    m_robots.push_back(make_unique<Robot_S>(s_2d(tmp_x, tmp_y), tmp_nbUpdate,
                       tmp_nbNr, tmp_nbNs, tmp_nbNd, tmp_nbRr, tmp_nbRs));

    return check_robot(m_robots[0]);
}

bool Simulation::read_robotR_prop(vector<string> lines, unsigned int& i)
{
    unsigned int j(i);
    while (i < j + dynamic_cast<Robot_S&>(*m_robots[0]).get_nbRs())
    {
        stringstream current_line(lines[i]);
        current_line.imbue( locale( "C" ) ); 
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
        current_line.imbue( locale( "C" ) ); 
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
    set_nbNp();//set nombre de robot_N en panne

    return true;
}

void Simulation::clear()
{
    m_robots.clear();
    m_nbP = 0;
    m_particles_vect.clear();
}

void Simulation::assign_target(bool override)
{
    if(override)
    {
        for(unsigned int i(1); i < m_robots.size(); i++)
        {
            if(m_robots[i]->get_type() == "N")
            {
                Robot_N* robotN = dynamic_cast<Robot_N*>(m_robots[i].get());
                robotN->delete_target();
            }
        }
    }
    vector<int> part_ind = get_untargeted_parts_index();
    for(unsigned int i(0); i < part_ind.size(); i++)
    {
        int robot_index=find_nearest_robot(m_particles_vect[part_ind[i]]->get_shape());
        if(robot_index != -1)
        {
            Robot_N* robotN = dynamic_cast<Robot_N*>(m_robots[robot_index].get());
            robotN->set_target(m_particles_vect[part_ind[i]].get());
            robotN->set_inter_point(robotN->find_safe_point());
        }
    }
    for(unsigned int i(1); i < m_robots.size(); i++)//si plus de robots que part
    {
        if(m_robots[i]->get_type() == "N" && m_nbP)
        {
            Robot_N* robotN = dynamic_cast<Robot_N*>(m_robots[i].get());
            if(!robotN->get_target())
                robotN->set_target(m_particles_vect[0].get());//plus grosse part
        }
    }
}

void Simulation::assign_robotR_targets()
{
    for(unsigned int i(1); i<m_robots.size(); i++)
    {
        if(m_robots[i]->get_type() == "R")
        {
            Robot_R* robotR = dynamic_cast<Robot_R*>(m_robots[i].get());
            robotR->set_target(nullptr);
        }
    }
    for(unsigned int i(1); i<m_robots.size(); i++)
    {
        if(m_robots[i]->get_type() == "N")
        {
            Robot_N* robotN = dynamic_cast<Robot_N*>(m_robots[i].get());
            if(robotN->get_panne())
            {   
                int max_nb_update = robotN->get_k_update_panne() + max_update
                                    - get_robotS().get_nb_update();                
                double shortest_distance(vtran_max*delta_t*max_nb_update);
                for(unsigned int j(1); j<m_robots.size(); j++)
                {
                    if(m_robots[j]->get_type() == "R")
                    {
                        Robot_R* robotR = dynamic_cast<Robot_R*>(m_robots[j].get());
                        if(distance(robotN->get_shape().m_center, 
                                    robotR->get_shape().m_center)<shortest_distance
                            && robotR->get_target()==nullptr)
                        {
                            shortest_distance = distance(robotN->get_shape().m_center,
                                                        robotR->get_shape().m_center);
                            robotR->set_target(robotN);
                        }
                    }
                }
            }
        }
    }
}

void Simulation::remove_particle(Particle* ptr)
{
    for(unsigned int i(0); i<m_particles_vect.size(); i++)
    {
        if(ptr->get_shape().m_center == m_particles_vect[i]->get_shape().m_center)
        {
            m_particles_vect.erase(m_particles_vect.begin()+i);
            m_nbP -= 1;
        }
    }
}

void Simulation::store_robot(Robot* ptr)
{
    for(unsigned int i(0); i<m_robots.size(); i++)
    {
        if(ptr->get_shape().m_center == m_robots[i]->get_shape().m_center)
        {
            if(ptr->get_type()=="N")
            {
                get_robotS().set_nbNr(get_robotS().get_nbNr()+1);
                get_robotS().set_nbNs(get_robotS().get_nbNs()-1);
            }else if(ptr->get_type()=="R")
            {
                get_robotS().set_nbRr(get_robotS().get_nbRr()+1);
                get_robotS().set_nbRs(get_robotS().get_nbRs()-1);
            }
            m_robots.erase(m_robots.begin()+i);
        }
    }
}

void Simulation::destroy_robot(Robot* ptr)
{
    for(unsigned int i(0); i<m_robots.size(); i++)
    {
        if(ptr->get_shape().m_center == m_robots[i]->get_shape().m_center)
        {
            get_robotS().set_nbNd(get_robotS().get_nbNd()+1);
            get_robotS().set_nbNp(get_robotS().get_nbNp()-1);
            get_robotS().set_nbNs(get_robotS().get_nbNs()-1);
            m_robots.erase(m_robots.begin()+i);
        }
    }
}

void Simulation::decide_deployment()
{
    s_2d pos_to_deploy(m_robots[0]->get_shape().m_center);
    if(get_robotS().get_nbNp()>get_robotS().get_nbRs())
    {
        if(get_robotS().get_nbRr()>0 && can_deploy("R"))
        {
            deploy_new_robot("R", pos_to_deploy);
            get_robotS().set_nbRr(get_robotS().get_nbRr()-1);
            get_robotS().set_nbRs(get_robotS().get_nbRs()+1);
        }
    }
    if(m_nbP>2*get_nb_N())
    {
        if(get_robotS().get_nbNr()>0 && can_deploy("N"))
        {
            deploy_new_robot("N", pos_to_deploy);
            get_robotS().set_nbNr(get_robotS().get_nbNr()-1);
            get_robotS().set_nbNs(get_robotS().get_nbNs()+1);
        }

    }
}
bool Simulation::can_deploy(std::string type)
{
    circle shape;
    if(type=="R")
        shape = circle(m_robots[0]->get_shape().m_center, r_reparateur);
    else
        shape = circle(m_robots[0]->get_shape().m_center, r_neutraliseur);
    for(unsigned int i(1); i < m_robots.size(); i++)
    {
        if(collision(shape, m_robots[i]->get_shape()))
            return false;
    }
    return true;
}

void Simulation::deploy_new_robot(std::string type, s_2d dest)
{
    if(type=="R")
    {
        m_robots.push_back(make_unique<Robot_R>(dest));
        assign_robotR_targets();
    }else if(type=="N"){
        int part_index = get_untargeted_parts_index()[0];
        Particle* part_targ = m_particles_vect[part_index].get();
        s_2d seg = part_targ->get_shape().m_center-get_robotS().get_shape().m_center;
        double angle = atan2(seg.m_y,seg.m_x);
        int type = (get_robotS().get_nbNs()+get_robotS().get_nbNd())%3;
        m_robots.push_back(make_unique<Robot_N>(dest, angle, type,
                                       false, 0));
        assign_target(true);
    }
}

///méthodes privées de génération
bool Simulation::check_particles(Particle part)
{
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
    
    for(unsigned int i(0); i < m_particles_vect.size(); i++)
    {
        if(collision(part.get_shape(),m_particles_vect[i]->get_shape(), true))
        {
            cout<<message::particle_superposition(
                                    part.get_shape().m_center.m_x,
                                    part.get_shape().m_center.m_y,
                                    m_particles_vect[i]->get_shape().m_center.m_x,
                                    m_particles_vect[i]->get_shape().m_center.m_y);
            return false;
        }
    }

    m_particles_vect.push_back(std::make_unique<Particle>(part));
    return true;
}

bool Simulation::check_robot(unique_ptr<Robot>& robot)
{
    for(unsigned int j(0); j<m_particles_vect.size(); j++)//check superposition N-P
    {
        if(collision(robot->get_shape(),m_particles_vect[j]->get_shape(),true))
        {
            show_particle_robot_superposition(robot, j);
            return false;
        }
    }

    if(robot->get_type() == "N")
    {
        Robot_N* robotN = dynamic_cast<Robot_N*>(robot.get());
        return check_robotN(*robotN);    
    }
    if(robot->get_type() == "R")
    {
        Robot_R* robotR = dynamic_cast<Robot_R*>(robot.get());
        return check_robotR(*robotR);    
    }
    if(robot->get_type() == "S")
    {
        Robot_S* robotS = dynamic_cast<Robot_S*>(robot.get());
        return check_robotS(*robotS);    
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
                m_particles_vect[j]->get_shape().m_center.m_x,
                m_particles_vect[j]->get_shape().m_center.m_y,
                m_particles_vect[j]->get_shape().m_size,
                robot->get_shape().m_center.m_x,
                robot->get_shape().m_center.m_y,
                robot->get_shape().m_radius);
}

int Simulation::find_nearest_robot(square s_part)
{
    int best_choice_index = -1;
    double best_time = -1;
    int k = 1;
    for (unsigned int i(0); i < m_robots.size(); i++)
    {
        if(m_robots[i]->get_type() != "N")
            continue;
        if(dynamic_cast<Robot_N&>(*m_robots[i]).get_target() != nullptr)
        {
            k++;
            continue;
        }
        Robot_N robotN = dynamic_cast<Robot_N&>(*m_robots[i]);
        if(robotN.get_panne())
        {
            k++;
            continue;
        }
        circle c_robotN = m_robots[i]->get_shape();
        s_2d point_part = s_part.m_center;
        s_2d seg = point_part - c_robotN.m_center;
        double part_orientation = atan2(seg.m_y, seg.m_x);
        if(part_orientation < 0)
            part_orientation = 2*M_PI+part_orientation;
        if(int(i) == get_robotS().get_nbRs() + k)
        {
            best_choice_index = i;
            double best_dist = distance(c_robotN.m_center, point_part);
            double best_rota = abs(robotN.get_angle() - part_orientation);
            if(best_rota > M_PI)
                best_rota = 2*M_PI - best_rota;
            best_time = best_rota/vrot_max + best_dist/vtran_max;
        }
        else
        {
            double new_best_dist = distance(c_robotN.m_center, point_part);
            double new_best_rota = abs(robotN.get_angle() - part_orientation);
            if(new_best_rota > M_PI)
                new_best_rota = 2*M_PI - new_best_rota;
            double new_best_time = new_best_rota/vrot_max + new_best_dist/vtran_max;
            if(new_best_time < best_time)
            {
                best_choice_index = i;
                best_time = new_best_time;
            }
        }
    }
    return best_choice_index;
}

vector<int> Simulation::get_untargeted_parts_index()
{
    tri_size(m_particles_vect);
    vector<int> new_vect;
    for(unsigned int i(0); i < m_particles_vect.size(); i++)
    {
        if(!m_particles_vect[i]->get_is_target())
            new_vect.push_back(i);
    }
    return new_vect;
}

void Simulation::tri_size(std::vector<unique_ptr<Particle>> &part_vect)
{
    unsigned int i, j;
    for (i = 1; i < part_vect.size(); ++i)
    {
        Particle part = *part_vect[i];
        for (j = i; j > 0 && part_vect[j-1]->get_shape().m_size 
                             < part.get_shape().m_size; j--)
            iter_swap(part_vect.begin() + j, part_vect.begin() + j-1);
    }
}

void Simulation::set_robots_state(Particle const &part)
{
    for(unsigned int i(1); i<m_robots.size(); i++)
    {
        if(m_robots[i]->get_type() == "N")
        {
            Robot_N& curr_robotN = dynamic_cast<Robot_N&>(*m_robots[i]);
            if(collision(curr_robotN.get_shape(), part.get_risk_zone()))
            {
                curr_robotN.set_panne(true);
                curr_robotN.set_k_update_panne(get_robotS().get_nb_update());
                get_robotS().set_nbNp(get_robotS().get_nbNp()+1);
            }
        }
    }
}

Robot_S& Simulation::get_robotS()
{
    return dynamic_cast<Robot_S&>(*m_robots[0]);
}

vector<unique_ptr<Particle>>& Simulation::get_particles_vect()
{
    return m_particles_vect;
}

vector<unique_ptr<Robot>>& Simulation::get_robots_ptr_vect()
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
        if(m_robots[i]->get_type() == "N" && 
                    dynamic_cast<Robot_N&>(*m_robots[i]).get_panne() == true)
            count+=1;
    }
    get_robotS().set_nbNp(count);
}

