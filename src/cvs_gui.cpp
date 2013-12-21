#include <gtkmm-2.4/gtkmm.h>

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "cvs_gui.hpp"
#include "cvs.hpp"
#include "dial.hpp"

CVSGUI::CVSGUI(const std::string& URI)
{
	EventBox *p_background = manage(new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);



	VBox *p_mainWidget = manage(new VBox(false, 5));



	Frame *p_cv1Frame = manage(new Frame("1"));
	p_cv1Frame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_cv1Box = manage(new HBox(false));

	slot<void> p_slotCV1 = compose(bind<0>(mem_fun(*this, &CVSGUI::write_control), p_cv1), mem_fun(*this,  &CVSGUI::get_cv1));
	m_dialCV1 = new LabeledDial("CV", p_slotCV1, p_cv1, 0, 5, NORMAL, 0.01, 2);
	p_cv1Box->pack_start(*m_dialCV1);

	slot<void> p_slotCVFine1 = compose(bind<0>(mem_fun(*this, &CVSGUI::write_control), p_cvFine1), mem_fun(*this,  &CVSGUI::get_cvFine1));
	m_dialCVFine1 = new LabeledDial("Fine", p_slotCVFine1, p_cvFine1, -0.5, 0.5, NORMAL, 0.001, 3);
	p_cv1Box->pack_start(*m_dialCVFine1);

	p_cv1Frame->add(*p_cv1Box);
	p_mainWidget->pack_start(*p_cv1Frame);



	p_mainWidget->pack_start(*(new HSeparator()));



	Frame *p_cv2Frame = manage(new Frame("2"));
	p_cv2Frame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_cv2Box = manage(new HBox(false));

	slot<void> p_slotCV2 = compose(bind<0>(mem_fun(*this, &CVSGUI::write_control), p_cv2), mem_fun(*this,  &CVSGUI::get_cv2));
	m_dialCV2 = new LabeledDial("CV", p_slotCV2, p_cv2, 0, 5, NORMAL, 0.01, 2);
	p_cv2Box->pack_start(*m_dialCV2);

	slot<void> p_slotCVFine2 = compose(bind<0>(mem_fun(*this, &CVSGUI::write_control), p_cvFine2), mem_fun(*this,  &CVSGUI::get_cvFine2));
	m_dialCVFine2 = new LabeledDial("Fine", p_slotCVFine2, p_cvFine2, -0.5, 0.5, NORMAL, 0.001, 3);
	p_cv2Box->pack_start(*m_dialCVFine2);

	p_cv2Frame->add(*p_cv2Box);
	p_mainWidget->pack_start(*p_cv2Frame);



	p_mainWidget->pack_start(*(new HSeparator()));



	Frame *p_cv3Frame = manage(new Frame("3"));
	p_cv3Frame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_cv3Box = manage(new HBox(false));

	slot<void> p_slotCV3 = compose(bind<0>(mem_fun(*this, &CVSGUI::write_control), p_cv3), mem_fun(*this,  &CVSGUI::get_cv3));
	m_dialCV3 = new LabeledDial("CV", p_slotCV3, p_cv3, 0, 5, NORMAL, 0.01, 2);
	p_cv3Box->pack_start(*m_dialCV3);

	slot<void> p_slotCVFine3 = compose(bind<0>(mem_fun(*this, &CVSGUI::write_control), p_cvFine3), mem_fun(*this,  &CVSGUI::get_cvFine3));
	m_dialCVFine3 = new LabeledDial("Fine", p_slotCVFine3, p_cvFine3, -0.5, 0.5, NORMAL, 0.001, 3);
	p_cv3Box->pack_start(*m_dialCVFine3);

	p_cv3Frame->add(*p_cv3Box);
	p_mainWidget->pack_start(*p_cv3Frame);



	p_mainWidget->pack_start(*(new HSeparator()));



	Frame *p_cv4Frame = manage(new Frame("4"));
	p_cv4Frame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_cv4Box = manage(new HBox(false));

	slot<void> p_slotCV4 = compose(bind<0>(mem_fun(*this, &CVSGUI::write_control), p_cv4), mem_fun(*this,  &CVSGUI::get_cv4));
	m_dialCV4 = new LabeledDial("CV", p_slotCV4, p_cv4, 0, 5, NORMAL, 0.01, 2);
	p_cv4Box->pack_start(*m_dialCV4);

	slot<void> p_slotCVFine4 = compose(bind<0>(mem_fun(*this, &CVSGUI::write_control), p_cvFine4), mem_fun(*this,  &CVSGUI::get_cvFine4));
	m_dialCVFine4 = new LabeledDial("Fine", p_slotCVFine4, p_cvFine4, -0.5, 0.5, NORMAL, 0.001, 3);
	p_cv4Box->pack_start(*m_dialCVFine4);

	p_cv4Frame->add(*p_cv4Box);
	p_mainWidget->pack_start(*p_cv4Frame);



	p_mainWidget->set_size_request(150, 360);

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

float CVSGUI::get_cv1(){ return m_dialCV1->get_value(); }
float CVSGUI::get_cvFine1(){ return m_dialCVFine1->get_value(); }
float CVSGUI::get_cv2(){ return m_dialCV2->get_value(); }
float CVSGUI::get_cvFine2(){ return m_dialCVFine2->get_value(); }
float CVSGUI::get_cv3(){ return m_dialCV3->get_value(); }
float CVSGUI::get_cvFine3(){ return m_dialCVFine3->get_value(); }
float CVSGUI::get_cv4(){ return m_dialCV4->get_value(); }
float CVSGUI::get_cvFine4(){ return m_dialCVFine4->get_value(); }

void CVSGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_cv1)
	{
		m_dialCV1->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_cvFine1)
	{
		m_dialCVFine1->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_cv2)
	{
		m_dialCV2->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_cvFine2)
	{
		m_dialCVFine2->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_cv3)
	{
		m_dialCV3->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_cvFine3)
	{
		m_dialCVFine3->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_cv4)
	{
		m_dialCV4->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_cvFine4)
	{
		m_dialCVFine4->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = CVSGUI::register_class("http://github.com/blablack/ams-lv2/cvs/gui");
