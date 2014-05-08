#ifndef GRAPH_IMPLEMENTATION_EDGE_TRAITS
#define GRAPH_IMPLEMENTATION_EDGE_TRAITS
namespace graph
{
    template<typename V>
    struct edge_traits
    {
        typedef V DistanceType; 
    };
    
    template<>
    struct edge_traits<int>
    {
        typedef long DistanceType;
    };
    //Add more later when necessary
}
#endif