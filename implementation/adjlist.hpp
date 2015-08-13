#ifndef GRAPH_IMPLEMENTATION_ADJLIST_HPP
#define GRAPH_IMPLEMENTATION_ADJLIST_HPP
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
/**
 * \brief adjlist.hpp - Header file that contains adjacency list of a graph 
 * **/
namespace graph
{
	/**
	 * \brief - class to store adjacency list of a graph
	 * **/
    template
    <
        typename VT,
        typename ET
    >
    class AdjacencyList
    {
    public:
        typedef VT VertexType;///<Vertex
        typedef ET EdgeType;///<Edge
        typedef typename std::map<VertexType,EdgeType> EdgeList;///<List of Edges
        typedef typename EdgeList::iterator EdgeIterator;///<Iterator for Edges
        typedef typename std::map<VertexType,EdgeList*>::iterator VertexIterator;///<Iterator of Vertices
        
        /** \brief -  constructor**/
        AdjacencyList(bool dir=false):directed(dir){}
        /** \brief - copy constructor **/
                AdjacencyList(const AdjacencyList<VT,ET>& g)
        {
            directed = g.directed;
            for (auto p: g.data)
                data[p.first] = new EdgeList(*p.second);
        }
        /** \brief - overloaded '=' operator for assigning one graph object to another. **/
        AdjacencyList<VT, ET>& operator=(const AdjacencyList<VT, ET>& g)
        {
            for (auto p: data)
                delete p.second;
            data.clear();
            directed = g.directed;
            for (auto p: g.data)
                data[p.first] = new EdgeList(*p.second);
            return *this;
        }
        /** \brief - Destructor **/
        ~AdjacencyList()
        {
            for (auto p: data)
                delete p.second;
        }
        
        /**
         * \brief - function to insert a vertex to a graph
         * 
         * @param const VertexType& v - Parameter, a vertex to be added
         * **/
        void insertVertex(const VertexType& v)
        {
            if(data.find(v)==data.end())
            {
                auto e=new EdgeList();
                data[v]=e;
            }
        }
        /**
         * \brief - function to remove a vertex from a graph
         * 
         * @param VertexType v - Parameter, a vertex to be removed
         * **/
        void removeVertex(VertexType v)
        {
            for(auto& p:data)
            {
                EdgeList& m=*p.second;
                for(auto x=m.begin();x!=m.end();++x)
                {
                    if(x->first==v)
                        m.erase(x);
                }
            }
            
            delete data[v];
            data.erase(v);
        }
        /**
         * \brief - function to insert an edge to a graph
         * 
         * @param const VertexType& x - First Parameter, source vertex
         * 
         * @param const VertexType& y - Second Parameter, destination vertex
         * 
         * @param const EdgeType& e - Third parameter, an edge
         * **/
        void insertEdge(const VertexType& x,const VertexType& y,const EdgeType& e)
        {
            auto xit=data.find(x);
            auto yit=data.find(y);
            if(xit==data.end()||yit==data.end())
                throw std::runtime_error("Vertex does not exist.");
            data[x]->insert({y,e});
            if(!directed)
                data[y]->insert({x,e});
        }
        /**
         * \brief - function to remove an edge from a graph
         * 
         * @param const VertexType& x - First Parameter, source vertex
         * 
         * @param const VertexType& y - Second Parameter, destination vertex
         * 
         * **/
        void removeEdge(const VertexType& x,const VertexType& y)
        {
            data[x]->erase(y);
            if(!directed)
                data[y]->erase(x);
        }
        
        VertexIterator begin(){return data.begin();}///< Returns the VertexIterator for beginning. 
        VertexIterator end(){return data.end();}///< Returns the VertexIterator for end.
        /**
         * \brief - function to find a vertex of a graph
         * 
         * @param const VertexType& v - Parameter, a vertex to be found
         * 
         * @returns VertexIterator - Iterator of the vertex if found, iterator to end() otherwise
         * **/
        VertexIterator find(const VertexType& v){return data.find(v);}
        
        EdgeIterator nbegin(const VertexType& v){return data[v]->begin();}///< Returns the EdgeIterator for beginning. 
        EdgeIterator nend(const VertexType& v){return data[v]->end();}///< Returns the EdgeIterator for end.
        /**
         * \brief - function to find a neighbour of a vertex of a graph
         * 
         * @param const VertexType& v - First Parameter, a vertex whose neighbour to be found
         * 
         * @param const VertexType& n - Second Parameter, the neighbour to be found
         * 
         * @returns EdgeIterator - Iterator of the vertex if found, iterator to nend() otherwise
         * **/
        EdgeIterator nfind(const VertexType& v,const VertexType& n){return data[v]->find(n);}
        /**
         * \brief - function to display vertices of a graph
         * **/
        void showInternal()
        {
            for(auto x:data)
            {
                std::cout<<x.first<<std::endl;
            }
        }
        /**
         * \brief - function to to get weight of an edge of a graph
         * 
         * @param const VertexType& x - First Parameter, source vertex
         * 
         * @param const VertexType& y - Second Parameter, destination vertex
         * **/
        EdgeType weight(const VertexType x,const VertexType y)
        {
            auto i=data[x]->find(y);
            if(i!=data[x]->end())
                return i->second;
            else
                return 0;
        }
        
        /**
         * \brief - returns true if directed, false otherwise.
         * **/
        bool isDirected(){return directed;}
        
        /**
         * \brief - function to find the order of the graph.
         * 
         * @returns uint order - the order of the graph.
         * **/
        uint order(){return data.size();}
    private:
        std::map<VertexType,EdgeList*> data;
        bool directed;
    };
}
#endif
