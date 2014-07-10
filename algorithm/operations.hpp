#ifndef GRAPH_ALGORITHM_OPERATIONS_HPP
#define GRAPH_ALGORITHM_OPERATIONS_HPP
#include "predicates.hpp"
#include "../graph.hpp"
namespace graph
{
    template<typename Graph>
    Graph Union(Graph g1,Graph g2)
    {
        Graph result;
        for(auto i=g1.begin();i!=g1.end();++i)
            result.insertVertex(i->first);
        for(auto i=g2.begin();i!=g2.end();++i)
            result.insertVertex(i->first);
        for(auto i=g1.begin();i!=g1.end();++i)
            for(auto j=g1.nbegin(i->first);j!=g1.nend(i->first);++j)
                result.insertEdge(i->first,j->first,j->second);
        for(auto i=g2.begin();i!=g2.end();++i)
            for(auto j=g2.nbegin(i->first);j!=g2.nend(i->first);++j)
                if(!isAdjacent(result,i->first,j->first))
                    result.insertEdge(i->first,j->first,j->second);
                        
        return result;
    }
    
    template<typename Graph>
    Graph intersection(Graph g1,Graph g2)
    {
        Graph result;
        for(auto i=g1.begin();i!=g1.end();++i)
            if(isVertex(g2,i->first))
                result.insertVertex(i->first);
        for(auto i=result.begin();i!=result.end();++i)
            for(auto j=g1.nbegin(i->first);j!=g1.nend(i->first);++j)
                if(isAdjacent(g2,i->first,j->first))
                    if(!isAdjacent(result,i->first,j->first))
                        result.insertEdge(i->first,j->first,1);
                        
        return result;
    }
    
    template<typename Graph>
    Graph join(Graph g1,Graph g2)
    {
        Graph result=Union(g1,g2);
        for(auto i=g1.begin();i!=g1.end();++i)
            for(auto j=g2.begin();j!=g2.end();++j)
                result.insertEdge(i->first,j->first,1);
         
        return result;
    }
    
    template<typename Graph>
    Graph complement(Graph g1)
    {
        Graph result;
        for(auto i=g1.begin();i!=g1.end();++i)
            result.insertVertex(i->first);
        for(auto i=g1.begin();i!=g1.end();++i)
            for (auto j=g1.begin();j!=g1.end();++j)
                if(i->first!=j->first && !(isAdjacent(g1,i->first,j->first)))
                    result.insertEdge(i->first,j->first,1);
                
        return result;
    }
}
#endif
