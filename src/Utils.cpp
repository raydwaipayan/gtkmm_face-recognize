#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <map>
#include <dirent.h>
#include <vector>

class Utils
{
public:
    static void getConfig(std::string path, std::map<std::string, std::string> &config)
    {
        std::ifstream inFile(path);

        if(!inFile)
        {
            std::cout<<"Cannot open file!\n";
            return;
        }

        std::stringstream ssFile;
        ssFile<<inFile.rdbuf();

        inFile.close();
        
        std::string line;

        while(std::getline(ssFile,line))
        {
            std::istringstream ssLine(line);
            std::string key;
            if(std::getline(ssLine, key, '='))
            {
                std::string value;
                if(std::getline(ssLine,value))
                {
                    config[key]=value;
                }
            }
        }
    }
    static void walkDirectory(const std::string pathDir, std::vector<std::string> &files, std::vector<std::string> &subs)
    {
        DIR *dirMain;
        DIR *dirSub;
        dirMain=opendir(pathDir.c_str());
        struct dirent *curr;
        if(dirMain)
        {
            curr=readdir(dirMain);
            while(curr)
            {
                if(std::strcmp(curr->d_name,".")==0 || std::strcmp(curr->d_name,"..")==0)
                {
                    curr=readdir(dirMain);
                    continue;
                }

                dirSub=opendir((pathDir+"/"+curr->d_name).c_str());
                if(dirSub)
                {
                    subs.push_back(curr->d_name);
                    closedir(dirSub);
                }
                else
                {
                    files.push_back(curr->d_name);
                }
                curr=readdir(dirMain);
            }

            closedir(dirMain);
        }
    }
};