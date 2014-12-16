#include <gtkmm/drawingarea.h>

#include "env_gui_scope.hpp"

#define SUSTAIN_LEN 0.5

EnvGUIScope::EnvGUIScope()
{
	set_size_request(80, 80);
}

bool EnvGUIScope::on_expose_event(GdkEventExpose* event)
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

		len = m_delayValue + m_attackValue + m_holdValue + m_decayValue + SUSTAIN_LEN + m_releaseValue;
		xscale = (float) width / len;
		yscale = (float) (height - 6);
		x = m_delayValue * xscale;
		cr->line_to((int) x, height);
		x += m_attackValue * xscale;
		cr->line_to((int) x, 6);
		x += m_holdValue * xscale;
		cr->line_to((int) x, 6);
		x += m_decayValue * xscale;
		y = m_sustainValue * yscale;
		cr->line_to((int) x, height - (int) y);
		x += SUSTAIN_LEN * xscale;
		cr->line_to((int) x, height - (int) y);
		x += m_releaseValue * xscale;
		cr->line_to((int) x, height - 1);
		x = m_delayValue * xscale;
		cr->line_to((int) x, height - 1);

		cr->stroke();
	}

	return true;
}

bool EnvGUIScope::Redraw()
{
	Glib::RefPtr<Gdk::Window> win = get_window();
	if (win)
	{
		Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
		win->invalidate_rect(r, false);
	}
	return true;
}
