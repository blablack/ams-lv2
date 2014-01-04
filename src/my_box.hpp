#ifndef BOX_H
#define BOX_H

#include <gtkmm-2.4/gtkmm.h>

#include <iostream>

using namespace Gtk;

class MyBox: public Gtk::Frame
{
    public:
        MyBox(const Glib::ustring& label, Gtk::Orientation orientation);
        virtual ~MyBox();

        void pack_start(Widget& child);

    private:
        Box* p_child;
};

#endif
