#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "cvs.hpp"
#include "cvs_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "cvs_gui.hpp"

CVSGUI::CVSGUI(const std::string& URI)
{
    EventBox *p_background = manage(new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);



    VBox *p_mainWidget = manage(new VBox(true));



    MyBox *p_cv1Frame = manage(new MyBox("CV Source 1", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_dialCV1 = new LabeledDial("CV", 0, 5, NORMAL, 0.01);
    m_dialCV1->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &CVSGUI::write_control), p_cv1), mem_fun(*m_dialCV1,  &LabeledDial::get_value)));
    p_cv1Frame->pack_start(*m_dialCV1);

	m_dialCVFine1 = new LabeledDial("Fine", -0.5, 0.5, NORMAL, 0.001);
    m_dialCVFine1->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &CVSGUI::write_control), p_cvFine1), mem_fun(*m_dialCVFine1,  &LabeledDial::get_value)));
    p_cv1Frame->pack_start(*m_dialCVFine1);

    p_mainWidget->pack_start(*p_cv1Frame);


    MyBox *p_cv2Frame = manage(new MyBox("CV Source 2", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_dialCV2 = new LabeledDial("CV", 0, 5, NORMAL, 0.01);
    m_dialCV2->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &CVSGUI::write_control), p_cv2), mem_fun(*m_dialCV2,  &LabeledDial::get_value)));
    p_cv2Frame->pack_start(*m_dialCV2);

	m_dialCVFine2 = new LabeledDial("Fine", -0.5, 0.5, NORMAL, 0.001);
    m_dialCVFine2->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &CVSGUI::write_control), p_cvFine2), mem_fun(*m_dialCVFine2,  &LabeledDial::get_value)));
    p_cv2Frame->pack_start(*m_dialCVFine2);

    p_mainWidget->pack_start(*p_cv2Frame);


    MyBox *p_cv3Frame = manage(new MyBox("CV Source 3", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_dialCV3 = new LabeledDial("CV", 0, 5, NORMAL, 0.01);
    m_dialCV3->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &CVSGUI::write_control), p_cv3), mem_fun(*m_dialCV3,  &LabeledDial::get_value)));
    p_cv3Frame->pack_start(*m_dialCV3);

	m_dialCVFine3 = new LabeledDial("Fine", -0.5, 0.5, NORMAL, 0.001);
    m_dialCVFine3->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &CVSGUI::write_control), p_cvFine3), mem_fun(*m_dialCVFine3,  &LabeledDial::get_value)));
    p_cv3Frame->pack_start(*m_dialCVFine3);

    p_mainWidget->pack_start(*p_cv3Frame);


    MyBox *p_cv4Frame = manage(new MyBox("CV Source 4", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_dialCV4 = new LabeledDial("CV", 0, 5, NORMAL, 0.01);
    m_dialCV4->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &CVSGUI::write_control), p_cv4), mem_fun(*m_dialCV4,  &LabeledDial::get_value)));
    p_cv4Frame->pack_start(*m_dialCV4);

	m_dialCVFine4 = new LabeledDial("Fine", -0.5, 0.5, NORMAL, 0.001);
    m_dialCVFine4->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &CVSGUI::write_control), p_cvFine4), mem_fun(*m_dialCVFine4,  &LabeledDial::get_value)));
    p_cv4Frame->pack_start(*m_dialCVFine4);

    p_mainWidget->pack_start(*p_cv4Frame);


    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void CVSGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    switch(port)
    {
    case p_cv1:
        m_dialCV1->set_value(*static_cast<const float*> (buffer));
        break;
    case p_cvFine1:
        m_dialCVFine1->set_value(*static_cast<const float*> (buffer));
        break;
    case p_cv2:
        m_dialCV2->set_value(*static_cast<const float*> (buffer));
        break;
    case p_cvFine2:
        m_dialCVFine2->set_value(*static_cast<const float*> (buffer));
        break;
    case p_cv3:
        m_dialCV3->set_value(*static_cast<const float*> (buffer));
        break;
    case p_cvFine3:
        m_dialCVFine3->set_value(*static_cast<const float*> (buffer));
        break;
    case p_cv4:
        m_dialCV4->set_value(*static_cast<const float*> (buffer));
        break;
    case p_cvFine4:
        m_dialCVFine4->set_value(*static_cast<const float*> (buffer));
        break;
    }
}

static int _ = CVSGUI::register_class("http://github.com/blablack/ams-lv2/cvs/gui");
