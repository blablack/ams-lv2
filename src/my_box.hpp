#ifndef BOX_H
#define BOX_H

class MyBox: public Gtk::Frame
{
	public:
		MyBox(const Glib::ustring& label, Gtk::Orientation orientation);
		void pack_start(Widget& child);

	private:
		Gtk::Box* p_child;
};

#endif
