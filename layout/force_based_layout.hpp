#ifndef GRAPH_LAYOUT_FORCE_BASED
#define GRAPH_LAYOUT_FORCE_BASED
#include "layout.hpp"
#include "../algorithm/predicates.hpp"
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
        ///TODO: Doesn't account for the graph changing
        void generate()
        {
            static const float gc=3000;
            static const float kc=1.0/1000;
            

            if(equilibrium)
                return;
            std::map<VertexType,Point> newmap;
            for(auto x=g.begin();x!=g.end();++x)
            {
                Point cur=map[x->first];
                float fx=0;
                float fy=0;
                for(auto y=g.begin();y!=g.end();++y)
                {
                    
                    if(x->first!=y->first)
                    {
                        Point far=map[y->first];
                        auto dx=cur.x-far.x;
                        auto dy=cur.y-far.y;
                        auto fgx=gc*(dx/std::fabs(dx))/(dx*dx);
                        auto fgy=gc*(dy/std::fabs(dy))/(dy*dy);
                        fx+=fgx;
                        fy+=fgy;
//                         std::cout<<fgx<<' '<<fgy<<' ';
                        if(isAdjacent(g,x->first,y->first))
                        {
//                             std::cout<<dx <<' '<<dy<<std::endl;

                            float fkx=-kc*dx;
                            float fky=-kc*dy;
                            fx+=fkx;
                            fy+=fky;
//                             std::cout<<fkx<<' '<<fky<<' ';
                        }
                        
                    }
                    
                }
//                 std::cin.get();
//                 std::cout<<cur.x<<' '<<cur.y<<' '<<fx<<' '<<fy<<std::endl;
                cur.x+=fx;
                cur.y+=fy;
                newmap[x->first]=cur;
            }
            std::swap(map,newmap);
            
        }
        Graph& g;
        std::map<VertexType,Point> map;
        bool instant;
        bool equilibrium;
    };
    
    
}
#endif
