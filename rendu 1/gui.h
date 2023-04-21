#ifndef GUI_H
#define GUI_H

/***************************************
/nom du fichier : gui.h
/auteurs        : - Axel Hall - 346228
/				  - Lucas Michel - 363073
/version        : 1.1
****************************************/
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/aspectframe.h>
#include <gtkmm/label.h>
#include <gtkmm/drawingarea.h>
#include "graphic.h"

class DrawArea : public Gtk::DrawingArea // héritage
{
public:
    DrawArea();
    virtual ~DrawArea();

    void draw();
    void clear();
protected:
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

private:
    bool m_empty;

};

class GuiWindow: public Gtk::Window
{
public:
    GuiWindow();
    ~GuiWindow() override;
protected:
    void on_button_clicked_exit();
	void on_button_clicked_open();
	void on_button_clicked_save();
	void on_button_clicked_start();
	void on_button_clicked_step();

	DrawArea m_area;

	Gtk::Frame m_area_frame;
	Gtk::AspectFrame m_area_aFrame;
	Gtk::Frame m_main_frame;
	Gtk::Box m_main_box;
	Gtk::Box m_interface_box;
	Gtk::Box m_buttons_box;	
	Gtk::Box m_infos_box;
	Gtk::Frame m_buttons_frame;	
	Gtk::Frame m_infos_frame;
	Gtk::Button m_button_exit;
	Gtk::Button m_button_open;
	Gtk::Button m_button_save;
	Gtk::Button m_button_start;
	Gtk::Button m_button_step;
};




#endif //GUI_H