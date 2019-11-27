#include "gui-base.h"
#include "src/recognizeUtil.cpp"
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
	builder->get_widget("entry_imgnum",entryImgNum);
	builder->get_widget("entry_capture_location",entryCaptureLocation);
	builder->get_widget("entry_imgloc",entryImgLoc);
	builder->get_widget("entry_name",entryName);
	builder->get_widget("entry_duration",entryDuration);
	builder->get_widget("rb_1",rb1);
	builder->get_widget("rb_2",rb2);
	builder->get_widget("rb_3",rb3);
	builder->get_widget("button_camera",btnCamera);

	//set the signals
	
	btnCompile->signal_clicked().connect(sigc::mem_fun(*this, &GuiBase::on_compile_button_clicked));
	btnCapture->signal_clicked().connect(sigc::mem_fun(*this, &GuiBase::on_capture_button_clicked));
	btnTrain->signal_clicked().connect(sigc::mem_fun(*this, &GuiBase::on_train_button_clicked));
	btnRecognize->signal_clicked().connect(sigc::mem_fun(*this, &GuiBase::on_recognize_button_clicked));
	btnCancel->signal_clicked().connect(sigc::mem_fun(*this, &GuiBase::on_cancel_button_clicked));

}

int GuiBase::executeProg(const char *file)
{
	int pid=fork();
	if(pid==0)
	{
		system(file);
		exit(0);
	}
	return 1;
}

int GuiBase::cexec(char *file, char **argv)
{
	int pid=fork();
	if(pid==0)
	{
		execv(file,argv);
		exit(2);
	}
	return 1;
}

void GuiBase::on_compile_button_clicked()
{
	std::string path=entrySource->get_text();
	std::string scriptPath=path+"src/compile_all.sh";
	executeProg(scriptPath.c_str());
}

void GuiBase::on_capture_button_clicked()
{
	std::string path=entrySource->get_text();
	std::string haarLocation=entryHaar->get_text();
	std::string captureLocation=entryCaptureLocation->get_text()+entryName->get_text();
	std::string imgNum=entryImgNum->get_text();
	std::string args;
	args="/usr/bin/python2.7 "+path+"src/face-detect-new.py ";
	args=args+haarLocation+" "+imgNum+" "+captureLocation;
	executeProg(args.c_str());	
}

void GuiBase::on_train_button_clicked()
{
	std::string path=entrySource->get_text();
	std::string dataPath=entryImgLoc->get_text();
	std::string haarLocation=entryHaar->get_text();
	std::string file=path+"src/run_training";
	std::string opt;

	if(rb1->get_active()==true)
		opt="eigen";
	else if(rb2->get_active()==true)
		opt="fisher";
	else opt="lbph";
	
	file=file+" "+dataPath+" "+opt+" "+haarLocation;
	executeProg(file.c_str());
}

void GuiBase::on_recognize_button_clicked()
{
	std::string path=entrySource->get_text();
	std::string dataPath=entryImgLoc->get_text();
	std::string duration=entryDuration->get_text();
	int dur=0;
	if(duration!="")
		dur=stoi(duration);
	std::pair<std::string, double> p;
	if(btnCamera->get_active()==true)
	{
		p=predict(path+"src/etc/model",path+"src/etc/config","",dur);

	}
	else
	{
		p=predict(path+"src/etc/model",path+"src/etc/config",dataPath,dur,false);
	}
        Gtk::MessageDialog dialog(*this, "Recognition Result",false , Gtk::MESSAGE_QUESTION, BUTTONS_OK);
	dialog.set_secondary_text(p.first+"\n"+"Accuracy: "+std::to_string(p.second));
	dialog.run();
}

void GuiBase::on_cancel_button_clicked()
{
	exit(0);
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
