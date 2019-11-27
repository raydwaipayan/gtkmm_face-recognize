#include <stdio.h>
#include <iostream>
#include <fstream>

#include "FaceRec.cpp"


int main(int argc, char **argv)
{
    if(argc<2)
    {
        printf( "usage: run_training <data_dir> [<technique> <haar_cascade>]\n"
			"--Note: directory should be organized into subdirectories by username\n"
			"--technique options: eigen (default), fisher, lbph\n"
			"--default face detector: etc/haarcascade_frontalface_default.xml\n" );
        return -1;
    }
    std::string pathDir=argv[1];
    std::string technique="eigen";
    std::string pathHaar  = "etc/haarcascade_frontalface_default.xml";
    std::string path;
    if(argc>=3)
    {
        technique=argv[2];
    }
    if(argc>=4)
    {
        path=argv[3];
	pathHaar=path+"haarcascade_frontalface_default.xml";
    }

    std::vector<std::string> usernames;
    std::vector<cv::Mat> images;
    std::vector<int> labels;

    std::vector<std::string> nullVec;

    Utils::walkDirectory(pathDir, nullVec, usernames);

    for(std::size_t i=0;i<usernames.size();i++)
    {
        std::vector<std::string> files;
        Utils::walkDirectory(pathDir+"/"+usernames[i],files, nullVec);

        for(std::size_t j=0;j<files.size();j++)
        {
            cv::Mat temp=cv::imread(pathDir+"/"+usernames[i]+"/"+files[j], cv::IMREAD_GRAYSCALE);

            if(temp.data)
            {
                images.push_back(temp);
                labels.push_back(i);
            }
        }
    }

    if(!images.size())
    {
        std::cout<<"No files found in "<<pathDir<<"\n";
        return -1;
    }

    FaceRec fr(technique, pathHaar);

    std::cout<<"Training "<<technique<<" model..\n";
    fr.Train(images,labels);

    fr.setLabelNames(usernames);

    fr.Save(path+"model");

    std::ofstream pConfig(path+"config");
    pConfig<<"imageCapture=true\n";
    //pConfig<<"imageDir=\n\n";
    pConfig<<"timeout=5\n";
    pConfig<<"threshold=150.00\n";
    pConfig.close();

    std::cout<<"Configuration files successfully written.\n";
    return 0;
}   
