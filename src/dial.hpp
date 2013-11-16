#ifndef DIAL_H
#define DIAL_H

#include <gtkmm/drawingarea.h>
#include <gtkmm/adjustment.h>

#include <iostream>

using namespace Gtk;

enum DialType { NORMAL, LOG, DIVIDER };

class Dial: public Gtk::DrawingArea
{
	public:
		Dial(const sigc::slot<void> toggle_slot, double Value, double Min, double Max, DialType Type, double Step, int NbDigit);
		virtual ~Dial();
		bool Redraw();

		void value_changed();
		float get_value();
		void set_value(float value);
		void disable();
		void enable();

	protected:
		virtual bool on_expose_event(GdkEventExpose* event);
		virtual bool onMouseMove(GdkEventMotion* event);
		virtual bool on_button_press_event(GdkEventButton* event);
		virtual bool on_button_release_event(GdkEventButton* event);
		virtual bool onMouseScroll(GdkEventScroll * e);

	private:
		Gtk::Adjustment *m_adj;

		float m_mouseDelta;
		bool m_mouseDown;

		bool m_enabled;

		DialType m_type;
		int m_rounder;

		double CalculateLogStep();
		double RoundValue(double Value);
		void ChangeValueUp();
		void ChangeValueDown();
};

#endif
