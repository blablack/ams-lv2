#include <gtkmm-2.4/gtkmm.h>

#include "my_box.hpp"

using namespace Gtk;

MyBox::MyBox(const Glib::ustring& label, Gtk::Orientation orientation): Frame(label)
{
	this->set_shadow_type(Gtk::ShadowType::SHADOW_ETCHED_OUT);

	Label *p_label = manage (new Label("<b> " + label + " </b>"));
	p_label->set_use_markup(true);
	this->set_label_widget(*p_label);

	switch(orientation)
	{
		case Gtk::Orientation::ORIENTATION_VERTICAL:
			p_child = manage(new VBox());
			p_child->set_homogeneous(false);
			this->add(*p_child);
			break;
		case Gtk::Orientation::ORIENTATION_HORIZONTAL:
			Alignment* p_align = new Alignment(0.5, 0.5, 1, 0);
			p_child = manage(new HBox());
			p_child->set_homogeneous(true);
			p_align->add(*p_child);
			this->add(*p_align);
			break;
	}

	this->set_border_width(2);
}

void MyBox::pack_start(Widget& child)
{
	p_child->pack_start(child, Gtk::PACK_EXPAND_PADDING, 0);
}

