#include "../../graph.hpp"
#include "GraphDecl.hpp"
#include "Stream.hpp"
#include <fstream>

int main()
{
    std::ifstream in("test.dot");
    dot::Stream stream(in);
    dot::GraphDecl gd;
    try
    {
        if(!gd.parse(stream))
            std::cout<<"Error";
    }
    catch(const dot::Exception& e)
    {
        std::cout << e.what();
    }
    
}