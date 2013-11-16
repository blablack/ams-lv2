#ifndef ENV_GUI_SCOPE_H
#define ENV_GUI_SCOPE_H

#include <gtkmm/drawingarea.h>

#define SUSTAIN_LEN                   0.5

class EnvGUIScope: public Gtk::DrawingArea
{
	public:
		EnvGUIScope();
		virtual ~EnvGUIScope();
		bool Redraw();


		float m_attackValue, m_decayValue, m_sustainValue, m_releaseValue, m_delayValue, m_holdValue;

	protected:
		virtual bool on_expose_event(GdkEventExpose* event);
};

#endif
