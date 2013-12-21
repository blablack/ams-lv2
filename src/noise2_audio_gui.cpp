#include <gtkmm-2.4/gtkmm.h>


#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "noise2_audio_gui.hpp"
#include "noise2_audio.hpp"
#include "dial.hpp"

Noise2AudioGUI::Noise2AudioGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	VBox *p_mainWidget = manage (new VBox(false, 5));

	Label *p_labelWaveForm = manage (new Label("Noise Type"));
	p_mainWidget->pack_start(*p_labelWaveForm);

	m_comboNoiseForm = manage (new ComboBoxText());
	m_comboNoiseForm->append_text("White");
	m_comboNoiseForm->append_text("Random");
	m_comboNoiseForm->append_text("Pink");

	slot<void> p_slotNoiseForm = compose(bind<0> (mem_fun(*this, &Noise2AudioGUI::write_control), p_noiseType), mem_fun(*m_comboNoiseForm, &ComboBoxText::get_active_row_number));
	m_comboNoiseForm->signal_changed().connect(p_slotNoiseForm);

	p_mainWidget->pack_start(*m_comboNoiseForm);

	slot<void> p_slotRandomRate = compose(bind<0>(mem_fun(*this, &Noise2AudioGUI::write_control), p_rate), mem_fun(*this,  &Noise2AudioGUI::get_randomRate));
	m_dialRandomRate = new LabeledDial("Random Rate", p_slotRandomRate, p_rate, 0, 10, NORMAL, 0.01, 2);
	p_mainWidget->pack_start(*m_dialRandomRate);

	slot<void> p_slotRandomLevel = compose(bind<0>(mem_fun(*this, &Noise2AudioGUI::write_control), p_level), mem_fun(*this, &Noise2AudioGUI::get_randomLevel));
	m_dialRandomLevel = new LabeledDial("Random Level", p_slotRandomLevel, p_level, 0, 1, LOG, 0.0001, 4);
	p_mainWidget->pack_start(*m_dialRandomLevel);

	p_mainWidget->set_size_request(150, 200);

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

float Noise2AudioGUI::get_randomRate() { return m_dialRandomRate->get_value(); }
float Noise2AudioGUI::get_randomLevel() { return m_dialRandomLevel->get_value(); }

void Noise2AudioGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_noiseType)
	{
		int p_noiseFormValue = (int) (*static_cast<const float*> (buffer));
		if (p_noiseFormValue >= 0 && p_noiseFormValue <= 2)
		{
			m_comboNoiseForm->set_active((int) p_noiseFormValue);
		}
	}
	else if (port == p_rate)
	{
		m_dialRandomRate->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_level)
	{
		m_dialRandomLevel->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = Noise2AudioGUI::register_class("http://github.com/blablack/ams-lv2/noise2_audio/gui");
