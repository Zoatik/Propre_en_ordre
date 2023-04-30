/************|HEADER|*************
* AUTHORS: - Hall Axel (50%)     *
*          - Michel Lucas (50%)  *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 2.6                   *
* FILE: gui.cc                   *
*********************************/


#include <iostream>
#include <cairomm/context.h>
#include <glibmm.h>
#include <gtkmm/application.h>
#include "Simulation.h"
#include "gui.h"


GuiWindow::GuiWindow(bool read_success, Simulation* world = nullptr) : 
	m_area(read_success, world), m_empty(!read_success), m_running(false),
	m_main_box(Gtk::Orientation::HORIZONTAL, 0),
 	m_interface_box(Gtk::Orientation::VERTICAL, 0),
	m_buttons_box(Gtk::Orientation::VERTICAL, 2),
	m_infos_box(Gtk::Orientation::HORIZONTAL, 2),//contient du texte
	m_area_aFrame(Gtk::Align::CENTER,Gtk::Align::CENTER, 1, true),
	m_buttons_frame("General"),
	m_button_exit("Exit"), m_button_open("Open"),
	m_button_save("Save"), m_button_start("Start"), m_button_step("Step"),
	m_texts_label("mises à jour :\nparticules:\nRobots réparateurs en service:\n"
	"Robots réparateurs en réserve:\nrobots neutraliseurs en service:\n"
	"robots neutraliseurs en panne:\nrobots neutraliseurs détruits:\n"
	"robots neutraliseurs en réserve:")
{
	// pointeur partagé du monde
	m_ptr_world = std::shared_ptr<Simulation>(world);
	
	//window's name
	set_title("Propre En Ordre");

	//area frame
	m_area_aFrame.set_child(m_area);
	m_area_aFrame.set_expand();
	m_area_aFrame.set_child(m_area);

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

	m_buttons_box.append(m_button_exit);
	m_buttons_box.append(m_button_open);
	m_buttons_box.append(m_button_save);
	m_buttons_box.append(m_button_start);
	m_buttons_box.append(m_button_step);
	update_users_buttons();
	
	m_button_exit.signal_clicked().connect(
		sigc::mem_fun(*this, &GuiWindow::on_button_clicked_exit));
	m_button_open.signal_clicked().connect(
		sigc::mem_fun(*this, &GuiWindow::on_button_clicked_open));
	m_button_save.signal_clicked().connect(
		sigc::mem_fun(*this, &GuiWindow::on_button_clicked_save));
	m_button_start.signal_clicked().connect(
		sigc::mem_fun(*this, &GuiWindow::on_button_clicked_start));
	m_button_step.signal_clicked().connect(
		sigc::mem_fun(*this, &GuiWindow::on_button_clicked_step));

	//timer
	sigc::slot<bool()> my_slot = sigc::bind(
		sigc::mem_fun(*this, &GuiWindow::on_timeout));
	auto conn = Glib::signal_timeout().connect(my_slot,delta_t*1000);
	//events
    auto controller = Gtk::EventControllerKey::create();
    controller->signal_key_pressed().connect(
                  sigc::mem_fun(*this, &GuiWindow::on_window_key_pressed), false);
    add_controller(controller);
}

GuiWindow::~GuiWindow()
{
	//dtor
}

void GuiWindow::on_button_clicked_exit()
{
	exit (EXIT_SUCCESS);
}

void GuiWindow::on_button_clicked_open()
{
	auto dialog = new Gtk::FileChooserDialog(*this, "Please choose a file",
	Gtk::FileChooser::Action::OPEN, true);
	dialog->set_transient_for(*this);
	dialog->set_modal(true);
	dialog->signal_response().connect(sigc::bind(
	sigc::mem_fun(*this, &GuiWindow::on_file_open_dialog_response),
	dialog));

	//response buttons
	dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
	dialog->add_button("_Open", Gtk::ResponseType::OK);

	//filtres
	auto filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Text files");
	filter_text->add_pattern("*.txt");
	dialog->add_filter(filter_text);

	auto filter_any = Gtk::FileFilter::create();
	filter_any->set_name("Any files");
	filter_any->add_pattern("*");
	dialog->add_filter(filter_any);

	dialog->show();
}

void GuiWindow::on_file_open_dialog_response(int response_id,
 											Gtk::FileChooserDialog* dialog)
{
	switch (response_id)
	{
		case Gtk::ResponseType::OK: 
		{
			auto filename = dialog->get_file()->get_path();
			m_ptr_world->clear();
			m_empty = !m_ptr_world->read_file(filename);
			m_area.set_emptiness(m_empty);
			m_area.queue_draw();
			refresh_label_values();
			update_users_buttons();
			break;
		}
		case Gtk::ResponseType::CANCEL:
		{
			break;
		}
		default:
		{
			std::cout << "Unexpected button clicked." << std::endl;
			break;
		}
	}
	dialog->hide();
} 

