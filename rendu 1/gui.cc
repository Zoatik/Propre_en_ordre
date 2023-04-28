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


GuiWindow::GuiWindow(Simulation* world = NULL) : 
	m_main_box(Gtk::Orientation::HORIZONTAL, 0),
 	m_interface_box(Gtk::Orientation::VERTICAL, 0),
	m_buttons_box(Gtk::Orientation::VERTICAL, 2),
	m_infos_box(Gtk::Orientation::HORIZONTAL, 2),//contient du texte
	m_area_aFrame(Gtk::Align::CENTER, /* center x */Gtk::Align::CENTER, /* center y */
    				1, /* xsize/ysize = 2 */true /* ignore child's aspect */),

	m_button_exit("Exit"), m_button_open("Open"),
	m_button_save("Save"), m_button_start("Start"), m_button_step("Step"),
	m_buttons_frame("General"), m_area(world), m_running(false),
	m_texts_label("mises à jour :\nparticules:\nRobots réparateurs en service:\n"
	"Robots réparateurs en réserve:\nrobots neutraliseurs en service:\n"
	"robots neutraliseurs en panne:\nrobots neutraliseurs détruits:\n"
	"robots neutraliseurs en réserve:")
{
	// ptr to the main simulation
	m_ptr_world = std::shared_ptr<Simulation>(world);
	//m_area.set_world_ptr(m_ptr_world);//On partage le pointer avec DrawArea
	
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
	m_infos_frame.set_margin(10);
	m_infos_frame.set_child(m_infos_box);
	refresh_label_values();
	m_infos_box.append(m_texts_label);
	m_infos_box.append(m_values_label);


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
	//events
    auto controller = Gtk::EventControllerKey::create();
    controller->signal_key_pressed().connect(
                  sigc::mem_fun(*this, &GuiWindow::on_window_key_pressed), false);
    add_controller(controller);
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
	auto dialog = new Gtk::FileChooserDialog("Please choose a file",
	Gtk::FileChooser::Action::OPEN);
	dialog->set_transient_for(*this);
	dialog->set_modal(true);
	dialog->signal_response().connect(sigc::bind(
	sigc::mem_fun(*this, &GuiWindow::on_file_dialog_response),
	dialog));

	//Add response buttons to the dialog:
	dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
	dialog->add_button("_Open", Gtk::ResponseType::OK);

	//Add filters, so that only certain file types can be selected:

	auto filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Text files");
	filter_text->add_mime_type("text/plain");
	dialog->add_filter(filter_text);

	auto filter_cpp = Gtk::FileFilter::create();
	filter_cpp->set_name("C/C++ files");
	filter_cpp->add_mime_type("text/x-c");
	filter_cpp->add_mime_type("text/x-c++");
	filter_cpp->add_mime_type("text/x-c-header");
	dialog->add_filter(filter_cpp);

	auto filter_any = Gtk::FileFilter::create();
	filter_any->set_name("Any files");
	filter_any->add_pattern("*");
	dialog->add_filter(filter_any);

	dialog->show();
}
void GuiWindow::on_file_dialog_response(int response_id,
 											Gtk::FileChooserDialog* dialog)
{
	//Handle the response:
	switch (response_id)
	{
		case Gtk::ResponseType::OK:
		{
			std::cout << "Open clicked." << std::endl;

			//Notice that this is a std::string, not a Glib::ustring.
			auto filename = dialog->get_file()->get_path();
			std::cout << "File selected: " << filename << std::endl;
			break;
		}
			case Gtk::ResponseType::CANCEL:
		{
			std::cout << "Cancel clicked." << std::endl;
			break;
		}
			default:
		{
			std::cout << "Unexpected button clicked." << std::endl;
			break;
		}
	}
	delete dialog;
} 
void GuiWindow::on_button_clicked_save()
{
	std::cout<<"on save"<<std::endl;
}
void GuiWindow::on_button_clicked_start()
{	
	if(not m_running)
	{
		std::cout<<"on start"<<std::endl;
		m_running = true;
		m_button_start.set_label("Stop");
	}else{
		std::cout<<"on stop"<<std::endl;
		m_running = false;
		m_button_start.set_label("Start");
	}
	
}
void GuiWindow::on_button_clicked_step()
{	
	if(not m_running)
	{
		std::cout<<"on step"<<std::endl;
		m_ptr_world->next_step();
		m_area.draw();
		refresh_label_values();
	}
}

bool GuiWindow::on_timeout()
{	
	if(m_running)
	{
		std::cout<<"update"<<std::endl;
		std::cout<<m_ptr_world->get_updates()<<std::endl;
		m_ptr_world->next_step();
		m_area.draw();
		refresh_label_values();
	}
	return true;
}

bool GuiWindow::on_window_key_pressed(guint keyval, guint, Gdk::ModifierType state)
{
	switch(gdk_keyval_to_unicode(keyval))
	{
		case 'w':
			std::cout << " Waow! key 'w' has been pressed !" << std::endl;
			return true;
		case 'c':
			std::cout << " action sur le lable du bouton Clear" 
				      << std::endl;
			return true;
		case 'C':
			std::cout << " action sur le lable du bouton Clear" 
				      << std::endl;
			return true;
		case 'q':
			std::cout << "Quit" << std::endl;
			return true;
	}
    //the event has not been handled
    return false;
}

void GuiWindow::refresh_label_values()
{	
	if(not m_ptr_world->get_emptiness()) 
	{
		m_values_label.set_label(
		std::to_string(m_ptr_world->get_updates())+"\n"+
		std::to_string(m_ptr_world->get_nbP())+"\n"+
		std::to_string(m_ptr_world->get_robotS().get_nbRs())+"\n"+
		std::to_string(m_ptr_world->get_robotS().get_nbRr())+"\n"+
		std::to_string(m_ptr_world->get_robotS().get_nbNs())+"\n"+
		std::to_string(m_ptr_world->get_robotS().get_nbNp())+"\n"+
		std::to_string(m_ptr_world->get_robotS().get_nbNd())+"\n"+
		std::to_string(m_ptr_world->get_robotS().get_nbNr())
		);
	}else{
		m_values_label.set_label("-\n-\n-\n-\n-\n-\n-\n-\n-");
	}
	
}

///DRAWAREA

constexpr int area_side(400);

DrawArea::DrawArea(Simulation *ptr_world): m_ptr_world(ptr_world)
{
    set_content_width(area_side);
    set_content_height(area_side);
    set_draw_func(sigc::mem_fun(*this, &DrawArea::on_draw));
}

DrawArea::~DrawArea()
{

}

void DrawArea::set_world_ptr(std::shared_ptr<Simulation>& ptr_world)
{
	m_ptr_world = ptr_world;
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
	
    if (not m_ptr_world->get_emptiness())
    {	
		
		 // center of the window
        int xc(width/2), yc(height/2);
 		 // window enlargment ratio
		double ratio(width/250.0);
		

 		//std::cout<<width<<" "<<height<<" "<<ratio<<std::endl;
		m_ptr_world->draw(cr, xc, yc, ratio);
	
    }
    else 
    {
        std::cout<<"EMPTY"<<std::endl;
    }
    
}
