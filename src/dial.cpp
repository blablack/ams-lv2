#include <cairomm/context.h>
#include <math.h>

#include "dial.hpp"

using namespace std;

Dial::Dial(const sigc::slot<void> toggle_slot, double Value, double Min, double Max, DialType Type, double Step, int NbDigit)
{
	m_enabled = true;
	m_type = Type;
	m_adj = new Gtk::Adjustment(Value, Min, Max, Step, Step);
	this->m_mouseDelta = 0;
	this->m_mouseDown = false;

	add_events(Gdk::EXPOSURE_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK| Gdk::POINTER_MOTION_MASK);
	signal_button_press_event().connect(sigc::mem_fun(*this, &Dial::on_button_press_event) );
	signal_button_release_event().connect(sigc::mem_fun(*this, &Dial::on_button_release_event) );
	signal_motion_notify_event().connect(sigc::mem_fun( *this, &Dial::onMouseMove) );
	signal_scroll_event().connect(sigc::mem_fun( *this, &Dial::onMouseScroll) );

	set_size_request(48, 48);

	m_adj->signal_value_changed().connect(mem_fun(*this, &Dial::value_changed));
	m_adj->signal_value_changed().connect(toggle_slot);

	m_rounder = 1;
	for(int i = 0 ; i<NbDigit ; i++)
	{
		m_rounder = m_rounder*10;
	}
}

Dial::~Dial()
{
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

		int xc = event->area.width/2;
		int yc = event->area.height/2;

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
		float angle= 2.46 + (4.54 * ((m_adj->get_value()-m_adj->get_lower()) / (m_adj->get_upper()-m_adj->get_lower())));

		if(m_enabled)
			cr->set_source_rgba( 255 / 255.f, 104 / 255.f , 0 / 255.f , 1.f );
		else
			cr->set_source_rgba( 66 / 255.f, 66 / 255.f , 66 / 255.f , 1.f );

		cr->set_line_width(1.7);
		cr->arc(xc,yc, 13, 2.46, angle );
		cr->line_to(xc,yc);
		cr->stroke();
		cr->arc(xc,yc, 17, 2.46, angle );
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

	// std::cout << "Perc " << p_perc << "\t Step " << m_adj->get_step_increment() + (m_adj->get_step_increment() * p_perc) <<  std::endl;

	return m_adj->get_step_increment() + (m_adj->get_step_increment() * p_perc);
}

double Dial::RoundValue(double Value)
{
	return floorf(Value * m_rounder + 0.5) / m_rounder;
}

bool Dial::onMouseScroll(GdkEventScroll * e)
{
	if(m_enabled)
	{
		if (e->direction == GDK_SCROLL_UP)
		{
			ChangeValueUp();
			if(m_type != DIVIDER)
			{
				for(int i = 0 ; i<4 ; i++)
					ChangeValueUp();
			}
		}
		else if (e->direction == GDK_SCROLL_DOWN)
		{
			ChangeValueDown();
			if(m_type != DIVIDER)
			{
				for(int i = 0 ; i<4 ; i++)
					ChangeValueDown();
			}
		}

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
		case DIVIDER:
			set_value(RoundValue(m_adj->get_value()*2));
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
		case DIVIDER:
			set_value(RoundValue(m_adj->get_value()/2));
			break;
	}
}

bool Dial::on_button_press_event(GdkEventButton* event)
{
	if( event->type == GDK_BUTTON_PRESS  ) // && event->button == 3
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
