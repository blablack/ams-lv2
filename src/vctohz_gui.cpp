#include <gtkmm-2.4/gtkmm.h>


#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "vctohz_gui.hpp"
#include "vctohz.hpp"
#include "dial.hpp"

VCToHZGUI::VCToHZGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	VBox *p_mainWidget = manage (new VBox(false, 5));

	Label *p_labelWaveForm = manage (new Label("Conversion Mode"));
	p_mainWidget->pack_start(*p_labelWaveForm);

	m_comboConversionMode = manage (new ComboBoxText());
	m_comboConversionMode->append_text("V/Octave --> Hz");
	m_comboConversionMode->append_text("V/Octave --> 0..1, 1=rate/2");
	m_comboConversionMode->append_text("V/Octave --> 0..1, 1=20000 Hz");

	slot<void> p_slotConversionMode = compose(bind<0> (mem_fun(*this, &VCToHZGUI::write_control), p_conversionMode), mem_fun(*m_comboConversionMode, &ComboBoxText::get_active_row_number));
	m_comboConversionMode->signal_changed().connect(p_slotConversionMode);

	p_mainWidget->pack_start(*m_comboConversionMode);

	slot<void> p_slotOctOffset = compose(bind<0>(mem_fun(*this, &VCToHZGUI::write_control), p_octaveOffset), mem_fun(*this, &VCToHZGUI::get_octaveOffset));
	m_dialOctaveOffset = new LabeledDial("Octave Offset", p_slotOctOffset, p_octaveOffset, -3, 3, NORMAL, 0.01, 2);
	p_mainWidget->pack_start(*m_dialOctaveOffset);

	p_mainWidget->set_size_request(180, 130);

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

float VCToHZGUI::get_octaveOffset() { return m_dialOctaveOffset->get_value(); }

void VCToHZGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_conversionMode)
	{
		int p_conversionValue = (int) (*static_cast<const float*> (buffer));
		if (p_conversionValue >= 0 && p_conversionValue <= 2)
		{
			m_comboConversionMode->set_active((int) p_conversionValue);
		}
	}
	else if (port == p_octaveOffset)
	{
		m_dialOctaveOffset->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = VCToHZGUI::register_class("http://github.com/blablack/ams.lv2/vctohz/gui");
