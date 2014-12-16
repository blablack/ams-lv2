#include <gtkmm/drawingarea.h>

#include "advenv_gui_scope.hpp"

#define SUSTAIN_LEN 0.5

AdvEnvGUIScope::AdvEnvGUIScope()
{
	set_size_request(80, 80);
}

bool AdvEnvGUIScope::on_expose_event(GdkEventExpose* event)
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

		cr->set_source_rgb(0.0, 0.8, 0.0);

		cr->rectangle(event->area.x, event->area.y, event->area.width, event->area.height);
		cr->clip();

		cr->move_to(width, height);

		len = m_valueDelay + m_valueAttackTime1 + m_valueAttackTime2 + m_valueAttackTime3 + m_valueAttackTime4 + m_valueReleaseTime1 + m_valueReleaseTime2 + m_valueReleaseTime3 + SUSTAIN_LEN;
		xscale = (float) width / len;
		yscale = (float) (height - 6);

		x = m_valueDelay * xscale;
		cr->line_to((int) x, height);
		x += m_valueAttackTime1 * xscale;
		y = m_valueAttackLevel1 * yscale;
		cr->line_to((int) x, height - (int) y);
		x += m_valueAttackTime2 * xscale;
		y = m_valueAttackLevel2 * yscale;
		cr->line_to((int) x, height - (int) y);
		x += m_valueAttackTime3 * xscale;
		y = m_valueAttackLevel3 * yscale;
		cr->line_to((int) x, height - (int) y);
		x += m_valueAttackTime4 * xscale;
		y = m_valueSustain * yscale;
		cr->line_to((int) x, height - (int) y);
		x += SUSTAIN_LEN * xscale;
		cr->line_to((int) x, height - (int) y);
		x += m_valueReleaseTime1 * xscale;
		y = m_valueReleaseLevel1 * yscale;
		cr->line_to((int) x, height - (int) y);
		x += m_valueReleaseTime2 * xscale;
		y = m_valueReleaseLevel2 * yscale;
		cr->line_to((int) x, height - (int) y);
		x += m_valueReleaseTime3 * xscale;
		cr->line_to((int) x, height);
		x = m_valueDelay * xscale;
		cr->line_to((int) x, height);
		cr->stroke();
	}

	return true;
}

bool AdvEnvGUIScope::Redraw()
{
	Glib::RefPtr<Gdk::Window> win = get_window();
	if (win)
	{
		Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
		win->invalidate_rect(r, false);
	}
	return true;
}
