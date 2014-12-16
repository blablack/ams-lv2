#include <gtkmm/drawingarea.h>
#include <gtkmm/adjustment.h>

#include "dial.hpp"

Dial::Dial(double Min, double Max, DialType Type, double Step)
{
	m_enabled = true;
	m_type = Type;
	m_adj = new Gtk::Adjustment(Min, Min, Max, Step, Step);

	m_scrollStep = 1;
	if((Max-Min)/Step>100)
		m_scrollStep = 5;
	else if((Max-Min)/Step>250)
		m_scrollStep = 10;
	else if((Max-Min)/Step>500)
		m_scrollStep = 15;

	this->m_mouseDelta = 0;
	this->m_mouseDown = false;

	add_events(Gdk::EXPOSURE_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK| Gdk::POINTER_MOTION_MASK);
	signal_button_press_event().connect(sigc::mem_fun(*this, &Dial::on_button_press_event) );
	signal_button_release_event().connect(sigc::mem_fun(*this, &Dial::on_button_release_event) );
	signal_motion_notify_event().connect(sigc::mem_fun( *this, &Dial::onMouseMove) );
	signal_scroll_event().connect(sigc::mem_fun( *this, &Dial::onMouseScroll) );

	set_size_request(38, 32);

	m_adj->signal_value_changed().connect(mem_fun(*this, &Dial::value_changed));

	double p_afterComa = Step - int(Step);
	std::ostringstream strs;
	strs << p_afterComa;
	std::string str = strs.str();

	if(p_afterComa == 0.0)
		m_nbDigit = 0;
	else
		m_nbDigit = str.length() - 2;

	m_rounder = (int)pow(10, m_nbDigit);
}

Glib::SignalProxy0<void> Dial::signal_value_changed()
{
	return m_adj->signal_value_changed();
}

void Dial::enable()
{
	if(!m_enabled)
	{
		m_enabled = true;
		Redraw();
	}
}

void Dial::disable()
{
	if(m_enabled)
	{
		m_enabled = false;
		Redraw();
	}
}

void Dial::value_changed()
{
	Redraw();
}

float Dial::get_value()
{
	return m_adj->get_value();
}

void Dial::set_value(float Value)
{
	m_adj->set_value(Value);
	Redraw();
}

int Dial::getNbDigit()
{
	return m_nbDigit;
}

bool Dial::on_expose_event(GdkEventExpose* event)
{
	Glib::RefPtr<Gdk::Window> window = get_window();
	if (window)
	{
		Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

		cr->set_source_rgb(0.118, 0.133, 0.141);
		cr->paint();

		cr->set_source_rgb(0.0, 0.8, 0.0);

		cr->rectangle((double)event->area.x, (double)event->area.y, (double)event->area.width, (double)event->area.height);
		cr->clip();

		Gtk::Allocation allocation = get_allocation();
		const int width = allocation.get_width();
		const int height = allocation.get_height();

		int xc = width/2;
		int yc = height/2 + 3;

		float radius = 14;

		cr->set_line_cap(Cairo::LINE_CAP_ROUND);
		cr->set_line_join(Cairo::LINE_JOIN_ROUND);
		cr->set_line_width(2.8);

		// Arc Angle Value
		cr->set_line_width(2.4);
		cr->move_to(xc, yc);
		cr->set_source_rgba(0, 0, 0, 0);
		cr->stroke();

		cr->set_source_rgba(  66 / 255.f,  66 / 255.f ,  66 / 255.f , 1.f );

		cr->arc(xc, yc, radius, 2.46, 0.75);
		cr->move_to(xc, yc);
		cr->stroke();

		cr->set_line_width(2.8);
		float angle;
		if(m_type != MULTIPLIER)
		{
			angle = 2.46 + (4.54 * ((m_adj->get_value()-m_adj->get_lower()) / (m_adj->get_upper()-m_adj->get_lower())));
		}
		else
		{
			if(m_adj->get_value() <= 0.0078125)
				angle = 2.46 + 4.54 * 0 / 14;
			else if(m_adj->get_value() <= 0.015625)
				angle = 2.46 + 4.54 * 1 / 14;
			else if(m_adj->get_value() <= 0.03125)
				angle = 2.46 + 4.54 * 2 / 14;
			else if(m_adj->get_value() <= 0.0625)
				angle = 2.46 + 4.54 * 3 / 14;
			else if(m_adj->get_value() <= 0.125)
				angle = 2.46 + 4.54 * 4 / 14;
			else if(m_adj->get_value() <= 0.25)
				angle = 2.46 + 4.54 * 5 / 14;
			else if(m_adj->get_value() <= 0.5)
				angle = 2.46 + 4.54 * 6 / 14;
			else if(m_adj->get_value() <= 1)
				angle = 2.46 + 4.54 * 7 / 14;
			else if(m_adj->get_value() <= 2)
				angle = 2.46 + 4.54 * 8 / 14;
			else if(m_adj->get_value() <= 4)
				angle = 2.46 + 4.54 * 9 / 14;
			else if(m_adj->get_value() <= 8)
				angle = 2.46 + 4.54 * 10 / 14;
			else if(m_adj->get_value() <= 16)
				angle = 2.46 + 4.54 * 11 / 14;
			else if(m_adj->get_value() <= 32)
				angle = 2.46 + 4.54 * 12 / 14;
			else if(m_adj->get_value() <= 64)
				angle = 2.46 + 4.54 * 13 / 14;
			else if(m_adj->get_value() > 64)
				angle = 2.46 + 4.54 * 14 / 14;
		}

		if(m_enabled)
			cr->set_source_rgba( 255 / 255.f, 104 / 255.f , 0 / 255.f , 1.f );
		else
			cr->set_source_rgba( 66 / 255.f, 66 / 255.f , 66 / 255.f , 1.f );

		float zero_angle;
		cr->set_line_width(1.7);
		if(!(m_adj->get_lower() < 0.0 && m_adj->get_upper() > 0.0))
		{
			cr->arc(xc, yc, 13, 2.46, angle);
		}
		else
		{
			if(angle >= 4.73)
				cr->arc(xc, yc, 13, 4.73, angle);
			else
				cr->arc_negative(xc, yc, 13, 4.73, angle);
		}
		cr->line_to(xc, yc);
		cr->stroke();
		if(!(m_adj->get_lower() < 0.0 && m_adj->get_upper() > 0.0))
		{
			cr->arc(xc, yc, 17, 2.46, angle);
		}
		else
		{
			if(angle >= 4.73)
				cr->arc(xc, yc, 17, 4.73, angle);
			else
				cr->arc_negative(xc, yc, 17, 4.73, angle);
		}
		cr->line_to(xc,yc);
		cr->stroke();
	}
	return true;
}

