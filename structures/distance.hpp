/**
 * \brief distance.hpp - Header file containing structure to hold distance of vertices of a graph
 * **/
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
        /**
         * \brief - function to check if distance of a vertex is unknown or known
         * 
         * @param V v - Parameter, a vertex
         * **/
        bool isUnknown(V v)
        {
            return !dist.isKnown(v);
        }
        /**
         * \brief - function to set distance of vertex
         * 
         * @param V v - First Parameter, a vertex
         * 
         * @param D d - Second Parameter, a distance
         * **/
        void set(V v,D d)
        {
            dist.value(v) = d;
        }
        /**
         * \brief - fuction to get distance of a vertex
         * 
         * @param V v- Parameter, a vertex
         * **/
        D get(V v)
        {
            if(isUnknown(v))
                return D(-1);
            else return dist.value(v);
        }
        /**
         * \brief - function to update the distance of a vertex
         * 
         * the distance of a vertex is updated if the new calculated distance is less than
         * the old distance, or if the distance of the vertex is priorly unknown
         * 
         * @param V v - First parameter, a vertex
         * 
         * @param D newDist - Second Parameter, the new calculated distance of v
         * **/
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
