/**	\brief generate.hpp - Contains a library of standard graphs
 * **/

#ifndef GRAPH_UTIL_GENERATE_HPP
#define GRAPH_UTIL_GENERATE_HPP
#include "../algorithm/operations.hpp"
#include<string>
#include<stdexcept>
namespace graph
{
    namespace gen
    {
        /**
        * \brief - Adds n vertices to Graph g
        *  
        * Graph<std::string,int>& g - First parameter, a pointer to a graph datastructure
        *   
        * int n- Second parameter, the number of vertices to be added
        * 
        * int start- Third parameter, the starting position from which the vertices are to be added
        * **/
        
        void add_vertices(Graph<std::string,int>& g,int n,int start)
        {
            for(int i=start;i<=start+n-1;++i)
                g.insertVertex(std::to_string(i));
        }
        
        /**
        * \brief - Returns a path graph 
        * Reference Link - http://en.wikipedia.org/wiki/Path_graph
        *  
        * int n- First parameter, the number of vertices to be added
        * 
        * int start- Second parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * 
        * Graph<std::string,int> result - a variable to store the path graph
        * **/
        
        Graph<std::string,int> path(int n,int start=1)
        {
            if(n<1)
                throw std::runtime_error("Not Possible : (n>0) not met ...");
            
            Graph<std::string,int> result;
            add_vertices(result,n,start);
            for(int i=start;i<=start+n-2;++i)
                result.insertEdge(std::to_string(i),std::to_string(i+1),1);

            return result;
        }
        
        /**
        * \brief - Returns a cycle graph
        * Reference Link - http://en.wikipedia.org/wiki/Cycle_graph
        *  
        * int n- First parameter, the number of vertices to be added
        * 
        * int start- Second parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * 
        * Graph<std::string,int> result - a variable to store the cycle graph
        * **/
        
        Graph<std::string,int> cycle(int n,int start=1)
        {
            if(n<3)
                throw std::runtime_error("Not possible : (n>2) not met ...");
            
            Graph<std::string,int> result = path(n,start);
            result.insertEdge(std::to_string(start),std::to_string(start+n-1),1);

            return result;
        }
        
        /**
        * \brief - Returns a complete graph
        * Reference Link - http://en.wikipedia.org/wiki/Complete_graph
        *  
        * int n- First parameter, the number of vertices to be added
        * 
        * int start- Second parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * 
        * Graph<std::string,int> result - a variable to store the complete graph
        * **/

        Graph<std::string,int> complete(int n,int start=1)
        {
            if(n<1)
                throw std::runtime_error("Not Possible : (n>0) not met ...");
            
            Graph<std::string,int> result;
            add_vertices(result,n,start);
            for(int i=start;i<=start+n-1;++i)
            for(int j=start;j<=start+n-1;++j)
                if(i!=j)				
                    result.insertEdge(std::to_string(i),std::to_string(j),1);
             
            return result;
        }
        
        /**
        * \brief - Returns a wheel graph
        * Reference Link - http://en.wikipedia.org/wiki/Wheel_graph
        *  
        * int n- First parameter, the number of vertices to be added
        * 
        * int start- Second parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * 
        * Graph<std::string,int> result - a variable to store the wheel graph
        * **/

        Graph<std::string,int> wheel(int n,int start=1)
        {
            if(n<4)
                throw std::runtime_error("Not Possible : (n>3) not met ...");
            
            Graph<std::string,int> result = cycle(n-1,start+1);
            result.insertVertex(std::to_string(start));
            for(int i=start+1;i<=start+n-1;++i)
                result.insertEdge(std::to_string(start),std::to_string(i),1);

            return result;
        }
        
        /**
        * \brief - Returns a complete bipartite graph
        * Reference Link - http://en.wikipedia.org/wiki/Complete_bipartite_graph
        * 
        * int m- First parameter, the number of vertices to be added on one side
        *  
        * int n- Second parameter, the number of vertices to be added on the other side
        * 
        * int start- Third parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * 
        * Graph<std::string,int> result - a variable to store the complete bipartite graph
        * **/
        
