#include <gtkmm-2.4/gtkmm.h>


#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "lfo_tempo_gui.hpp"
#include "lfo_tempo.hpp"
#include "dial.hpp"

LfoTempoGUI::LfoTempoGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	VBox *p_mainWidget = manage (new VBox(false, 5));

	Label *p_labelWaveForm = manage (new Label("Wave Form"));
	p_mainWidget->pack_start(*p_labelWaveForm);

	m_comboWaveForm = manage (new ComboBoxText());
	m_comboWaveForm->append_text("Sine");
	m_comboWaveForm->append_text("Triangle");
	m_comboWaveForm->append_text("Sawtooth Up");
	m_comboWaveForm->append_text("Sawtooth Down");
	m_comboWaveForm->append_text("Rectangle");
	m_comboWaveForm->append_text("S & H");

	slot<void> p_slotWaveForm = compose(bind<0> (mem_fun(*this, &LfoTempoGUI::write_control), p_waveForm), mem_fun(*m_comboWaveForm, &ComboBoxText::get_active_row_number));
	m_comboWaveForm->signal_changed().connect(p_slotWaveForm);

	p_mainWidget->pack_start(*m_comboWaveForm);

	Frame *p_freqFrame = manage(new Frame("Tempo"));

	HBox *p_freqBox = manage(new HBox(true));

	slot<void> p_slotTempo = compose(bind<0>(mem_fun(*this, &LfoTempoGUI::write_control), p_tempo), mem_fun(*this, &LfoTempoGUI::get_tempo));
	m_dialTempo = new LabeledDial("Tempo", p_tempo, 1, 320, NORMAL, 1, 0);
	m_dialTempo->signal_value_changed().connect(p_slotTempo);
	p_freqBox->pack_start(*m_dialTempo);

	slot<void> p_slotTempoMultiplier = compose(bind<0>(mem_fun(*this, &LfoTempoGUI::write_control), p_tempoMultiplier), mem_fun(*this, &LfoTempoGUI::get_tempoMultiplier));
	m_dialTempoMultiplier = new LabeledDial("Tempo Multiplier", p_tempoMultiplier, 0.0078125, 32, DIVIDER, 1, 7);
	m_dialTempoMultiplier->signal_value_changed().connect(p_slotTempoMultiplier);
	p_freqBox->pack_start(*m_dialTempoMultiplier);

	p_freqFrame->add(*p_freqBox);
	p_mainWidget->pack_start(*p_freqFrame);

	slot<void> p_slotPhi0 = compose(bind<0> (mem_fun(*this, &LfoTempoGUI::write_control), p_phi0), mem_fun(*this, &LfoTempoGUI::get_phi0));
	m_dialPhi0 = new LabeledDial("Phi0", p_phi0, 0, 6.28, NORMAL, 0.01, 2);
	m_dialPhi0->signal_value_changed().connect(p_slotPhi0);
	p_mainWidget->pack_start(*m_dialPhi0);

	p_mainWidget->set_size_request(160, 260);

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

float LfoTempoGUI::get_tempo() 				{ return m_dialTempo->get_value(); }
float LfoTempoGUI::get_tempoMultiplier()	{ return m_dialTempoMultiplier->get_value(); }
float LfoTempoGUI::get_phi0() 				{ return m_dialPhi0->get_value(); }

void LfoTempoGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_waveForm)
	{
		int p_waveFormValue = (int) (*static_cast<const float*> (buffer));
		if (p_waveFormValue >= 0 && p_waveFormValue <= 5)
		{
			m_comboWaveForm->set_active((int) p_waveFormValue);
		}
	}
	else if (port == p_tempo)
	{
		m_dialTempo->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_tempoMultiplier)
	{
		m_dialTempoMultiplier->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_phi0)
	{
		m_dialPhi0->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = LfoTempoGUI::register_class("http://github.com/blablack/ams-lv2/lfo_tempo/gui");
