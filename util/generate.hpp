/**     \brief generate.hpp - Contains a library of standard graphs
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
        
        Graph<std::string,int> path(std::vector<int> args, int start=1)
        {
            if(args[0]<1)
                throw std::runtime_error("Not Possible : (n>0) not met ...");
            
            Graph<std::string,int> result;
            add_vertices(result,args[0],start);
            for(int i=start;i<=start+args[0]-2;++i)
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
        
        Graph<std::string,int> cycle(std::vector<int> args,int start=1)
        {
            if(args[0]<3)
                throw std::runtime_error("Not possible : (n>2) not met ...");
            
            Graph<std::string,int> result = path({args[0]},start);
            result.insertEdge(std::to_string(start),std::to_string(start+args[0]-1),1);

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

        Graph<std::string,int> complete(std::vector<int> args,int start=1)
        {
            if(args[0]<1)
                throw std::runtime_error("Not Possible : (n>0) not met ...");
            
            Graph<std::string,int> result;
            add_vertices(result,args[0],start);
            for(int i=start;i<=start+args[0]-1;++i)
            for(int j=start;j<=start+args[0]-1;++j)
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

        Graph<std::string,int> wheel(std::vector<int> args,int start=1)
        {
            if(args[0]<4)
                throw std::runtime_error("Not Possible : (n>3) not met ...");
            
            Graph<std::string,int> result = cycle({args[0]-1},start+1);
            result.insertVertex(std::to_string(start));
            for(int i=start+1;i<=start+args[0]-1;++i)
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
        
        Graph<std::string,int> complete_bipartite(std::vector<int> args,int start=1)
        {
            if(args[0]<1 || args[1]<1)
                throw std::runtime_error("Not Possible : (m,n>0) not met ...");
            
            Graph<std::string,int> result;
            add_vertices(result,args[1]+args[0],start);
            for(int i=start;i<=start+args[0]-1;++i)
                for(int j=start+args[0];j<=start+args[0]+args[1]-1;++j)
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
        
        Graph<std::string,int> star(std::vector<int> args,int start=1)
        {
            if(args[0]<3)
                throw std::runtime_error("Not Possible : (n>2) not met ...");
            
            return complete_bipartite({1,args[0]},start);
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

        Graph<std::string,int> star_polygon(std::vector<int> args,int start=1)
        {
            if(!(args[1]>1 && args[0]>2*args[1]))
                throw std::runtime_error("Not Possible : (2<2q<p) not met ...");
            
            Graph<std::string,int> result;
            add_vertices(result,args[0],start);
            
            int end=start+args[0]-1;
            for(int i=start,j=start+args[1];i<=end;++i)
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
        
        Graph<std::string,int> friendship(std::vector<int> args,int start=1)
        {
            if(args[0]<2)
                throw std::runtime_error("Not Possible : (n>1) not met ...");
            
            Graph<std::string,int> result = star({args[0]*2},start);
            
            int end=start+2*args[0];
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
        
        Graph<std::string,int> mobius_ladder(std::vector<int> args,int start=1)
        {
            if(args[0]%2 != 0)
                throw std::runtime_error("Not Possible : 'n' must be even ...");
            
            Graph<std::string,int> result = cycle({args[0]},start);
            int end=start+args[0]-1;
            for(int i=start;i<=(start+end)/2;++i)
                result.insertEdge(std::to_string(i),std::to_string(i+args[0]/2),1);
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
        
        Graph<std::string,int> grid(std::vector<int> args,int start=1)
        {
            if(args[0]<1 || args[1]<1)
                throw std::runtime_error("Not Possible : (m,n>0) not met ...");
            
            Graph<std::string,int> result;

            if(args[0]==1 && args[1]==1)
            {
                result.insertVertex(std::to_string(start));
                return result;
            }
            if(args[0]==1)
                return path({args[1]},start);
            if(args[1]==1)
                return path({args[0]},start);

            add_vertices(result,args[0]*args[1],start);

            for(int i=start;i<=start+args[0]*args[1]-1;i+=args[1])
                for(int j=i;j<=i+args[1]-2;++j)
                    result.insertEdge(std::to_string(j),std::to_string(j+1),1);
            for(int i=start;i<=start+args[1]-1;++i)
                for(int j=i+args[1];j<=start+args[0]*args[1]-1;j+=args[1])
                    result.insertEdge(std::to_string(j-args[1]),std::to_string(j),1);

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
        
        Graph<std::string,int> generalized_petersen(std::vector<int> args, int start=1)
        {
            Graph<std::string,int> result = Union(star_polygon({args[0],args[1]},start),cycle({args[0]},start+args[0]));
            for(int i=start;i<=start+args[0]-1;i++)
                result.insertEdge(std::to_string(i),std::to_string(i+args[0]),1);
            
            return result;
        }
        
        /**
        * \brief - Returns a wagner graph
        * Reference Link - http://en.wikipedia.org/wiki/Wagner_graph
        * 
        * int start- Parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * **/
        
        Graph<std::string,int> wagner(std::vector<int> args, int start=1)
        {
            return mobius_ladder({8},start);
        }
        
        /**
        * \brief - Returns a butterfly graph
        * Reference Link - http://en.wikipedia.org/wiki/Butterfly_graph
        * 
        * int start- Parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * **/
        
        Graph<std::string,int> butterfly(std::vector<int> args, int start=1)
        {
            return friendship({2},start);
        }
        
        /**
        * \brief - Returns a petersen graph
        * Reference Link - http://en.wikipedia.org/wiki/Petersen_graph
        * 
        * int start- Parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * **/
        
        Graph<std::string,int> petersen(std::vector<int> args, int start=1)
        {
            return generalized_petersen({5,2},start);
        }
        
        /**
        * \brief - Returns a durer graph
        * Reference Link - http://en.wikipedia.org/wiki/Durer_graph
        * 
        * int start- Parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * **/

        Graph<std::string,int> durer(std::vector<int> args, int start=1)
        {
            return generalized_petersen({6,2},start);
        }
        
        /**
        * \brief - Returns a desargues graph
        * Reference Link - http://en.wikipedia.org/wiki/Desargues_graph
        * 
        * int start- Parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * **/
        
        Graph<std::string,int> desargues(std::vector<int> args, int start=1)
        {
            return generalized_petersen({10,3},start);
        }
        
        /**
        * \brief - Returns a mobius kantor graph
        * Reference Link - http://en.wikipedia.org/wiki/Möbius–Kantor_graph
        * 
        * int start- Parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * **/
        
        Graph<std::string,int> mobius_kantor(std::vector<int> args, int start=1)
        {
            return generalized_petersen({8,3},start);
        }
        
        /**
        * \brief - Returns a dodecahedron graph
        * Reference Link - http://en.wikipedia.org/wiki/Dodecahedron
        * 
        * int start- Parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * **/
        
        Graph<std::string,int> dodecahedron(std::vector<int> args, int start=1)
        {
            return generalized_petersen({10,2},start);
        }
        
        /**
        * \brief - Returns a nauru graph
        * Reference Link - http://en.wikipedia.org/wiki/Nauru_graph
        * 
        * int start- Parameter, the starting position from which the vertices are 
        * to be added, default value 1
        * **/
        
        Graph<std::string,int> nauru(std::vector<int> args, int start=1)
        {
            return generalized_petersen({12,5},start);
        }
    }
}
#endif
