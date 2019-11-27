#include <gtkmm.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>


class GuiBase:public Gtk::Window{
protected:
	Glib::RefPtr<Gtk::Builder> builder;
	
	Gtk::Entry *entrySource;
	Gtk::Entry *entryHaar;
	Gtk::Entry *entryImgPath;
	Gtk::Entry *entryImgNum;
	Gtk::Entry *entryCaptureLocation;
	Gtk::Entry *entryImgLoc;
	Gtk::Entry *entryName;
	Gtk::Entry *entryDuration;

	Gtk::Button *btnCompile;
	Gtk::Button *btnCapture;	
	Gtk::Button *btnTrain;
	Gtk::Button *btnRecognize;
	Gtk::Button *btnCancel;
	
	Gtk::RadioButton *rb1;
	Gtk::RadioButton *rb2;
	Gtk::RadioButton *rb3;	

	Gtk::CheckButton *btnCamera;

public:
	GuiBase(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);

protected:

	int executeProg(const char *file);
	int cexec(char *file, char **argv);
	void on_compile_button_clicked();
	void on_capture_button_clicked();
	void on_train_button_clicked();
	void on_recognize_button_clicked();
	void on_cancel_button_clicked();
};


	
