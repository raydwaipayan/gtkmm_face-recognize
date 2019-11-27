#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include "Utils.cpp"

class FaceRec
{
private:
    cv::Ptr<cv::face::FaceRecognizer> fr;
    cv::CascadeClassifier cascade;
    std::size_t sizeFace;
    std::string method;
    std::string pathCascade;
    
    void setMethod(const std::string s)
    {
        if(s=="eigen")
        {
            fr=cv::face::EigenFaceRecognizer::create();
        }
        else if(s=="fisher")
        {
            fr=cv::face::FisherFaceRecognizer::create();
        }
        else if(s=="lbph")
        {
            fr=cv::face::LBPHFaceRecognizer::create();
        }
        else
        {
            std::cout<<"Invalid method! Defaulting to eigenface\n";
            fr=cv::face::EigenFaceRecognizer::create();
            method="eigen";
        }
        method=s;
    }
    
    bool loadCascade(const std::string s)
    {
        pathCascade=s;

        if(!cascade.load(pathCascade))
        {
            std::cout<<"Could not load haar cascade\n";
            return false;
        }
        return true;
    }

    bool cropFace(const cv::Mat image, cv::Mat &cropped)
    {
        std::vector<cv::Rect> faces;
        cascade.detectMultiScale(image,faces,1.05,8,0 |2, cv::Size(40,40));

        if(!faces.size())
        {
            return false;
        }

        cropped=image(faces[0]);
        cv::resize(cropped,cropped, cv::Size(sizeFace, sizeFace));

        return true;

    }
public:
    FaceRec(): sizeFace(96)
    {}

    FaceRec(const std::string method, const std::string pathCascade): sizeFace(96)
    {
        setMethod(method);
        loadCascade(pathCascade);
    }

    void Train(const std::vector<cv::Mat> images,const std::vector<int> labels)
    {
        if(!images.size())
        {
            std::cout<<"Empty!\n";
            return;
        }

        std::vector<cv::Mat> imagesCropped;
        std::vector<int> labelsCropped;
            
        for(size_t i=0;i<images.size();i++)
        {
            cv::Mat crop;
            if(cropFace(images[i],crop))
            {
                labelsCropped.push_back(labels[i]);
                imagesCropped.push_back(crop);
            }
        }

        fr->train(imagesCropped,labelsCropped);
    }

    void Predict(const cv::Mat im, int &label, double &confidence)
    {
        cv::Mat cropped;

        if(!cropFace(im,cropped))
        {
            label=-1;
            confidence=10000;
            return;
        }

        fr->predict(cropped,label,confidence);
    }

    void Save(const std::string path)
    {
        std::ofstream file;
        file.open(path);
        file<<"model="<<method<<"\n";
        file<<"sizeFace="<<sizeFace<<"\n";
        file.close();

        fr->save(path+"-facerec.xml");

        std::ifstream org(pathCascade, std::ios::binary);
        std::ofstream cpy(path+"-cascade.xml",std::ios::binary);
        cpy<<org.rdbuf();

        org.close();
        cpy.close();
    }

    void Load(const std::string path)
    {
        std::map<std::string, std::string> config;
        Utils::getConfig(path,config);

        sizeFace=stoi(config["sizeFace"]);
        setMethod(config["model"]);

        loadCascade(path+"-cascade.xml");
        fr->read(path+"-facerec.xml");
    }

    void setLabelNames(const std::vector<std::string> names)
    {
        for(std::size_t i=0;i<names.size();i++)
        {
            fr->setLabelInfo(i,names[i]);
        }
    }

    std::string getLabelName(int index)
    {
        return fr->getLabelInfo(index);
    }

};