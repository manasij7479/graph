/**
 * \brief - Header file containing collection of vertex coloring algorithms
 * **/
#ifndef GRAPH_ALGORITHM_COLORING_HPP
#define GRAPH_ALGORITHM_COLORING_HPP
#include "../graph.hpp"
#include "collections.hpp"
#include<map>
#include<vector>
#include<utility>
#include<algorithm>
namespace graph
{
//     template<typename Graph>
//     class Coloring
//     {
//     public:
//         typedef typename Graph::VertexType V;
//         typedef typename Graph::EdgeType E;
//         /**
//          * \brief - Constructor to initialize chromatic number of the graph
//          * **/
//         Coloring(Graph& g_):g(g_)
//         {
//             chromatic_no=g.order();
//             doneMapping=false;
//         }
//         /**
//          * \brief - Returns chromtaic number of the graph
//          * **/
//         int getChromaticNo()
//         {
//             if(!doneMapping)
//                 vertexColoring();
//             return chromatic_no;
//         }
//         /**
//          * \brief - Returns a map of vertex and corresponding chromatic number
//          * **/
//         std::map<V,int> getColorMap()
//         {
//             if(!doneMapping)
//                 vertexColoring();
//             return colormap;
//         }
//         
//     private:
//         Graph& g;
//         std::map<V,int> colormap;
//         int chromatic_no;
//         bool doneMapping;
//         /**
//          * \brief - Returns a map of vertex and corresponding chromatic number for a particular
//          * 			sequence of vertices
//          * **/
//         std::pair<std::map<V,int>,int> assignColor(std::vector<V> vertices)
//         {
//             std::map<V,int> tempmap;
//             int ncolor=0;
//             for(auto i=0;i<vertices.size();++i)
//             {
//                 std::vector<int> used;
//                 for(auto j=g.nbegin(vertices[i]);j!=g.nend(vertices[i]);++j)
//                 {
//                     auto it=tempmap.find(j->first);
//                     if(it!=tempmap.end())
//                         used.push_back(it->second);
//                 }
//                 for(int c=1;c<=ncolor+1;++c)
//                     if(std::find(used.begin(),used.end(),c)==used.end())
//                     {
//                         tempmap[vertices[i]]=c;
//                         if(c==ncolor+1)
//                             ncolor++;
//                         break;
//                     }
//             }
//             return std::make_pair(tempmap,ncolor);
//         }
//         /**
//          * \brief - Determines the map of vertices and corresponding chromatic number for all possobile
//          * 			sequence of vertices
//          * **/
//         void vertexColoring()
//         {
//             std::vector<V> vertices = VertexList(g);
//             std::sort(vertices.begin(),vertices.end());
//             do 
//             {
//                 std::pair<std::map<V,int>,int> temppair = assignColor(vertices);
//                 if(temppair.second < chromatic_no)
//                 {
//                     chromatic_no = temppair.second;
//                     colormap = temppair.first;
//                 }
//             } while (std::next_permutation(vertices.begin(),vertices.end()));
//             doneMapping=true;
//         }
//         
//     };
    
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
    ColorState<Graph, typename Graph::VertexType> vertexColoring(Graph g, std::vector<typename Graph::VertexType> vertices)
    {
        std::map<typename Graph::VertexType,int> tempmap;
        int ncolor=0;
        for(auto i=0;i<vertices.size();++i)
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
    ColorState<Graph, typename Graph::VertexType> minVertexColoring(Graph g)
    {
        int min_color=g.order()+1;
        ColorState<Graph, typename Graph::VertexType> min_cstate;
        auto vertices = VertexList(g);
        std::sort(vertices.begin(),vertices.end());
        do 
        {
            auto cstate = vertexColoring(g,vertices);
            if(cstate.noOfColorsUsed() < min_color)
                min_cstate = cstate;
        } while (std::next_permutation(vertices.begin(),vertices.end()));
//         doneMapping=true;
        return min_cstate;
    }
}

#endif
