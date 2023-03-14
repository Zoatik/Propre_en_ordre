#include "File.h"

//constructeurs
File::File()
{
    //ctor
}
//destructeur
File::~File()
{
    //dtor
}
//m�thodes
/*PUBLIC*/
bool File::read_file(std::string file_path)
{
    std::string line;
    std::vector<std::string> lines;
    std::ifstream file(file_path);
    if (file.is_open())
    {
        while (file)
        {
            std::getline(file, line);
            lines.push_back(line);
        }
    }
    else
    {
        std::cout << "Could not open file : " << file_path << std::endl;
        return false;
    }
    file.close();
    sep_file_infos(lines);

    return true;
}

/*PRIVATE*/
void File::sep_file_infos(std::vector<std::string> lines)
{
    int line_type(0);//0: infos particules, 1: ' robot spatial, 
                     //2: '' r�parateur, 3: neutraliseur
    for (unsigned int i(0); i < lines.size(); i++)
    {
        std::istringstream current_line(lines[i]);
        std::string spec;
        current_line >> spec;
        if (spec == "#" || lines[i].size() == 0)
            //on saute la ligne si # ou si vide
            continue;
        switch (line_type)
        {
        case 0 : //particules
            read_particles_prop(spec, lines, i);
            break;
        case 1 : //robot Spatial
            read_robotS_prop(lines, i);
            break;
        case 2 : //robot R�parateur
            read_robotR_prop(lines, i);
            break;
        case 3 : //robot Neutralisateur
            read_robotN_prop(lines, i);
            break;
        default :
            break;
        }
        line_type++; //on passe au type suivant
    }
    show_infos();
}

void File::read_particles_prop(std::string spec, std::vector<std::string> lines, unsigned int &i)
{
        
    m_nbP = std::stoi(spec);
    unsigned int j(i);
    i++;
    while (i <= j + m_nbP)//on boucle sur le nb de particules
    {
        std::istringstream current_line(lines[i]);
        double tmp_x, tmp_y, tmp_d;
        current_line >> tmp_x >> tmp_y >> tmp_d;
        //std::cout<<tmp_x<<"/"<<tmp_y<<"/"<<tmp_d<<"\n";
        s_particle_infos part(s_2d(tmp_x, tmp_y), tmp_d);
        m_particle_vect.push_back(part);
        i++;
    }
}

void File::read_robotS_prop(std::vector<std::string> lines, unsigned int& i)
{
    std::istringstream current_line(lines[i]);
    double tmp_x, tmp_y;
    int tmp_nbUpdate, tmp_nbNr, tmp_nbNs, tmp_nbNd, tmp_nbRr, tmp_nbRs;
    current_line >> tmp_x >> tmp_y >> tmp_nbUpdate >> tmp_nbNr >> tmp_nbNs >>
                    tmp_nbNd >> tmp_nbRr >> tmp_nbRs;
    m_robotS = s_robotS_infos(s_2d(tmp_x, tmp_y),
                       tmp_nbUpdate, tmp_nbNr,
                       tmp_nbNs, tmp_nbNd,
                       tmp_nbRr, tmp_nbRs);
}

void File::read_robotR_prop(std::vector<std::string> lines, unsigned int& i)
{
    unsigned int j(i);
    while (i < j + m_robotS.m_nbRs)
    {
        std::istringstream current_line(lines[i]);
        double tmp_x, tmp_y;
        current_line >> tmp_x >> tmp_y;
        s_robotR_infos rRi(s_2d(tmp_x, tmp_y));
        m_robotR_vect.push_back(rRi);
        i++;
    }
}

void File::read_robotN_prop(std::vector<std::string> lines, unsigned int& i)
{
    unsigned int j(i);
    while (i < j + m_robotS.m_nbNs)
    {
        std::istringstream current_line(lines[i]);
        double tmp_x, tmp_y, tmp_a;
        int tmp_c_n, tmp_k_update_panne;
        std::string tmp_str_panne;
        current_line >> tmp_x >> tmp_y >> tmp_a >> tmp_c_n >>
                        tmp_str_panne >> tmp_k_update_panne;
        bool tmp_panne(bool(tmp_str_panne == "true"));
        s_robotN_infos rNi(s_2d(tmp_x, tmp_y), tmp_a, tmp_c_n,
                           tmp_panne, tmp_k_update_panne);
        m_robotN_vect.push_back(rNi);
        i++;
    }
}

///DEBUG
void File::show_infos()
{
    std::cout<<"PARTICULES :\n";
    for(int i = 0; i<m_particle_vect.size(); i++)
    {
        std::cout<<i+1<<")\n";
        std::cout<<"- x : "<<m_particle_vect[i].m_pos.m_x<<std::endl;
        std::cout<<"- y : "<<m_particle_vect[i].m_pos.m_y<<std::endl;
        std::cout<<"- d : "<<m_particle_vect[i].m_d<<std::endl;
    }
    std::cout<<"\nROBOT SPATIAL :\n"<<"- x : " << m_robotS.m_pos.m_x
                             <<"\n- y : " << m_robotS.m_pos.m_y
                             <<"\n- nb update : " << m_robotS.m_nb_update
                             <<"\n- nbNr : " << m_robotS.m_nbNr
                             <<"\n- nbNs : " << m_robotS.m_nbNs
                             <<"\n- nbNd : " << m_robotS.m_nbNd
                             <<"\n- nbRr : " << m_robotS.m_nbRr
                             <<"\n- nbRs : " << m_robotS.m_nbRs<<std::endl;
    std::cout<<"\nROBOT REPARATEUR : \n";
    for(int i = 0; i<m_robotR_vect.size(); i++)
    {
        std::cout<<i+1<<")\n";
        std::cout<<"- x : "<<m_robotR_vect[i].m_pos.m_x<<std::endl;
        std::cout<<"- y : "<<m_robotR_vect[i].m_pos.m_y<<std::endl;
    }

    std::cout<<"\nROBOT NEUTRALISEUR : \n";
    for(int i = 0; i<m_robotN_vect.size(); i++)
    {
        std::cout<<i+1<<")\n";
        std::cout<<"- x : "<<m_robotN_vect[i].m_pos.m_x<<std::endl;
        std::cout<<"- y : "<<m_robotN_vect[i].m_pos.m_y<<std::endl;
        std::cout<<"- angle : "<<m_robotN_vect[i].m_a<<std::endl;
        std::cout<<"- coord type : "<<m_robotN_vect[i].m_c_n<<std::endl;
        std::cout<<"- panne : "<<m_robotN_vect[i].m_panne<<std::endl;
        std::cout<<"- k_update_panne : "<<m_robotN_vect[i].m_k_update_panne<<std::endl;
    }

}

int File::get_nbP()
{
    return m_nbP;
}
s_robotS_infos File::get_robotS_infos()
{
    return m_robotS;
}
std::vector<s_robotN_infos> File::get_robotN_infos()
{
    return m_robotN_vect;
}
std::vector<s_robotR_infos> File::get_robotR_infos()
{
    return m_robotR_vect;
}
std::vector<s_particle_infos> File::get_particles_infos()
{
    return m_particle_vect;
}

