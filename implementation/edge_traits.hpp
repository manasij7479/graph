/**
 * \brief edge_traits.hpp - Header file to store edge traits
 * **/
#ifndef GRAPH_IMPLEMENTATION_EDGE_TRAITS
#define GRAPH_IMPLEMENTATION_EDGE_TRAITS
namespace graph
{
    /** 
     *\brief - defines a structure of edge traits with vertex type
     * **/
    template<typename V>
    struct edge_traits
    {
        typedef V DistanceType; 
    };
    /**
     * \brief - defines a structure of edge traits with long
     * **/
    template<>
    struct edge_traits<int>
    {
        typedef long DistanceType;
    };
    //Add more later when necessary
}
#endif
