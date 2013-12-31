#include <cairomm/context.h>
#include <cmath>

#include "labeleddial.hpp"

using namespace std;

LabeledDial::LabeledDial(const std::string TextLabel, double Value, double Min, double Max, DialType Type, double Step, int NbDigit)
{
	m_type = Type;
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	this->modify_bg(Gtk::STATE_NORMAL, *color);

	VBox *p_mainWidget = manage (new VBox(false));

	Label *p_label = manage (new Label(TextLabel));
	p_mainWidget->pack_start(*p_label);

	m_dial = new Dial(Value, Min, Max, Type, Step, NbDigit);

	m_dial->signal_value_changed().connect(mem_fun(*this, &LabeledDial::value_changed));

	p_mainWidget->pack_start(*m_dial);

	std::stringstream out;
	out << Value;

	m_label = new Gtk::Label();
	m_label->set_text(out.str());

	p_mainWidget->pack_start(*m_label);

	this->add(*p_mainWidget);

	set_size_request(60, 64);
}

LabeledDial::~LabeledDial()
{
}

Glib::SignalProxy0<void> LabeledDial::signal_value_changed()
{
    return m_dial->signal_value_changed();
}

bool LabeledDial::Redraw()
{
	return m_dial->Redraw();
}

void LabeledDial::enable()
{
	m_dial->enable();
}

void LabeledDial::disable()
{
	m_dial->disable();
}

void LabeledDial::value_changed()
{
	m_dial->Redraw();
	m_label->set_text(float_to_fraction(m_dial->get_value()));
}

float LabeledDial::get_value()
{
	return m_dial->get_value();
}

void LabeledDial::set_value(float Value)
{
	m_dial->set_value(Value);
	m_label->set_text(float_to_fraction(Value));
	m_dial->Redraw();
}

Glib::ustring LabeledDial::float_to_fraction(float value)
{
	if(m_type != DIVIDER)
	{
		std::stringstream out;
		out << value;
		return out.str();
	}
	else
	{
		if(value == 0.0078125)
			return "1/128";
		else if(value == 0.015625)
			return "1/64";
		else if(value == 0.03125)
			return "1/32";
		else if(value == 0.0625)
			return "1/16";
		else if(value == 0.125)
			return "1/8";
		else if(value == 0.25)
			return "1/4";
		else if(value == 0.5)
			return "1/2";
		else
		{
			std::stringstream out;
			out << value;
			return out.str();
		}
	}
}