        Graph<std::string,int> complete_bipartite(int m,int n,int start=1)
        {
            if(m<1 || n<1)
                throw std::runtime_error("Not Possible : (m,n>0) not met ...");
            
            Graph<std::string,int> result;
            add_vertices(result,m+n,start);
            for(int i=start;i<=start+m-1;++i)
                for(int j=start+m;j<=start+m+n-1;++j)
                    result.insertEdge(std::to_string(i),std::to_string(j),1);

            return result;
        }
        
        /**
        * \brief - Returns a star graph
        * Reference Link - http://en.wikipedia.org/wiki/Star_graph
        *  
        * int n- First parameter, the number of vertices to be added
        * 
        * int start- Second parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * 
        * Graph<std::string,int> result - a variable to store the star graph
        * **/
        
        Graph<std::string,int> star(int n,int start=1)
        {
            if(n<3)
                throw std::runtime_error("Not Possible : (n>2) not met ...");
            
            return complete_bipartite(1,n,start);
        }

		/**
        * \brief - Returns a star polygon graph
        * Reference Link - http://en.wikipedia.org/wiki/Star_polygon
        * 
        * int p- First parameter, the number of vertices to be added
        *  
        * int q- Second parameter, the number of vertices between two vetices with an edge
        * 
        * int start- Third parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * 
        * Graph<std::string,int> result - a variable to store the star polygon graph
        * **/

        Graph<std::string,int> star_polygon(int p,int q,int start=1)
        {
            if(!(q>1 && p>2*q))
                throw std::runtime_error("Not Possible : (2<2q<p) not met ...");
            
            Graph<std::string,int> result;
            add_vertices(result,p,start);
            
            int end=start+p-1;
            for(int i=start,j=start+q;i<=end;++i)
            {
                result.insertEdge(std::to_string(i),std::to_string(j),1);
                if(j==end)
                    j=start;
                else
                    j++;
            }
            
            return result;
        }
        
        /**
        * \brief - Returns a friendship graph
        * Reference Link - http://en.wikipedia.org/wiki/Friendship_graph
        *  
        * int n- First parameter, the number of vertices to be added
        * 
        * int start- Second parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * 
        * Graph<std::string,int> result - a variable to store the friendship graph
        * **/
        
        Graph<std::string,int> friendship(int n,int start=1)
        {
            if(n<2)
                throw std::runtime_error("Not Possible : (n>1) not met ...");
            
            Graph<std::string,int> result = star(n*2,start);
            
            int end=start+2*n;
            for(int i=start+1;i<=end;i+=2)
                result.insertEdge(std::to_string(i),std::to_string(i+1),1);
            
            return result;
        }
        
        /**
        * \brief - Returns a modius ladder graph
        * Reference Link - http://en.wikipedia.org/wiki/Möbius_ladder
        *  
        * int n- First parameter, the number of vertices to be added
        * 
        * int start- Second parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * 
        * Graph<std::string,int> result - a variable to store the mobius ladder graph
        * **/
        
        Graph<std::string,int> mobius_ladder(int n,int start=1)
        {
            if(n%2 != 0)
                throw std::runtime_error("Not Possible : 'n' must be even ...");
            
            Graph<std::string,int> result = cycle(n,start);
            int end=start+n-1;
            for(int i=start;i<=(start+end)/2;++i)
                result.insertEdge(std::to_string(i),std::to_string(i+n/2),1);
            return result;
        }
        
         /**
        * \brief - Returns a grid graph
        * Reference Link - http://en.wikipedia.org/wiki/Grid_graph
        * 
        * int m- First parameter, the number of vertices to be added as y coordinates
        *  
        * int n- Second parameter, the number of vertices to be added as x coordinates
        * 
        * int start- Third parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * 
        * Graph<std::string,int> result - a variable to store the grid graph
        * **/
        