bool Dial::Redraw()
{
	Glib::RefPtr<Gdk::Window> win = get_window();
	if (win)
	{
		Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
		win->invalidate_rect(r, false);
	}
	return true;
}

double Dial::CalculateLogStep()
{
	double p_perc = (m_adj->get_value() - m_adj->get_lower()) / (m_adj->get_upper() - m_adj->get_lower()) * 1000;
	return m_adj->get_step_increment() + (m_adj->get_step_increment() * p_perc);
}

double Dial::RoundValue(double Value)
{
	return floorf(Value * m_rounder + 0.5) / m_rounder;
}

double Dial::MultValue(double Value)
{
	if(Value <= 0.0078125)
		return (0.0078125);
	else if(Value <= 0.015625)
		return (0.015625);
	else if(Value <= 0.03125)
		return (0.03125);
	else if(Value <= 0.0625)
		return (0.0625);
	else if(Value <= 0.125)
		return (0.125);
	else if(Value <= 0.25)
		return (0.25);
	else if(Value <= 0.5)
		return (0.5);
	else if(Value <= 1)
		return (1);
	else if(Value <= 2)
		return (2);
	else if(Value <= 4)
		return (4);
	else if(Value <= 8)
		return (8);
	else if(Value <= 16)
		return (16);
	else if(Value <= 32)
		return (32);
	else if(Value <= 64)
		return (64);
	else if(Value > 64)
		return (128);
}

bool Dial::onMouseScroll(GdkEventScroll * e)
{
	if(m_enabled)
	{
		if (e->direction == GDK_SCROLL_UP)
			if(m_type != MULTIPLIER)
				for(int i = 0 ; i<m_scrollStep ; i++)
					ChangeValueUp();
			else
				ChangeValueUp();
		else if (e->direction == GDK_SCROLL_DOWN)
			if(m_type != MULTIPLIER)
				for(int i = 0 ; i<m_scrollStep ; i++)
					ChangeValueDown();
			else
				ChangeValueDown();

		return true;
	}
	else
		return false;
}

bool Dial::onMouseMove(GdkEventMotion* event)
{
	if (m_mouseDown && m_enabled)
	{
		if(m_adj->get_value()<m_adj->get_upper() && m_mouseDelta>(event->y + 5))
		{
			ChangeValueUp();
			m_mouseDelta = event->y;
		}
		else if(m_adj->get_value()>m_adj->get_lower() && m_mouseDelta<(event->y - 5))
		{
			ChangeValueDown();
			m_mouseDelta = event->y;
		}
		Redraw();

		return true;
	}
	else
	{
		return false;
	}
}

void Dial::ChangeValueUp()
{
	switch(m_type)
	{
		case NORMAL:
			set_value(RoundValue(m_adj->get_value()+m_adj->get_step_increment()));
			break;
		case LOG:
			set_value(RoundValue(m_adj->get_value()+CalculateLogStep()));
			break;
		case MULTIPLIER:
			set_value(MultValue(m_adj->get_value()*2));
			break;
	}
}
void Dial::ChangeValueDown()
{
	switch(m_type)
	{
		case NORMAL:
			set_value(RoundValue(m_adj->get_value()-m_adj->get_step_increment()));
			break;
		case LOG:
			set_value(RoundValue(m_adj->get_value()-CalculateLogStep()));
			break;
		case MULTIPLIER:
			set_value(MultValue(m_adj->get_value()/2));
			break;
	}
}

bool Dial::on_button_press_event(GdkEventButton* event)
{
	if( event->type == GDK_BUTTON_PRESS ) // && event->button == 3
	{
		m_mouseDown = true; // for pointer motion "drag" operations
		m_mouseDelta = event->y;
		return true;
	}
	else
	{
		return false;
	}
}

bool Dial::on_button_release_event(GdkEventButton* event)
{
	if( event->type == GDK_BUTTON_RELEASE  ) // && event->button == 3
	{
		m_mouseDown = false;
		return true; //It's been handled.
	}
	else
	{
		return false;
	}
}
