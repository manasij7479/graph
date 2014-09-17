#ifndef GRAPH_STRUCTURES_DISTANCE_HPP
#define GRAPH_STRUCTURES_DISTANCE_HPP
#include <map>
#include <set>
#include "../implementation/edge_traits.hpp"
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
            return knowledge.find(v)==knowledge.end();
        }
        void set(V v,D d)
        {
            map[v]=d;
            knowledge.insert(v);
        }
        D get(V v)
        {
            if(isUnknown(v))
                return D(-1);
            else return map[v];
        }
        bool updateIfLess(V v, D newDist)//Generalized lambda version if needed later.
        {
            if(isUnknown(v)||newDist<map[v])
            {
                set(v,newDist);
                return true;
            }
            return false;
        }
        D& operator[](V v)
        {
            knowledge.insert(v);//for safety
            return map[v];            
        }
        std::size_t size(){return knowledge.size();}
    private:
        std::map<V,D> map;
        std::set<V> knowledge;
    };
}

#endif