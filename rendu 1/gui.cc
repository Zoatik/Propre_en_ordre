#include <iostream>
#include <cairomm/context.h>
#include "Simulation.h"
#include "gui.h"


/***************************************
/nom du fichier : gui.cc
/auteurs        : - Axel Hall - 346228
/				  - Lucas Michel - 363073
/version        : 1.1
****************************************/

GuiWindow::GuiWindow(Simulation world) : 
	m_button_exit("Exit"), m_button_open("Open"),
	m_button_save("Save"), m_button_start("Start"), m_button_step("Step"),
	m_buttons_frame("General"),
	m_main_box(Gtk::Orientation::HORIZONTAL, 0),
 	m_interface_box(Gtk::Orientation::VERTICAL, 0),
	m_buttons_box(Gtk::Orientation::VERTICAL, 2),
	m_infos_box(Gtk::Orientation::VERTICAL, 2),//contient du texte
	m_area_aFrame(Gtk::Align::CENTER, /* center x */Gtk::Align::CENTER, /* center y */
    				1, /* xsize/ysize = 2 */true /* ignore child's aspect */)
{
	m_world = world;
	set_title("Drawing test");
	//set_resizable(false);
	set_child(m_main_box);
	m_area_frame.set_child(m_area_aFrame);

	//m_main_frame.set_child(m_main_box);
	//m_main_frame.set_halign(Gtk::Align::START);
	//m_main_frame.set_expand();
	m_main_box.set_expand();
	m_area_frame.set_expand();
	m_area_frame.set_margin(10);
	
	
	//m_buttons_frame.set_label(Gtk::Label("General"));
	m_buttons_frame.set_margin(10);
	m_buttons_frame.set_child(m_buttons_box);
	m_infos_frame.set_label("Info : nombre de ...");
	m_infos_frame.set_margin(10);
	m_infos_frame.set_child(m_infos_box);

	
	m_interface_box.append(m_buttons_frame);
	m_interface_box.append(m_infos_frame);

	m_area_aFrame.set_child(m_area);
	//m_area_frame.set_expand();
	//m_main_box.set_expand();
	/*m_area_frame.set_halign(Gtk::Align::CENTER);
	m_interface_box.set_halign(Gtk::Align::START);
	m_main_box.set_halign(Gtk::Align::CENTER);*/

	m_main_box.append(m_interface_box);
	m_main_box.append(m_area_frame);
	m_main_box.set_homogeneous(false);
	m_main_box.set_vexpand();
	
	
	
	
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
}

///DRAWAREA

constexpr int area_side(200);

DrawArea::DrawArea(): m_empty(false)
{
    set_content_width(area_side);
    set_content_height(area_side);
    set_draw_func(sigc::mem_fun(*this, &DrawArea::on_draw));
}

DrawArea::~DrawArea()
{

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
	/*for(auto i : m_world)
	{

	}*/
    if (not m_empty)
    {
        // center of the window
        int xc(width/2), yc(height/2);
        cr->set_line_width(10.0);
        // draw red lines out from the center of the window
        cr->set_source_rgb(0.8, 0.0, 0.0);
        cr->move_to(0, 0);
        cr->line_to(xc, yc);
        cr->line_to(0, height);
        cr->move_to(xc, yc);
        cr->line_to(width, yc);
        cr->stroke();
		cr->arc(xc, yc, 20, 0.0, 2.0 * M_PI);
		cr->stroke();
    }
    else 
    {
        std::cout<<"EMPTY"<<std::endl;
    }
    
}
