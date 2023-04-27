/************\HEADER/*************
* AUTHORS: - Hall Axel           *
*          - Michel Lucas        *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 2.0                   *
* FILE: gui.cc                   *
*********************************/

#include <iostream>
#include <cairomm/context.h>
#include <glibmm.h>
#include "Simulation.h"
#include "gui.h"


GuiWindow::GuiWindow(Simulation *world) : 
	m_main_box(Gtk::Orientation::HORIZONTAL, 0),
 	m_interface_box(Gtk::Orientation::VERTICAL, 0),
	m_buttons_box(Gtk::Orientation::VERTICAL, 2),
	m_infos_box(Gtk::Orientation::VERTICAL, 2),//contient du texte
	m_area_aFrame(Gtk::Align::CENTER, /* center x */Gtk::Align::CENTER, /* center y */
    				1, /* xsize/ysize = 2 */true /* ignore child's aspect */),

	m_button_exit("Exit"), m_button_open("Open"),
	m_button_save("Save"), m_button_start("Start"), m_button_step("Step"),
	m_buttons_frame("General")
	
{
	// ptr to the main simulation
	ptr_world = world;
	m_area.set_world_ptr(world);
	
	//window's name
	set_title("Drawing test");

	//area frame
	m_area_aFrame.set_child(m_area);
	m_area_aFrame.set_expand();
	m_area_aFrame.set_child(m_area_frame);
	m_area_frame.set_child(m_area);


	//interface box
	m_buttons_frame.set_margin(10);
	m_buttons_frame.set_child(m_buttons_box);
	m_infos_frame.set_label("Info : nombre de ...");
	m_infos_frame.set_vexpand();
	m_infos_frame.set_margin(10);
	m_infos_frame.set_child(m_infos_box);
	m_infos_box.set_vexpand();


	m_interface_box.append(m_buttons_frame);
	m_interface_box.append(m_infos_frame);

	//main box
	set_child(m_main_box);
	m_main_box.set_expand();
	m_main_box.append(m_interface_box);
	m_main_box.append(m_area_aFrame);
	m_main_box.set_homogeneous(false);
	
	
	
	m_button_exit.set_size_request(300,0);//request une taille minimale (si possible)
	m_button_open.set_size_request(300,0);
	m_button_save.set_size_request(300,0);
	m_button_start.set_size_request(300,0);
	m_button_step.set_size_request(300,0);
	//m_buttons_box.set_size_request(400,400);//limite la taille des children (seulement largeur)

	m_buttons_box.append(m_button_exit);
	m_buttons_box.append(m_button_open);
	m_buttons_box.append(m_button_save);
	m_buttons_box.append(m_button_start);
	m_buttons_box.append(m_button_step);
	

	m_button_exit.signal_clicked().connect(sigc::mem_fun(*this, &GuiWindow::on_button_clicked_exit));
	m_button_open.signal_clicked().connect(sigc::mem_fun(*this, &GuiWindow::on_button_clicked_open));
	m_button_save.signal_clicked().connect(sigc::mem_fun(*this, &GuiWindow::on_button_clicked_save));
	m_button_start.signal_clicked().connect(sigc::mem_fun(*this, &GuiWindow::on_button_clicked_start));
	m_button_step.signal_clicked().connect(sigc::mem_fun(*this, &GuiWindow::on_button_clicked_step));

	//timer
	sigc::slot<bool()> my_slot = sigc::bind(sigc::mem_fun(*this, &GuiWindow::on_timeout));
	auto conn = Glib::signal_timeout().connect(my_slot,delta_t*1000);

}
GuiWindow::~GuiWindow()
{

}

void GuiWindow::on_button_clicked_exit()
{
	exit (EXIT_SUCCESS);
}

void GuiWindow::on_button_clicked_open()
{
	std::cout<<"on ouvre"<<std::endl;
}
void GuiWindow::on_button_clicked_save()
{
	std::cout<<"on save"<<std::endl;
}
void GuiWindow::on_button_clicked_start()
{
	std::cout<<"on start"<<std::endl;
}
void GuiWindow::on_button_clicked_step()
{
	std::cout<<"on step"<<std::endl;
	ptr_world->next_step();
	m_area.draw();
}

bool GuiWindow::on_timeout()
{
	std::cout<<"update"<<std::endl;
	std::cout<<ptr_world->get_updates()<<std::endl;
	ptr_world->next_step();
	m_area.draw();
	return true;
}

///DRAWAREA

constexpr int area_side(400);

DrawArea::DrawArea(): m_empty(false)
{
    set_content_width(area_side);
    set_content_height(area_side);
    set_draw_func(sigc::mem_fun(*this, &DrawArea::on_draw));
}

DrawArea::~DrawArea()
{

}

void DrawArea::set_world_ptr(Simulation *ptr)
{
	ptr_world = ptr;
}

void DrawArea::draw()
{
    m_empty = false;
    queue_draw();
}

void DrawArea::clear()
{
    m_empty = true;
    queue_draw();
}

void DrawArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
    if (not m_empty)
    {	
		 // center of the window
        int xc(width/2), yc(height/2);
 		 // window enlargment ratio
		double ratio(width/250.0);

 		//std::cout<<width<<" "<<height<<" "<<ratio<<std::endl;
		ptr_world->draw(cr, xc, yc, ratio);

		
	
    }
    else 
    {
        std::cout<<"EMPTY"<<std::endl;
    }
    
}
