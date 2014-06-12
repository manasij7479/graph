#ifndef GRAPH_UTIL_GENERATE_HPP
#define GRAPH_UTIL_GENERATE_HPP
#include<string>
namespace graph
{
    namespace gen
    {
        Graph<std::string,int> cycle(int n)
        {
            Graph<std::string,int> result;
            for(int i=1;i<=n;++i)
                result.insertVertex(std::to_string(i));
            for(int i=0;i<n;++i)
                result.insertEdge(std::to_string(i+1),std::to_string((i+1)%n+1),1);

            return result;
        }
        
    }
}
#endif