        Graph<std::string,int> grid(int m,int n,int start=1)
        {
            if(m<1 || n<1)
                throw std::runtime_error("Not Possible : (m,n>0) not met ...");
            
            Graph<std::string,int> result;

            if(m==1 && n==1)
            {
                result.insertVertex(std::to_string(start));
                return result;
            }
            if(m==1)
                return path(n,start);
            if(n==1)
                return path(m,start);

            add_vertices(result,m*n,start);

            for(int i=start;i<=start+m*n-1;i+=n)
                for(int j=i;j<=i+n-2;++j)
                    result.insertEdge(std::to_string(j),std::to_string(j+1),1);
            for(int i=start;i<=start+n-1;++i)
                for(int j=i+n;j<=start+m*n-1;j+=n)
                    result.insertEdge(std::to_string(j-n),std::to_string(j),1);

            return result;
        }
        
        /**
        * \brief - Returns a generalized petersen graph
        * Reference Link - http://en.wikipedia.org/wiki/Generalized_Petersen_graph
        * 
        * int n- First parameter, the number of vertices to be added
        *  
        * int k- Second parameter, the number of vertices between two vertices with an 
        * edge in the star polygon
        * 
        * int start- Third parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * 
        * Graph<std::string,int> result - a variable to store the generalized petersen graph
        * **/
        
        Graph<std::string,int> generalized_petersen(int n,int k,int start=1)
        {
            Graph<std::string,int> result = Union(star_polygon(n,k,start),cycle(n,start+n));
            for(int i=start;i<=start+n-1;i++)
                result.insertEdge(std::to_string(i),std::to_string(i+n),1);
            
            return result;
        }
        
        /**
        * \brief - Returns a wagner graph
        * Reference Link - http://en.wikipedia.org/wiki/Wagner_graph
        * 
        * int start- Parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * **/
        
        Graph<std::string,int> wagner(int start=1)
        {
            return mobius_ladder(8,start);
        }
        
        /**
        * \brief - Returns a butterfly graph
        * Reference Link - http://en.wikipedia.org/wiki/Butterfly_graph
        * 
        * int start- Parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * **/
        
        Graph<std::string,int> butterfly(int start=1)
        {
            return friendship(2,start);
        }
        
        /**
        * \brief - Returns a petersen graph
        * Reference Link - http://en.wikipedia.org/wiki/Petersen_graph
        * 
        * int start- Parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * **/
        
        Graph<std::string,int> petersen(int start=1)
        {
            return generalized_petersen(5,2,start);
        }
        
        /**
        * \brief - Returns a durer graph
        * Reference Link - http://en.wikipedia.org/wiki/Durer_graph
        * 
        * int start- Parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * **/

        Graph<std::string,int> durer(int start=1)
        {
            return generalized_petersen(6,2,start);
        }
        
        /**
        * \brief - Returns a desargues graph
        * Reference Link - http://en.wikipedia.org/wiki/Desargues_graph
        * 
        * int start- Parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * **/
        
        Graph<std::string,int> desargues(int start=1)
        {
            return generalized_petersen(10,3,start);
        }
        
        /**
        * \brief - Returns a mobius kantor graph
        * Reference Link - http://en.wikipedia.org/wiki/Möbius–Kantor_graph
        * 
        * int start- Parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * **/
        
        Graph<std::string,int> mobius_kantor(int start=1)
        {
            return generalized_petersen(8,3,start);
        }
        
        /**
        * \brief - Returns a dodecahedron graph
        * Reference Link - http://en.wikipedia.org/wiki/Dodecahedron
        * 
        * int start- Parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * **/
        
        Graph<std::string,int> dodecahedron(int start=1)
        {
            return generalized_petersen(10,2,start);
        }
        
        /**
        * \brief - Returns a nauru graph
        * Reference Link - http://en.wikipedia.org/wiki/Nauru_graph
        * 
        * int start- Parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * **/
        
        Graph<std::string,int> nauru(int start=1)
        {
            return generalized_petersen(12,5,start);
        }
    }
}
#endif
