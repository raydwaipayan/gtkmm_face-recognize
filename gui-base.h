#include <gtkmm.h>
#include <string>

class GuiBase:public Gtk::Window{
protected:
	Glib::RefPtr<Gtk::Builder> builder;
	
	Gtk::Entry *entrySource;
	Gtk::Entry *entryHaar;
	Gtk::Entry *entryImgPath;

	Gtk::Button *btnCompile;
	Gtk::Button *btnCapture;	
	Gtk::Button *btnTrain;
	Gtk::Button *btnRecognize;
	Gtk::Button *btnCancel;
	

public:
	GuiBase(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);

protected:
	void on_compile_button_clicked();
	void on_capture_button_clicked();
	void on_train_button_clicked();
	void on_recognize_button_clicked();
	void on_cancel_button_clicked();
};


	
