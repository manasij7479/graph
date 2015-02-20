#ifndef GRAPH_IMPLEMENTATION_ADJLIST_HPP
#define GRAPH_IMPLEMENTATION_ADJLIST_HPP
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
namespace graph
{
    template
    <
        typename VT,
        typename ET
    >
    class AdjacencyList
    {
    public:
        typedef VT VertexType;
        typedef ET EdgeType;
        typedef typename std::map<VertexType,EdgeType> EdgeList;
        typedef typename EdgeList::iterator EdgeIterator;
        typedef typename std::map<VertexType,EdgeList*>::iterator VertexIterator;
        
        AdjacencyList(bool dir=false):directed(dir){}
        
        void insertVertex(const VertexType& v)
        {
            if(data.find(v)==data.end())
            {
                auto e=new EdgeList();
                data[v]=e;
            }
        }
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
        
        void removeEdge(const VertexType& x,const VertexType& y)
        {
            data[x]->erase(y);
            if(!directed)
                data[y]->erase(x);
        }
        
        VertexIterator begin(){return data.begin();}
        VertexIterator end(){return data.end();}
        VertexIterator find(const VertexType& v){return data.find(v);}
        
        EdgeIterator nbegin(const VertexType& v){return data[v]->begin();}
        EdgeIterator nend(const VertexType& v){return data[v]->end();}
        EdgeIterator nfind(const VertexType& v,const VertexType& n){return data[v]->find(n);}
        
        void showInternal()
        {
            for(auto x:data)
            {
                std::cout<<x.first<<std::endl;
            }
        }
        
        EdgeType weight(const VertexType x,const VertexType y)
        {
            auto i=data[x]->find(y);
            if(i!=data[x]->end())
                return i->second;
            else
                return 0;
        }
        
        bool isDirected(){return directed;}
        uint order(){return data.size();}
    private:
        std::map<VertexType,EdgeList*> data;
        bool directed;
    };
}
#endif