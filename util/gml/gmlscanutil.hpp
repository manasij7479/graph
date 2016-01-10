#ifndef GRAPH_UTIL_GMLSCANUTIL_HPP
#define GRAPH_UTIL_GMLSCANUTIL_HPP
#include<iostream>
#include<fstream>
#include<string>
namespace graph
{
    class GMLScanUtil
    {
    public:
        GMLScanUtil(std::string filename_) : filename(filename_)
        {
            inputStream.open(filename);
            if(!inputStream.good())
                std::cout<<"Error in opening file ..."<<std::endl;
        }
        
        std::ifstream* getInputStream() { return &inputStream; }
        
    private:
        std::string filename;
        std::ifstream inputStream;
    };
}
#endif