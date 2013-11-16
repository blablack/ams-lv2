#ifndef ADVENV_GUI_SCOPE_H
#define ADVENV_GUI_SCOPE_H

#include <gtkmm/drawingarea.h>

#define SUSTAIN_LEN                   0.5

class AdvEnvGUIScope: public Gtk::DrawingArea
{
	public:
		AdvEnvGUIScope();
		virtual ~AdvEnvGUIScope();
		bool Redraw();

		float m_valueSustain;
		float m_valueDelay;

		float m_valueAttackTime1;
		float m_valueAttackTime2;
		float m_valueAttackTime3;
		float m_valueAttackTime4;

		float m_valueAttackLevel1;
		float m_valueAttackLevel2;
		float m_valueAttackLevel3;

		float m_valueReleaseTime1;
		float m_valueReleaseTime2;
		float m_valueReleaseTime3;

		float m_valueReleaseLevel1;
		float m_valueReleaseLevel2;

	protected:
		virtual bool on_expose_event(GdkEventExpose* event);
};

#endif
