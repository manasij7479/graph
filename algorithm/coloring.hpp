#ifndef GRAPH_ALGORITHM_COLORING_HPP
#define GRAPH_ALGORITHM_COLORING_HPP
#include "../graph.hpp"
#include "collections.hpp"
#include "operations.hpp"
#include<map>
#include<vector>
#include<utility>
#include<algorithm>
/**
 * \brief coloring.hpp - Header file containing collection of graph coloring algorithms.
 * **/
namespace graph
{
	/**
	 * \brief - Class to hold the current state of the required datastructures
     * during any graph coloring algorithm.
     * 
     * It colors "ColorType", the template argument, with a color(integer)
     * and stores it in a map. It also stores the no. of colors used.
     * "ColorType" may be a vertex or an edge. 
	 * **/
    template<typename Graph, typename ColorType>
    class ColorState
    {
    public:
        typedef typename Graph::VertexType V;///<Vertex
        typedef typename Graph::EdgeType E;///<Edge
        typedef std::map<ColorType,int> CMapType;///<Color Map
        /**
         * \brief - Default Constructor
         * **/
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
     * 
     * @param Graph &g - First Parameter, a graph object
     * 
     * @param std::vector<typename Graph::VertexType> vertices - Second parameter, a list of vertices
     * 
     * @returns ColorState<Graph, typename Graph::VertexType> cstate - map of vertex and corresponding chromatic number for a particular
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
     * \brief - Determines the map of vertices and corresponding chromatic number for all possible
     *                      sequence of vertices
     * 
     * @param Graph& g - Parameter, a graph object
     * 
     * @returns ColorState<Graph, typename Graph::VertexType> min_cstate - map of vertices and corresponding chromatic number for all possible
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
    
    /**
     * \brief - Vertex Coloring algorithm using some heuristics. Determines the
     *          map of vertices and corresponding chromatic number for all possible
     *                      sequence of vertices
     * 
     * @param Graph& g - Parameter, a graph object
     * 
     * @returns ColorState<Graph, typename Graph::VertexType> - map of vertices and corresponding chromatic number for all possible
     *                      sequence of vertices
     * Reference Link <a href="http://comjnl.oxfordjournals.org/content/10/1/85.full.pdf+html"> WelshPowell </a>
     * **/
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
    /**
     * \brief - Returns the chromatic number for a graph object
     * 
     * @param Graph g - Parameter, a graph object
     * 
     * @returns no of colors used in vertex coloring
     * **/
    template<typename Graph>
    int chromaticNumber(Graph g)
    {
        return minVertexColoring(g).noOfColorsUsed();
    }
    inline std::pair<int, int> pair_invert(int z)
    {
        int w = (std::sqrt(8*z+1)-1)/2;
        int t = (w*w+w)/2;
        int y = z-t;
        int x = w-y;
        return {x, y};
    }
    /**
     * \brief - Determines the map of edges and corresponding chromatic number for
     * 		    all possible sequence of vertices
     * 
     * @param Graph& g - Parameter, a graph object
     * 
     * @returns ColorState<Graph, std::pair<V,V>> cstate_g cstate_g - map of edges and corresponding chromatic number for
     * 		    all possible sequence of vertices
     * **/
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
//         auto cstate_l = minVertexColoring(l);
        auto cstate_l = WelshPowellColoring(l);
        auto cmap=cstate_l.getColorMap();
        for(auto i=cmap.begin();i!=cmap.end();++i)
        {
            auto inv = pair_invert(i->first);
            resultmap[inv] = i->second;
            resultmap[{inv.second,inv.first}] = i->second;
        }
        ColorState<Graph, std::pair<V,V>> cstate_g(g,resultmap,cstate_l.noOfColorsUsed());
        return cstate_g;
    }
    /**
     * \brief - Returns the minimum number of colors used in Edge coloring
     * 
     * @param Graph g - Parameter, a graph object
     * 
     * @returns minimum number of colors used in Edge coloring
     * **/
    template<typename Graph>
    int chromaticIndex(Graph g)
    {
        return minEdgeColoring(g).noOfColorsUsed();
    }
}

#endif
