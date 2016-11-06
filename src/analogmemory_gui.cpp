#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "analogmemory.hpp"
#include "analogmemory_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "analogmemory_gui.hpp"

AnalogMemoryGUI::AnalogMemoryGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	VBox *p_mainWidget = manage(new VBox(false));

	MyBox *p_writeAddressingModeBox = manage (new MyBox("Write Addressing Mode", Gtk::Orientation::ORIENTATION_VERTICAL));

	m_comboWriteAddressForm = manage (new ComboBoxText());
	m_comboWriteAddressForm->append_text("Direct (no fill)");
	m_comboWriteAddressForm->append_text("Linear up only, no fill");
	m_comboWriteAddressForm->append_text("Linear up only, fill");
	m_comboWriteAddressForm->append_text("Linear down only, no fill");
	m_comboWriteAddressForm->append_text("Linear down only, fill");
	m_comboWriteAddressForm->append_text("Reflected");
	m_comboWriteAddressForm->signal_changed().connect(compose(bind<0> (mem_fun(*this, &AnalogMemoryGUI::write_control), p_write_addressing_mode), mem_fun(*m_comboWriteAddressForm, &ComboBoxText::get_active_row_number)));

	p_writeAddressingModeBox->pack_start(*m_comboWriteAddressForm);
	p_mainWidget->pack_start(*p_writeAddressingModeBox);

	p_mainWidget->pack_start(*(m_dialN				= CreateDial("N (for 2^N memory cells)",	p_n,			NORMAL, 1)));
	p_mainWidget->pack_start(*(m_dialWriteThresh	= CreateDial("Write Threshold",				p_write_tresh,	NORMAL, 0.01)));

	p_background->add(*p_mainWidget);

	add(*p_background);

	Gtk::manage(p_background);
}

void AnalogMemoryGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	int p_comboValue;
	switch(port)
	{
		case p_write_addressing_mode:
			p_comboValue = (int) (*static_cast<const float*> (buffer));
			if (p_comboValue >= 0 && p_comboValue <= 5)
				m_comboWriteAddressForm->set_active(p_comboValue);
			break;
		case p_n:
			m_dialN->set_value(*static_cast<const float*> (buffer));
			break;
		case p_write_tresh:
			m_dialWriteThresh->set_value(*static_cast<const float*> (buffer));
			break;
	}
}

LabeledDial* AnalogMemoryGUI::CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step)
{
	peg_data_t p_portData = p_ports[PortIndex];
	LabeledDial* p_tempDial = new LabeledDial(TextLabel, p_portData.min, p_portData.max, Type, Step);
	p_tempDial->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &AnalogMemoryGUI::write_control), PortIndex), mem_fun(*p_tempDial, &LabeledDial::get_value)));

	return p_tempDial;
}

static int _ = AnalogMemoryGUI::register_class("http://github.com/blablack/ams-lv2/analogmemory/gui");
