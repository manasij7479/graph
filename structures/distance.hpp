#ifndef GRAPH_STRUCTURES_DISTANCE_HPP
#define GRAPH_STRUCTURES_DISTANCE_HPP
#include "../implementation/edge_traits.hpp"
#include "attribute.hpp"
namespace graph
{
    template<typename Graph>
    class DistanceArray
    {
    public:
        typedef typename Graph::EdgeType E;
        typedef typename Graph::VertexType V;
        typedef typename edge_traits<E>::DistanceType D;
        
        bool isUnknown(V v)
        {
            return !dist.isKnown(v);
        }
        void set(V v,D d)
        {
            dist.value(v) = d;
        }
        D get(V v)
        {
            if(isUnknown(v))
                return D(-1);
            else return dist.value(v);
        }
        bool updateIfLess(V v, D newDist)//Generalized lambda version if needed later.
        {
            if(isUnknown(v)||newDist< get(v))
            {
                set(v,newDist);
                return true;
            }
            return false;
        }
        D& operator[](V v)
        {
            return dist.value(v);            
        }
        std::size_t size(){return dist.count();}
    private:
        VertexAttribute<Graph, D> dist;
    };
}

#endif