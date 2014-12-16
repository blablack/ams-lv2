#include <gtkmm-2.4/gtkmm.h>
#include <iomanip>

#include "labeleddial.hpp"

using namespace Gtk;

LabeledDial::LabeledDial(const std::string TextLabel, double Min, double Max, DialType Type, double Step)
{
    m_type = Type;
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    this->modify_bg(Gtk::STATE_NORMAL, *color);

    VBox *p_mainWidget = manage (new VBox(false));

    Label *p_label = manage (new Label(" " + TextLabel + " "));
    p_mainWidget->pack_start(*p_label, Gtk::PACK_SHRINK, 0, 0);

	m_dial = new Dial(Min, Max, Type, Step);
    m_dial->signal_value_changed().connect(mem_fun(*this, &LabeledDial::value_changed));

    p_mainWidget->pack_start(*m_dial, Gtk::PACK_SHRINK, 0, 0);

    m_label = new Gtk::Label();
	std::stringstream out;
	out << std::fixed << std::setprecision(m_dial->getNbDigit()) << m_dial->get_value();
	m_label->set_text(out.str());
    p_mainWidget->pack_start(*m_label, Gtk::PACK_SHRINK, 0, 0);

    this->set_border_width(1);
    this->add(*p_mainWidget);
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

    if(m_type != MULTIPLIER)
    {
		std::stringstream out;
		out << std::fixed << std::setprecision(m_dial->getNbDigit()) << m_dial->get_value();
        m_label->set_text(out.str());
    }
    else
    {
        if(m_dial->get_value() <= 0.0078125)
            m_label->set_text("1/128");
        else if(m_dial->get_value() <= 0.015625)
            m_label->set_text("1/64");
        else if(m_dial->get_value() <= 0.03125)
            m_label->set_text("1/32");
        else if(m_dial->get_value() <= 0.0625)
            m_label->set_text("1/16");
        else if(m_dial->get_value() <= 0.125)
            m_label->set_text("1/8");
		else if(m_dial->get_value() <= 0.25)
            m_label->set_text("1/4");
        else if(m_dial->get_value() <= 0.5)
            m_label->set_text("1/2");
        else if(m_dial->get_value() <= 1)
            m_label->set_text("1");
        else if(m_dial->get_value() <= 2)
            m_label->set_text("2");
        else if(m_dial->get_value() <= 4)
            m_label->set_text("4");
        else if(m_dial->get_value() <= 8)
            m_label->set_text("8");
        else if(m_dial->get_value() <= 16)
            m_label->set_text("16");
        else if(m_dial->get_value() <= 32)
            m_label->set_text("32");
        else if(m_dial->get_value() <= 64)
            m_label->set_text("64");
        else if(m_dial->get_value() > 64)
            m_label->set_text("128");
    }
}

float LabeledDial::get_value()
{
    return m_dial->get_value();
}

void LabeledDial::set_value(float Value)
{
    m_dial->set_value(Value);
}





