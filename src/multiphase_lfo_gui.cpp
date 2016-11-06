#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "multiphase_lfo.hpp"
#include "multiphase_lfo_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "multiphase_lfo_gui.hpp"

MultiphaseLfoGUI::MultiphaseLfoGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	VBox *p_mainWidget = manage (new VBox(false));

	p_mainWidget->pack_start(*(m_dialFreq = CreateDial("Frequency (Hz)", p_freq, NORMAL, 0.01)));
	p_mainWidget->pack_start(*(m_dialGainSaw = CreateDial("Gain Saw", p_gainSaw, NORMAL, 0.01)));
	p_mainWidget->pack_start(*(m_dialGainTri = CreateDial("Gain Triangle", p_gainTriangle, NORMAL, 0.01)));

	MyBox *p_sawModeBox = manage (new MyBox("Saw Mode", Gtk::Orientation::ORIENTATION_HORIZONTAL));
	m_comboSawMode = manage (new ComboBoxText());
	m_comboSawMode->append_text("Saw Up");
	m_comboSawMode->append_text("Saw Down");
	m_comboSawMode->append_text("Saw Up (0..135) / Saw Down (180..315)");
	m_comboSawMode->signal_changed().connect(compose(bind<0> (mem_fun(*this, &MultiphaseLfoGUI::write_control), p_sawMode), mem_fun(*m_comboSawMode, &ComboBoxText::get_active_row_number)));
	p_sawModeBox->pack_start(*m_comboSawMode);
	p_mainWidget->pack_end(*p_sawModeBox);

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

LabeledDial* MultiphaseLfoGUI::CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step)
{
	peg_data_t p_portData = p_ports[PortIndex];
	LabeledDial* p_tempDial = new LabeledDial(TextLabel, p_portData.min, p_portData.max, Type, Step);
	p_tempDial->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &MultiphaseLfoGUI::write_control), PortIndex), mem_fun(*p_tempDial, &LabeledDial::get_value)));

	return p_tempDial;
}

void MultiphaseLfoGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	int p_sawModeValue;

	switch(port)
	{
		case p_sawMode:
			p_sawModeValue = (int) (*static_cast<const float*> (buffer));
			if (p_sawModeValue >= 0 && p_sawModeValue <= 2)
				m_comboSawMode->set_active((int) p_sawModeValue);
			break;
		case p_gainSaw:
			m_dialGainSaw->set_value(*static_cast<const float*> (buffer));
			break;
		case p_gainTriangle:
			m_dialGainTri->set_value(*static_cast<const float*> (buffer));
			break;
		case p_freq:
			m_dialFreq->set_value(*static_cast<const float*> (buffer));
			break;
	}
}

static int _ = MultiphaseLfoGUI::register_class("http://github.com/blablack/ams-lv2/multiphase_lfo/gui");
