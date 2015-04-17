#ifndef GRAPH_UTIL_IO_HPP
#define GRAPH_UTIL_IO_HPP
#include <fstream>
#include <sstream>
#include <map>
#include "../graph.hpp"
#include "../algorithm/collections.hpp"
//Placeholder implementation,
//will need to be abstracted when adding new formats
/**
 * \brief - io.hpp - Header file that contains all input output operations
 * **/
namespace graph
{
    inline Graph<std::string,int> makeGraph(std::istream& in)
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
    inline Graph<std::string,int> makeGraph(std::string filename)
    {
        std::ifstream in(filename);
        return makeGraph(in);
    }
    /**
     * \brief - Function to display adjacency list of a graph
     * 
     * @param Graph& g - First Parameter, a graph object
     * 
     * @param std::ostream& out = std::cout - Second Paramaeter, an output stream
     * **/
    template<typename Graph>
    void displayGraph(Graph& g, std::ostream& out = std::cout)
    {
        for(auto x = g.begin();x!=g.end();++x)
        {
            out<<"["<<x->first<<"] =>> ";
            for(auto y = g.nbegin(x->first);y!=g.nend(x->first);++y)
            {
                out<<"("<< y->first<<","<< y->second<<") ";
            }
            out<<"*\n";
        }
    }
    template<typename Graph>
    std::string writeGraph(Graph& g)
    {
        std::ostringstream out;
        out<<"directed "<<g.isDirected()<<"\n";
        out<<"weighted 1\n";
        for(auto x = g.begin();x!=g.end();++x)
            out<<"v "<<x->first<<"\n";
        
        for(auto x = g.begin();x!=g.end();++x)
        {
            for(auto y = g.nbegin(x->first);y!=g.nend(x->first);++y)
            {
                out<<"e "<<x->first<<" "<< y->first<<" "<< y->second<<"\n";
            }
        }
        return out.str();
    }
    
    template<typename Graph>
    std::string writeGraphDOT(Graph& g)
    {
        std::ostringstream out;
        std::string connector = "--";
        if (g.isDirected())
            connector = "->";
        out << "graph {\n";
        for (auto e : EdgeList<Graph>(g, false))
            out << std::get<0>(e)<<connector<<std::get<1>(e)<<";\n";
        out << "}\n";
        return out.str();
    }
}
#endif
