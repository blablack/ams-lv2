#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "fftvocoder.hpp"
#include "fftvocoder_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "fftvocoder_gui.hpp"

FFTVocoderGUI::FFTVocoderGUI(const std::string& URI)
{
	EventBox *p_background = manage(new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);


	VBox *p_mainWidget = manage(new VBox(false));


	MyBox *p_channels_box = manage (new MyBox("Channels", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	p_channels_box->pack_start(*(m_scaleBinsChannel = CreateDial("Bins/Channel", p_bins_channel, NORMAL, 1)));
	p_channels_box->pack_start(*(m_scaleVCBinsChannels = CreateDial("VC Bins/Channels", p_vcbins_channels, NORMAL, 1)));

	p_mainWidget->pack_start(*p_channels_box);


	MyBox *p_envelope_box = manage (new MyBox("Envelope", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	p_envelope_box->pack_start(*(m_scaleAttackTime = CreateDial("Attack Time", p_attacktime, NORMAL, 0.001)));
	p_envelope_box->pack_start(*(m_scaleReleaseTime = CreateDial("Release Time", p_releasetime, NORMAL, 0.001)));

	p_mainWidget->pack_start(*p_envelope_box);


	MyBox *p_frequency_box = manage (new MyBox("Frequency", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	p_frequency_box->pack_start(*(m_scalePitchShiftOctave = CreateDial("Pitch Shift (Octaves)", p_pitchshift_octaves, NORMAL, 0.01)));
	p_frequency_box->pack_start(*(m_scaleVCPitchShift = CreateDial("VC Pitch Shift", p_vcpitchshift, NORMAL, 0.01)));
	p_frequency_box->pack_start(*(m_scaleFrequencyBodeShift = CreateDial("Frequency (Bode) Shift", p_freq_bode_shift, NORMAL, 1)));
	p_frequency_box->pack_start(*(m_scaleVCFreqShift = CreateDial("VC Freq Shift", p_vcfreqshift, NORMAL, 0.1)));
	p_frequency_box->pack_start(*(m_scalePhaseShift = CreateDial("Phase Shift", p_phaseshift, NORMAL, 0.01)));

	p_mainWidget->pack_start(*p_frequency_box);


	MyBox *p_fft_window_function_box = manage (new MyBox("FFT Window Function", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_comboFFTWindowFunction = manage (new ComboBoxText());
	m_comboFFTWindowFunction->append_text("Rectangular");
	m_comboFFTWindowFunction->append_text("Trapezoidal");
	m_comboFFTWindowFunction->append_text("Hann (Cosine)");
	m_comboFFTWindowFunction->append_text("Hamming (Cosine)");
	m_comboFFTWindowFunction->append_text("Tukey (Flattop Cosine)");
	m_comboFFTWindowFunction->append_text("Blackman-Nutall (Minimum Spill)");
	m_comboFFTWindowFunction->signal_changed().connect(compose(bind<0> (mem_fun(*this, &FFTVocoderGUI::write_control), p_fftwindowfunction), mem_fun(*m_comboFFTWindowFunction, &ComboBoxText::get_active_row_number)));

	p_fft_window_function_box->pack_start(*m_comboFFTWindowFunction);

	p_mainWidget->pack_start(*p_fft_window_function_box);


	p_mainWidget->pack_start(*(m_checkDynamicSlicing = CreateCheck("Dynamic Splicing", p_dynamicsplicing)));
	p_mainWidget->pack_start(*(m_RThetaModulaotr = CreateCheck("R-Theta Modulator", p_rthetamodulator)));


	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

void FFTVocoderGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	int p_value;

	switch(port)
	{
		case p_fftwindowfunction:
			p_value = (int) (*static_cast<const float*> (buffer));
			if (p_value >= 0 && p_value <= 5)
				m_comboFFTWindowFunction->set_active(p_value);
			break;
		case p_dynamicsplicing:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkDynamicSlicing->set_active(p_value == 1);
			break;
		case p_rthetamodulator:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_RThetaModulaotr->set_active(p_value == 1);
			break;
		case p_bins_channel:
			m_scaleBinsChannel->set_value(*static_cast<const float*> (buffer));
			break;
		case p_vcbins_channels:
			m_scaleVCBinsChannels->set_value(*static_cast<const float*> (buffer));
			break;
		case p_attacktime:
			m_scaleAttackTime->set_value(*static_cast<const float*> (buffer));
			break;
		case p_releasetime:
			m_scaleReleaseTime->set_value(*static_cast<const float*> (buffer));
			break;
		case p_pitchshift_octaves:
			m_scalePitchShiftOctave->set_value(*static_cast<const float*> (buffer));
			break;
		case p_vcpitchshift:
			m_scaleVCPitchShift->set_value(*static_cast<const float*> (buffer));
			break;
		case p_freq_bode_shift:
			m_scaleFrequencyBodeShift->set_value(*static_cast<const float*> (buffer));
			break;
		case p_vcfreqshift:
			m_scaleVCFreqShift->set_value(*static_cast<const float*> (buffer));
			break;
		case p_phaseshift:
			m_scalePhaseShift->set_value(*static_cast<const float*> (buffer));
			break;
	}
}

LabeledDial* FFTVocoderGUI::CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step)
{
	peg_data_t p_portData = p_ports[PortIndex];
	LabeledDial* p_tempDial = new LabeledDial(TextLabel, p_portData.min, p_portData.max, Type, Step);
	p_tempDial->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &FFTVocoderGUI::write_control), PortIndex), mem_fun(*p_tempDial, &LabeledDial::get_value)));

	return p_tempDial;
}

CheckButton* FFTVocoderGUI::CreateCheck(const std::string TextLabel, int PortNum)
{
	CheckButton* m_tempCheck = manage (new CheckButton(TextLabel, PortNum));
	m_tempCheck->signal_toggled().connect(compose(bind<0>(mem_fun(*this, &FFTVocoderGUI::write_control), PortNum), mem_fun(*m_tempCheck, &CheckButton::get_active)));

	return m_tempCheck;
}

static int _ = FFTVocoderGUI::register_class("http://github.com/blablack/ams-lv2/fftvocoder/gui");
