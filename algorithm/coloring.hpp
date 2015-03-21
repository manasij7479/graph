/**
 * \brief - Header file containing collection of vertex coloring algorithms
 * **/
#ifndef GRAPH_ALGORITHM_COLORING_HPP
#define GRAPH_ALGORITHM_COLORING_HPP
#include "../graph.hpp"
#include "collections.hpp"
#include "operations.hpp"
#include<map>
#include<vector>
#include<utility>
#include<algorithm>
namespace graph
{
    template<typename Graph, typename ColorType>
    class ColorState
    {
    public:
        typedef typename Graph::VertexType V;
        typedef typename Graph::EdgeType E;
        typedef std::map<ColorType,int> CMapType;
        
        ColorState() {}
        /**
         * \brief - Constructor to initialize chromatic number of the graph
         * **/
        ColorState(Graph g_, CMapType colormap_, int ncolors_) : g(g_), colormap(colormap_), ncolors(ncolors_) {} 
        /**
         * \brief - Returns chromtaic number of the graph
         * **/
        int noOfColorsUsed()
        {
            return ncolors;
        }
        /**
         * \brief - Returns a map of vertex and corresponding chromatic number
         * **/
        CMapType getColorMap()
        {
            return colormap;
        }
        
    private:
        Graph g;
        CMapType colormap;
        int ncolors;
        bool doneMapping;
    };
    
    /**
     * \brief - Returns a map of vertex and corresponding chromatic number for a particular
     *                      sequence of vertices
     * **/
    template<typename Graph>
    ColorState<Graph, typename Graph::VertexType> vertexColoring(Graph& g, std::vector<typename Graph::VertexType> vertices)
    {
        std::map<typename Graph::VertexType,int> tempmap;
        int ncolor=0;
        for(uint i=0;i<vertices.size();++i)
        {
            std::vector<int> used;
            for(auto j=g.nbegin(vertices[i]);j!=g.nend(vertices[i]);++j)
            {
                auto it=tempmap.find(j->first);
                if(it!=tempmap.end())
                    used.push_back(it->second);
            }
            for(int c=1;c<=ncolor+1;++c)
                if(std::find(used.begin(),used.end(),c)==used.end())
                {
                    tempmap[vertices[i]]=c;
                    if(c==ncolor+1)
                        ncolor++;
                    break;
                }
        }
        ColorState<Graph, typename Graph::VertexType> cstate(g,tempmap,ncolor);
        return cstate;
    }
    
    /**
     * \brief - Determines the map of vertices and corresponding chromatic number for all possobile
     *                      sequence of vertices
     * **/
    template<typename Graph>
    ColorState<Graph, typename Graph::VertexType> minVertexColoring(Graph& g)
    {
        int min_color=g.order()+1,i=0;
        ColorState<Graph, typename Graph::VertexType> min_cstate;
        auto vertices = VertexList(g);
        std::sort(vertices.begin(),vertices.end());
        do 
        {
            auto cstate = vertexColoring(g,vertices);
            if(cstate.noOfColorsUsed() < min_color)
            {
                min_color = cstate.noOfColorsUsed();
                min_cstate = cstate;
            }
        } while (std::next_permutation(vertices.begin(),vertices.end()));
//         doneMapping=true;
        return min_cstate;
    }
    
    
    // doesn't produce optimal coloring for SOME ordering of ...
    // ... crown, chordal, interval & indifference graphs
    template<typename Graph>
    ColorState<Graph, typename Graph::VertexType> WelshPowellColoring(Graph& g)
    {
        typedef typename Graph::VertexType V;
        auto d_list = DegreeMap(g);
        auto vlist = VertexList(g);
        std::sort(vlist.begin(),vlist.end(),[&](V x,V y){return d_list[x]>d_list[y];});
        return vertexColoring(g, vlist);
    }
    
    template<typename Graph>
    int chromaticNumber(Graph g)
    {
        return minVertexColoring(g).noOfColorsUsed();
    }
    
    template<typename Graph>
    ColorState
    <
        Graph, 
        std::pair
        <
            typename Graph::VertexType,
            typename Graph::VertexType
        >
    >
    minEdgeColoring(Graph& g)
    {
        typedef typename Graph::VertexType V;
        std::map< std::pair<V,V>, int> resultmap;
        auto l = line(g);
        auto cstate_l = minVertexColoring(l);
        auto cmap=cstate_l.getColorMap();
        for(auto i=cmap.begin();i!=cmap.end();++i)
        {
            auto inv = pairInvert(i->first);
            resultmap[inv] = i->second;
            resultmap[{inv.second,inv.first}] = i->second;
        }
        ColorState<Graph, std::pair<V,V>> cstate_g(g,resultmap,cstate_l.noOfColorsUsed());
        return cstate_g;
    }
    
    template<typename Graph>
    int chromaticIndex(Graph g)
    {
        return minEdgeColoring(g).noOfColorsUsed();
    }
}

#endif
