#ifndef DIAL_H
#define DIAL_H

enum DialType
{
	NORMAL,
	LOG,
	MULTIPLIER
};

class Dial: public Gtk::DrawingArea
{
	public:
		Dial(double Min, double Max, DialType Type, double Step);
		bool Redraw();

		void value_changed();
		float get_value();
		void set_value(float value);
		int getNbDigit();
		void disable();
		void enable();
		Glib::SignalProxy0<void> signal_value_changed();

	protected:
		virtual bool on_expose_event(GdkEventExpose* event);
		virtual bool onMouseMove(GdkEventMotion* event);
		virtual bool on_button_press_event(GdkEventButton* event);
		virtual bool on_button_release_event(GdkEventButton* event);
		virtual bool onMouseScroll(GdkEventScroll * e);

	private:
		Gtk::Adjustment *m_adj;

		float m_mouseDelta;
		bool m_mouseDown;

		bool m_enabled;

		DialType m_type;
		int m_rounder;
		int m_nbDigit;
		int m_scrollStep;

		double CalculateLogStep();
		double RoundValue(double Value);
		double MultValue(double Value);
		void ChangeValueUp();
		void ChangeValueDown();
};

#endif
