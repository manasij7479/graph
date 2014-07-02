#ifndef GRAPH_LAYOUT_RANDOM_LAYOUT_HPP
#define GRAPH_LAYOUT_RANDOM_LAYOUT_HPP
#include "layout.hpp"
#include "../algorithm/predicates.hpp"
#include <random>

namespace graph
{
    //The points are normally distributed, 
    //uniform distribution would look weird.
    template<typename Graph>
    class RandomLayout : public Layout<Graph>
    {
    public:
        typedef typename Graph::VertexType VertexType;
        RandomLayout(Graph& g_,Point mean={0,0},Point stddev={0.5f,.5f})
            :g(g_),twister(rd()),x(mean.x,stddev.x),y(mean.y,stddev.y)
            {
                generate();
            };
        Point Vertex(VertexType v)
        {
            generate();
            return map[v];
        }
        Curve Edge(VertexType x, VertexType y)
        {
            generate();
            if(isAdjacent(g,x,y))
                return {map[x],map[y]};
            else return {};
        }
    private:
        void generate()
        {
            if(g.order()<=map.size())
                return;
            for(auto it=g.begin();it!=g.end();++it)
            {
                if(map.find(it->first)==map.end())
                {
                    float xp=x(twister);
                    float yp=y(twister);
                    map[it->first]=Point({xp,yp});
                }
            }
               
        }
        Graph& g;
        std::map<VertexType,Point> map;
        
        std::random_device rd;
        std::mt19937 twister;
        std::normal_distribution<> x,y;
        
    };
};
#endif