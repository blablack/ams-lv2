#ifndef ENV_GUI_SCOPE_H
#define ENV_GUI_SCOPE_H

#include <gtkmm/drawingarea.h>

class PercussiveEnvGUIScope: public Gtk::DrawingArea
{
	public:
		PercussiveEnvGUIScope();
		virtual ~PercussiveEnvGUIScope();
		bool Redraw();


		float m_attackValue, m_decayValue, m_delayValue, m_holdValue;

	protected:
		virtual bool on_expose_event(GdkEventExpose* event);
};

#endif
