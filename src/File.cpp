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
//méthodes

bool File::read_file(std::string file_path)
{
    s_sim_infos sim_infos;
    std::string line;
    std::vector<std::string> lines;
    std::ifstream file(file_path);
    if(file.is_open())
    {
        while(file)
        {
            std::getline(file,line);
            lines.push_back(line);
        }
    }
    else
    {
        std::cout<<"Could not open file\n";
        return false;
    }
    file.close();

    int line_type(0);//0: infos particules, 1: ' robot spatial, 2: '' réparateur, 3: neutraliseur
    for(unsigned int i(0); i<lines.size(); i++)
    {
        std::istringstream current_line(lines[i]);
        std::string spec;
        current_line >> spec;
        if(spec == "#" || lines[i].size()==0)//on saute la ligne si # ou si vide
                continue;
        if(line_type == 0)
        {
            sim_infos.m_nbP = std::stoi(spec);
            unsigned int j(i);
            i++;
            while(i<=j+sim_infos.m_nbP)//on boucle sur le nb de particules
            {
                current_line = std::istringstream(lines[i]);
                double tmp_x, tmp_y, tmp_d;
                current_line >> tmp_x >> tmp_y >> tmp_d;
                //std::cout<<tmp_x<<"/"<<tmp_y<<"/"<<tmp_d<<"\n";
                s_particle_infos part(tmp_x, tmp_y, tmp_d);
                this->s_particle_vect.push_back(part);
                i++;
            }
            line_type = 1;// on passe au type suivant
        }
        else if(line_type == 1)
        {
            current_line = std::istringstream(lines[i]);
            double tmp_x, tmp_y;
            int tmp_nbUpdate, tmp_nbNr, tmp_nbNs, tmp_nbNd, tmp_nbRr, tmp_nbRs;
            current_line >> tmp_x >> tmp_y >> tmp_nbUpdate >> tmp_nbNr >> tmp_nbNs >>
                            tmp_nbNd >> tmp_nbRr >> tmp_nbRs;
            s_robotS_infos rSi(tmp_x,tmp_y,
                               tmp_nbUpdate, tmp_nbNr,
                               tmp_nbNs, tmp_nbNd,
                               tmp_nbRr, tmp_nbRs);
            this->s_robotS = rSi;
            line_type = 2;
        }
        else if(line_type == 2)
        {
            unsigned int j(i);
            while(i<j+this->s_robotS.m_nbRs)
            {
                current_line = std::istringstream(lines[i]);
                double tmp_x, tmp_y;
                current_line >> tmp_x >> tmp_y;
                s_robotR_infos rRi(tmp_x, tmp_y);
                this->s_robotR_vect.push_back(rRi);
                i++;
            }
            line_type = 3;
        }
        else if(line_type == 3)
        {
            unsigned int j(i);
            while(i<j+this->s_robotS.m_nbNs)
            {
                current_line = std::istringstream(lines[i]);
                double tmp_x, tmp_y, tmp_a;
                int tmp_c_n, tmp_k_update_panne;
                std::string tmp_str_panne;
                std::cout<<i<<std::endl;
                if (lines[i].size() == 0)
                    std::cout<<"emptyyy"<<std::endl;
                current_line >> tmp_x >> tmp_y >> tmp_a >> tmp_c_n >>
                                tmp_str_panne >> tmp_k_update_panne;
                bool tmp_panne(bool(tmp_str_panne=="true"));
                s_robotN_infos rNi(tmp_x, tmp_y, tmp_a, tmp_c_n, tmp_panne, tmp_k_update_panne);
                this->s_robotN_vect.push_back(rNi);
                i++;
            }
        }

        //std::cout<<i<<std::endl;
    }
    //std::cout<<"on sort"<<std::endl;
    this->show_infos();
    return true;
}

///DEBUG
void File::show_infos()
{
    std::cout<<"PARTICULES :\n";
    for(int i = 0; i<this->s_particle_vect.size(); i++)
    {
        std::cout<<i+1<<")\n";
        std::cout<<"- x : "<<this->s_particle_vect[i].m_x<<std::endl;
        std::cout<<"- y : "<<this->s_particle_vect[i].m_y<<std::endl;
        std::cout<<"- d : "<<this->s_particle_vect[i].m_d<<std::endl;
    }
    std::cout<<"\nROBOT SPATIAL :\n"<<"- x : " << this->s_robotS.m_x
                             <<"\n- y : " << this->s_robotS.m_y
                             <<"\n- nb update : " << this->s_robotS.m_nb_update
                             <<"\n- nbNr : " << this->s_robotS.m_nbNr
                             <<"\n- nbNs : " << this->s_robotS.m_nbNs
                             <<"\n- nbNd : " << this->s_robotS.m_nbNd
                             <<"\n- nbRr : " << this->s_robotS.m_nbRr
                             <<"\n- nbRs : " << this->s_robotS.m_nbRs<<std::endl;
    std::cout<<"\nROBOT REPARATEUR : \n";
    for(int i = 0; i<this->s_robotR_vect.size(); i++)
    {
        std::cout<<i+1<<")\n";
        std::cout<<"- x : "<<this->s_robotR_vect[i].m_x<<std::endl;
        std::cout<<"- y : "<<this->s_robotR_vect[i].m_y<<std::endl;
    }

    std::cout<<"\nROBOT NEUTRALISEUR : \n";
    for(int i = 0; i<this->s_robotN_vect.size(); i++)
    {
        std::cout<<i+1<<")\n";
        std::cout<<"- x : "<<this->s_robotN_vect[i].m_x<<std::endl;
        std::cout<<"- y : "<<this->s_robotN_vect[i].m_y<<std::endl;
        std::cout<<"- angle : "<<this->s_robotN_vect[i].m_a<<std::endl;
        std::cout<<"- coord type : "<<this->s_robotN_vect[i].m_c_n<<std::endl;
        std::cout<<"- panne : "<<this->s_robotN_vect[i].m_panne<<std::endl;
        std::cout<<"- k_update_panne : "<<this->s_robotN_vect[i].m_k_update_panne<<std::endl;
    }

}
