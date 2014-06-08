#ifndef GRAPH_UTIL_IO_HPP
#define GRAPH_UTIL_IO_HPP
#include <istream>
#include <sstream>
#include <map>
#include "../graph.hpp"
//Placeholder implementation,
//will need to be abstracted when adding new formats
namespace graph
{
    Graph<std::string,int> makeGraph(std::istream& in)
    {
        std::string line;
        std::string type,v1,v2,v3;
        int x;
        std::unordered_map<std::string,int> options;
        std::getline(in,line);
        std::istringstream sin(line);
        sin>>type>>x;
        options[type]=x;
        std::getline(in,line);
        std::istringstream sin2(line);
        sin2>>type>>x;
        options[type]=x;
        
        Graph<std::string,int> g(options["directed"]);
        
        while(std::getline(in,line))
        {
            std::istringstream sin(line);
            char type;
            sin>>type;
            if(type=='v')
            {
                std::string v;
                sin>>v;
                g.insertVertex(v);
            }
            else if(type=='e')
            {
                std::string x,y;
                int w=1;
                sin>>x>>y;
                if(options["weighted"])
                    sin>>w;
                g.insertEdge(x,y,w);
            }
        }
        return g;
    }
    template<typename Graph>
    void displayGraph(Graph& g)
    {
        for(auto x = g.begin();x!=g.end();++x)
        {
            std::cout<<"["<<x->first<<"] =>> ";
            for(auto y = g.nbegin(x->first);y!=g.nend(x->first);++y)
            {
                std::cout<<"("<< y->first<<","<< y->second<<") ";
            }
            std::cout<<"*\n";
        }
    }
}
#endif