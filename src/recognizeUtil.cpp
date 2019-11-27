#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <bits/stdc++.h>
#include <ctime>
#include "FaceRec.cpp"
#define ff first
#define ss second
const std::string none="NONE";

std::pair<std::string,double> predict(std::string modelDir, std::string configDir, std::string imagePath ,int duration, bool imCapture=true)
{
    std::map<std::string, std::string> config;
    Utils::getConfig(configDir,config);

    std::time_t timeout=std::stoi(config["timeout"]);
    double threshold = std::stod( config["threshold"] );
    if(duration!=0)
    {
	timeout=(std::time_t)duration;
    }
    FaceRec fr=FaceRec();
    fr.Load(modelDir);
    
    std::time_t start=std::time(NULL);
    cv::VideoCapture vc;
	
    std::map<int, int> m;
    std::map<std::string, int> mm;    

    //test camera
    if(imCapture && !vc.open(0))
    {
        std::cerr<<"Could not open camera\n";
        return std::make_pair("Could not open scamera!", 0.);
    }
    else if(!imCapture)
    {
        //search the directory for images
        std::string temp;
        std::vector<std::string> files;
        std::vector<cv::Mat> images;
        std::vector<std::string> nullVec;

        Utils::walkDirectory(imagePath, files, nullVec);

        for(std::size_t i=0;i<files.size();i++)
        {
            std::vector<std::string> files;
            cv::Mat temp=cv::imread(imagePath+"/"+files[i], cv::IMREAD_GRAYSCALE);
            if(temp.data)
            {
                images.push_back(temp);
            }
        }

        if(!images.size())
        {
            std::cout<<"No files found in "<<imagePath<<"\n";
            return std::make_pair(none,0);
        }

        for(std::size_t i=0;i<images.size();i++){
            double confidence=0.0;
            int prediction=-1;

            fr.Predict(images[i],prediction, confidence);
        
            if(prediction==-1) continue;
            if(confidence < threshold)
            {
                mm[fr.getLabelName(prediction)]++;
            }
        }
    }
    if(imCapture){
        while(std::time(NULL)-start<timeout)
        {
            cv::Mat im;
            if(imCapture)
            {
                vc.read(im);
                cv::cvtColor(im,im,cv::COLOR_BGR2GRAY);
            }

            if(im.size().area()==0)
                continue;

            double confidence=0.0;
            int prediction=-1;

            fr.Predict(im,prediction, confidence);
        
            if(prediction==-1) continue;
            if(confidence < threshold)
            {
                mm[fr.getLabelName(prediction)]++;
            }

        }
    }

    std::string ans="";
    int freq=0;
    int tfreq=0;
    for(auto x:mm)
    {
        tfreq+=x.second;
	    if(x.second>freq)
	    {
		    ans=x.first;
		    freq=x.second;
		}
    }
    double acc=freq/double(tfreq);
    if(acc>0.9)
    	return std::make_pair(ans,acc);
    return std::make_pair(none, acc);
}	

