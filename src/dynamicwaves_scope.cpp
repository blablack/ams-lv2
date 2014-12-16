#include <gtkmm/drawingarea.h>

#include "dynamicwaves_scope.hpp"

#define SUSTAIN_LEN 0.5

DynamicWavesScope::DynamicWavesScope(int ScopeCount)
{
	set_size_request(80, 80);
}

bool DynamicWavesScope::on_expose_event(GdkEventExpose* event)
{
	Glib::RefPtr<Gdk::Window> window = get_window();
	if (window)
	{
		float len, x, y, xscale, yscale;

		Gtk::Allocation allocation = get_allocation();
		const int width = allocation.get_width();
		const int height = allocation.get_height();

		Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
		cr->set_line_width(2.0);
		cr->set_source_rgb(0.0, 0.0, 0.0);
		cr->paint();

		for( int i = 0 ; i < 8 ; i++ )
		{
			switch(i)
			{
				case 0:
					//colorTable[0].setRgb(255, 255, 255);
					cr->set_source_rgb(1.0, 1.0, 1.0);
					break;
				case 1:
					//colorTable[1].setRgb(255, 0, 0);
					cr->set_source_rgb(1.0, 0.0, 0.0);
					break;
				case 2:
					//colorTable[2].setRgb(0, 255, 0);
					cr->set_source_rgb(0.0, 1.0, 0.0);
					break;
				case 3:
					//colorTable[3].setRgb(50, 150, 255);
					cr->set_source_rgb(0.2, 0.6, 1.0);
					break;
				case 4:
					//colorTable[4].setRgb(255, 255, 0);
					cr->set_source_rgb(1.0, 1.0, 0.0);
					break;
				case 5:
					//colorTable[5].setRgb(0, 255, 255);
					cr->set_source_rgb(0.0, 1.0, 1.0);
					break;
				case 6:
					//colorTable[6].setRgb(255, 100, 255);
					cr->set_source_rgb(1.0, 0.4, 1.0);
					break;
				case 7:
					//colorTable[7].setRgb(255, 200, 50);
					cr->set_source_rgb(1.0, 0.8, 0.2);
					break;
			}

			cr->rectangle(event->area.x, event->area.y, event->area.width, event->area.height);
			cr->clip();

			cr->move_to(width, height);

			len = m_valueDelay[i] + m_valueAttackTime1[i] + m_valueAttackTime2[i] + m_valueAttackTime3[i] + m_valueAttackTime4[i] + m_valueReleaseTime1[i] + m_valueReleaseTime2[i] + m_valueReleaseTime3[i] + SUSTAIN_LEN;
			xscale = (float) width / len;
			yscale = (float) (height - 6);

			x = m_valueDelay[i] * xscale;
			cr->line_to((int) x, height);
			x += m_valueAttackTime1[i] * xscale;
			y = m_valueAttackLevel1[i] * yscale;
			cr->line_to((int) x, height - (int) y);
			x += m_valueAttackTime2[i] * xscale;
			y = m_valueAttackLevel2[i] * yscale;
			cr->line_to((int) x, height - (int) y);
			x += m_valueAttackTime3[i] * xscale;
			y = m_valueAttackLevel3[i] * yscale;
			cr->line_to((int) x, height - (int) y);
			x += m_valueAttackTime4[i] * xscale;
			y = m_valueSustain[i] * yscale;
			cr->line_to((int) x, height - (int) y);
			x += SUSTAIN_LEN * xscale;
			cr->line_to((int) x, height - (int) y);
			x += m_valueReleaseTime1[i] * xscale;
			y = m_valueReleaseLevel1[i] * yscale;
			cr->line_to((int) x, height - (int) y);
			x += m_valueReleaseTime2[i] * xscale;
			y = m_valueReleaseLevel2[i] * yscale;
			cr->line_to((int) x, height - (int) y);
			x += m_valueReleaseTime3[i] * xscale;
			cr->line_to((int) x, height);
			x = m_valueDelay[i] * xscale;
			cr->line_to((int) x, height);
			cr->stroke();
		}
	}

	return true;
}

bool DynamicWavesScope::Redraw()
{
	Glib::RefPtr<Gdk::Window> win = get_window();
	if (win)
	{
		Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
		win->invalidate_rect(r, false);
	}

	return true;
}
