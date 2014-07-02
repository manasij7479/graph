#ifndef GRAPH_LAYOUT_FORCE_BASED
#define GRAPH_LAYOUT_FORCE_BASED
#include "layout.hpp"
#include <map>
namespace graph
{
    template<typename Graph>
    class ForceBasedLayout : public Layout<Graph>
    {
    public:
        typedef typename Graph::VertexType VertexType;
        ForceBasedLayout(Graph& g_,Layout<Graph>& l,bool instant_=false):g(g_),instant(instant_),equilibrium(false)
        {
            import(l);
            if(instant)
                while(!equilibrium)
                    generate();
        }
        void import(Layout<Graph>& l)
        {
            for(auto it=g.begin();it!=g.end();++it)
                map[it->first]=l.Vertex(it->first);
        }
        Point Vertex(VertexType v)
        {
            do
            {generate();}
            while(instant && ! equilibrium);
            
            return map[v];
        }
        Curve Edge(VertexType x, VertexType y)
        {
            do
            {generate();}
            while(instant && ! equilibrium);
            
            if(isAdjacent(g,x,y))
                return {map[x],map[y]};
            else return {};
        }
    private:
        void generate()
        {
            ///TODO: Placeholder
        }
        Graph& g;
        std::map<VertexType,Point> map;
        bool instant;
        bool equilibrium;
    };
    
    
}
#endif
