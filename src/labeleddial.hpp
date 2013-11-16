#ifndef LABELEDDIAL_H
#define LABELEDDIAL_H

#include <gtkmm-2.4/gtkmm.h>

#include <gtkmm/drawingarea.h>
#include <gtkmm/adjustment.h>

#include <iostream>

#include "dial.hpp"

using namespace Gtk;

class LabeledDial: public Gtk::EventBox
{
	public:
		LabeledDial(const std::string TextLabel, const sigc::slot<void> toggle_slot, double Value, double Min, double Max, DialType Type, double Step, int NbDigit);
		virtual ~LabeledDial();
		bool Redraw();

		void value_changed();
		float get_value();
		void set_value(float value);
		void disable();
		void enable();

	private:
		Glib::ustring float_to_fraction(float value);
		Dial *m_dial;
		Gtk::Label *m_label;
		DialType m_type;
};

#endif

