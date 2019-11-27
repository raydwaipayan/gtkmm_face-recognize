#include "gui-base.h"
using namespace Gtk;

GuiBase::GuiBase(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder> &refGlade): Gtk::Window(cobject), builder(refGlade){
	
	builder->get_widget("button_compile", btnCompile);
	builder->get_widget("button_capture", btnCapture);
	builder->get_widget("button_train", btnTrain);
	builder->get_widget("button_recognize",btnRecognize);
	builder->get_widget("button_cancel", btnCancel);
	builder->get_widget("entry_source",entrySource);
	builder->get_widget("entry_haar", entryHaar);
	builder->get_widget("entry_imgpath",entryImgPath);

	//set the signals
	btnTrain->signal_clicked().connect(sigc::mem_fun(*this, &GuiBase::on_train_button_clicked));
	btnCancel->signal_clicked().connect(sigc::mem_fun(*this, &GuiBase::on_cancel_button_clicked));

}

void GuiBase::on_compile_button_clicked()
{
	std::string path=entrySource->get_text();
	
}

void GuiBaseLLon_capture_button_clicked()
{
	//do
}

void GuiBase::on_train_button_clicked()
{
	//do
}

void GuiBase::on_recognize_button_clicked()
{
	//do
}

void GuiBase::on_cancel_button_clicked()
{
	//do
}

int main(int argc, char** argv)
{
	Main kit(argc,argv);
	Glib::RefPtr<Gtk::Builder> builder=Gtk::Builder::create_from_file("gui-base.glade");

	GuiBase *gui=0;
	builder->get_widget_derived("GuiBase",gui);
	kit.run(*gui);
	
	return 0;
}
