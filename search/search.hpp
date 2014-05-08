#ifndef GRAPH_SEARCH_HPP
#define GRAPH_SEARCH_HPP
#include "../graph.hpp"
#include "../implementation/edge_traits.hpp"
#include <map>

namespace graph
{
    template
    <
        typename Graph,
        template <typename> class Container
    >
    class Search
    {
    public:
        typedef typename Graph::VertexType VertexType;
        typedef typename edge_traits<VertexType>::DistanceType DistanceType;
        
        Search():fringe()
        {
            
        }
    private:
        Container<VertexType> fringe;
        std::map<VertexType,DistanceType> dist;
    };
}
#endif