void GuiWindow::on_button_clicked_save()
{
	auto dialog = new Gtk::FileChooserDialog(*this, "Save a file",
											 Gtk::FileChooser::Action::SAVE, true);
	dialog->set_transient_for(*this);
	dialog->set_modal(true);
	dialog->set_current_name("untitled.txt");
	dialog->signal_response().connect(sigc::bind(
	sigc::mem_fun(*this, &GuiWindow::on_file_save_dialog_response),
	dialog));

	//response buttons
	dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
	dialog->add_button("_Save", Gtk::ResponseType::OK);

	//filtres
	auto filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Text files");
	filter_text->add_pattern("*.txt");
	dialog->add_filter(filter_text);

	auto filter_any = Gtk::FileFilter::create();
	filter_any->set_name("Any files");
	filter_any->add_pattern("*");
	dialog->add_filter(filter_any);

	dialog->show();
}

void GuiWindow::on_file_save_dialog_response(int response_id,
 											Gtk::FileChooserDialog* dialog)
{
	switch (response_id)
	{
		case Gtk::ResponseType::OK: 
		{
			auto filename = dialog->get_file()->get_path();	
			m_ptr_world->write_file(filename);
			break;
		}
		case Gtk::ResponseType::CANCEL:
		{
			break;
		}
		default:
		{
			std::cout << "Unexpected button clicked." << std::endl;
			break;
		}
	}
	dialog->hide();
} 

void GuiWindow::on_button_clicked_start()
{	
	if(!m_empty)
	{
		if(!m_running)
		{
			m_running = true;
			m_button_start.set_label("Stop");
			m_button_open.set_sensitive(false);
			m_button_save.set_sensitive(false);
			m_button_step.set_sensitive(false);

		}
		else
		{
			m_running = false;
			m_button_start.set_label("Start");
			m_button_open.set_sensitive(true);
			m_button_save.set_sensitive(true);
			m_button_step.set_sensitive(true);
		}
	}
}

void GuiWindow::on_button_clicked_step()
{	
	if(!m_empty and !m_running)
	{
		m_ptr_world->next_step();
		m_area.queue_draw();
		refresh_label_values();
	}
}

bool GuiWindow::on_timeout()
{	
	if(!m_empty and m_running)
	{
		m_ptr_world->next_step();
		m_area.queue_draw();
		refresh_label_values();
	}
	return true;
}

bool GuiWindow::on_window_key_pressed(guint keyval, guint, Gdk::ModifierType state)
{
	switch(gdk_keyval_to_unicode(keyval))
	{
		case 's':
			on_button_clicked_start();
			return true;
		case '1':
			on_button_clicked_step();
			return true;
	}
    //the event has not been handled
    return false;
}

void GuiWindow::refresh_label_values()
{	
	if(!m_empty) 
	{
		m_values_label.set_label(
		std::to_string(m_ptr_world->get_updates())+"\n"+
		std::to_string(m_ptr_world->get_nbP())+"\n"+
		std::to_string(m_ptr_world->get_robotS().get_nbRs())+"\n"+
		std::to_string(m_ptr_world->get_robotS().get_nbRr())+"\n"+
		std::to_string(m_ptr_world->get_robotS().get_nbNs())+"\n"+
		std::to_string(m_ptr_world->get_robotS().get_nbNp())+"\n"+
		std::to_string(m_ptr_world->get_robotS().get_nbNd())+"\n"+
		std::to_string(m_ptr_world->get_robotS().get_nbNr()));
	}
	else
		m_values_label.set_label("-\n-\n-\n-\n-\n-\n-\n-\n-");
}

void GuiWindow::update_users_buttons()
{
	bool is_active = !m_empty;
	m_button_save.set_sensitive(is_active);
	m_button_start.set_sensitive(is_active);
	m_button_step.set_sensitive(is_active);
}

///DRAWAREA
constexpr unsigned taille_dessin(500); 

DrawArea::DrawArea(bool read_success, Simulation *ptr_world): m_empty(!read_success),
															  m_ptr_world(ptr_world)
{
    set_content_width(taille_dessin);
    set_content_height(taille_dessin);
    set_draw_func(sigc::mem_fun(*this, &DrawArea::on_draw));
}

DrawArea::~DrawArea()
{
	//dtor
}

void DrawArea::set_world_ptr(std::shared_ptr<Simulation>& ptr_world)
{
	m_ptr_world = ptr_world;
}

void DrawArea::set_emptiness(bool is_empty)
{
	m_empty = is_empty;
}

void DrawArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
    if (!m_empty)
    {	
		graphic_set_context(cr);
		// center of the window
        int xc(width/2), yc(height/2);
 		// window enlargment ratio
		double ratio(width/(2*dmax));

		m_ptr_world->draw(xc, yc, ratio);
    }
    else 
    {
        std::cout<<"EMPTY"<<std::endl;
    }  
}
