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
    template<typename Graph>
    class Coloring
    {
    public:
        typedef typename Graph::VertexType V;
        typedef typename Graph::EdgeType E;
        /**
         * \brief - Constructor to initialize chromatic number of the graph
         * **/
        Coloring(Graph& g_):g(g_)
        {
            chromatic_no=g.order();
            doneMapping=false;
        }
        /**
         * \brief - Returns chromtaic number of the graph
         * **/
        int getChromaticNo()
        {
            if(!doneMapping)
                vertexColoring();
            return chromatic_no;
        }
        /**
         * \brief - Returns a map of vertex and corresponding chromatic number
         * **/
        std::map<V,int> getColorMap()
        {
            if(!doneMapping)
                vertexColoring();
            return colormap;
        }
        
    private:
        Graph& g;
        std::map<V,int> colormap;
        int chromatic_no;
        bool doneMapping;
        /**
         * \brief - Returns a map of vertex and corresponding chromatic number for a particular
         * 			sequence of vertices
         * **/
        std::pair<std::map<V,int>,int> assignColor(std::vector<V> vertices)
        {
            std::map<V,int> tempmap;
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
            return std::make_pair(tempmap,ncolor);
        }
        /**
         * \brief - Determines the map of vertices and corresponding chromatic number for all possobile
         * 			sequence of vertices
         * **/
        void vertexColoring()
        {
            std::vector<V> vertices = VertexList(g);
            std::sort(vertices.begin(),vertices.end());
            do 
            {
                std::pair<std::map<V,int>,int> temppair = assignColor(vertices);
                if(temppair.second < chromatic_no)
                {
                    chromatic_no = temppair.second;
                    colormap = temppair.first;
                }
            } while (std::next_permutation(vertices.begin(),vertices.end()));
            doneMapping=true;
        }
        
    };
}

#endif
