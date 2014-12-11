#ifndef DYNAMICWAVES_SCOPE_H
#define DYNAMICWAVES_SCOPE_H

#include <gtkmm/drawingarea.h>

#define SUSTAIN_LEN                   0.5

class DynamicWavesScope: public Gtk::DrawingArea
{
	public:
		DynamicWavesScope(int ScopeCount);
		virtual ~DynamicWavesScope();
		bool Redraw();

		float m_valueSustain[8];
		float m_valueDelay[8];

		float m_valueAttackTime1[8];
		float m_valueAttackTime2[8];
		float m_valueAttackTime3[8];
		float m_valueAttackTime4[8];

		float m_valueAttackLevel1[8];
		float m_valueAttackLevel2[8];
		float m_valueAttackLevel3[8];

		float m_valueReleaseTime1[8];
		float m_valueReleaseTime2[8];
		float m_valueReleaseTime3[8];

		float m_valueReleaseLevel1[8];
		float m_valueReleaseLevel2[8];

	protected:
		virtual bool on_expose_event(GdkEventExpose* event);
};

#endif
