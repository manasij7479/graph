/**     \brief generate.hpp - Contains a library of standard graphs
 * **/

#ifndef GRAPH_UTIL_GENERATE_HPP
#define GRAPH_UTIL_GENERATE_HPP
#include "../algorithm/operations.hpp"
#include<stdexcept>
namespace graph
{
    namespace gen
    {
        /**
         * \brief - Adds n vertices to Graph g
         *  
         * @params Graph<std::string,int>& g - First parameter, a pointer to a graph datastructure
         *   
         * @params int n- Second parameter, the number of vertices to be added
         * 
         * @params int start- Third parameter, the starting position from which the vertices are to be added
         * **/
        
        void add_vertices(Graph<int,int>& g,int n,int start)
        {
            for(int i=start;i<=start+n-1;++i)
                g.insertVertex(i);
        }
        
        Graph<int,int> empty(std::vector<int> ,int=1)   
        {
            Graph<int,int> result;
            return result;
        }
        
        /**
         * \brief - Returns a path graph 
         * 
         * In a path graph, each vertice but the first and last has two adjacent vertices.
         * The first and last vertex is adjacent to one vertex each.
         * Reference Link - http://en.wikipedia.org/wiki/Path_graph
         * 
         * @params std::vector<int> args - First parameter, a vector of integers
         * 
         * @params int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @params args[0] - the number of vertices to be added
         * 
         * @returns Graph<std::string,int> result - a variable to store the path graph
         * **/
        
        Graph<int,int> path(std::vector<int> args, int start=1)
        {
            if(args[0]<1)
                throw std::runtime_error("Not Possible : (n>0) not met ...");
            
            Graph<int,int> result;
            add_vertices(result,args[0],start);
            for(int i=start;i<=start+args[0]-2;++i)
                result.insertEdge(i,i+1,1);
            
            return result;
        }
        
        /**
         * \brief - Returns a cycle graph
         * Reference Link - http://en.wikipedia.org/wiki/Cycle_graph
         *  
         * std::vector<int> args - First parameter, a vector of integers
         * 
         * int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * args[0]- The number of vertices to be added
         * 
         * Graph<std::string,int> result - a variable to store the cycle graph
         * **/
        
        Graph<int,int> cycle(std::vector<int> args,int start=1)
        {
            if(args[0]<3)
                throw std::runtime_error("Not possible : (n>2) not met ...");
            
            Graph<int,int> result = path({args[0]},start);
            result.insertEdge(start,start+args[0]-1,1);
            
            return result;
        }
        
        /**
         * \brief - Returns a hypercube graph
         * Reference Link - http://en.wikipedia.org/wiki/Hypercube
         *  
         * std::vector<int> args - First parameter, a vector of integers
         * 
         * int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * args[0]- The number of vertices to be added
         * 
         * Graph<std::string,int> result - a variable to store the hypercube graph
         * **/
        
        Graph<int,int> hypercube(std::vector<int> args,int start=1)
        {
            if(args[0]<1)
                throw std::runtime_error("Not possible : (n>0) not met ...");
            int n=args[0], x=start, y=1;
            Graph<int,int> result = path({2},x);
            while(pow(2,y)<=pow(2,n-1))
            {
                y++;
                x=x+2;
                auto g = path({2},x);
                result=cartesian_product(result,g);
            }
            return result;
        }
        
        /**
         * \brief - Returns a complete graph
         * Reference Link - http://en.wikipedia.org/wiki/Complete_graph
         *  
         * std::vector<int> args - First parameter, a vector of integers
         * 
         * int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * args[0]- The number of vertices to be added
         * 
         * Graph<std::string,int> result - a variable to store the complete graph
         * **/
        
        Graph<int,int> complete(std::vector<int> args,int start=1)
        {
            if(args[0]<1)
                throw std::runtime_error("Not Possible : (n>0) not met ...");
            
            Graph<int,int> result;
            add_vertices(result,args[0],start);
            for(int i=start;i<=start+args[0]-1;++i)
                for(int j=start;j<=start+args[0]-1;++j)
                    if(i!=j)                                
                        result.insertEdge(i,j,1);
                    
                    return result;
        }
        
        /**
         * \brief - Returns a wheel graph
         * Reference Link - http://en.wikipedia.org/wiki/Wheel_graph
         *  
         * std::vector<int> args - First parameter, a vector of integers
         * 
         * int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * args[0]- The number of vertices to be added
         * 
         * Graph<std::string,int> result - a variable to store the wheel graph
         * **/
        
        Graph<int,int> wheel(std::vector<int> args,int start=1)
        {
            if(args[0]<4)
                throw std::runtime_error("Not Possible : (n>3) not met ...");
            
            Graph<int,int> result = cycle({args[0]-1},start+1);
            result.insertVertex(start);
            for(int i=start+1;i<=start+args[0]-1;++i)
                result.insertEdge(start,i,1);
            
            return result;
        }
        
        /**
         * \brief - Returns a complete bipartite graph
         * Reference Link - http://en.wikipedia.org/wiki/Complete_bipartite_graph
         * 
         * std::vector<int> args - First parameter, a vector of integers
         * 
         * int start- Third parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * args[0]- The number of vertices to be added on one side
         *  
         * args[1]- The number of vertices to be added on the other side
         * 
         * Graph<std::string,int> result - a variable to store the complete bipartite graph
         * **/
        
        Graph<int,int> complete_bipartite(std::vector<int> args,int start=1)
        {
            if(args[0]<1 || args[1]<1)
                throw std::runtime_error("Not Possible : (m,n>0) not met ...");
            
            Graph<int,int> result;
            add_vertices(result,args[1]+args[0],start);
            for(int i=start;i<=start+args[0]-1;++i)
                for(int j=start+args[0];j<=start+args[0]+args[1]-1;++j)
                    result.insertEdge(i,j,1);
                
                return result;
        }
        
        /**
         * \brief - Returns a star graph
         * Reference Link - http://en.wikipedia.org/wiki/Star_graph
         *  
         * std::vector<int> args - First parameter, a vector of integers
         * 
         * int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * args[0]- The number of vertices to be added
         * 
         * Graph<std::string,int> result - a variable to store the star graph
         * **/
        
        Graph<int,int> star(std::vector<int> args,int start=1)
        {
            if(args[0]<3)
                throw std::runtime_error("Not Possible : (n>2) not met ...");
            
            return complete_bipartite({1,args[0]},start);
        }
        
        /**
         * \brief - Returns a star polygon graph
         * Reference Link - http://en.wikipedia.org/wiki/Star_polygon
         * 
         * std::vector<int> args - First parameter, a vector of integers
         * 
         * int start- Third parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * args[0]- The number of vertices to be added
         *  
         * args[1]- The number of vertices between two vetices with an edge
         * 
         * Graph<std::string,int> result - a variable to store the star polygon graph
         * **/
        
        Graph<int,int> star_polygon(std::vector<int> args,int start=1)
        {
            if(!(args[1]>1 && args[0]>2*args[1]))
                throw std::runtime_error("Not Possible : (2<2q<p) not met ...");
            
            Graph<int,int> result;
            add_vertices(result,args[0],start);
            
            int end=start+args[0]-1;
            for(int i=start,j=start+args[1];i<=end;++i)
            {
                result.insertEdge(i,j,1);
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
         * std::vector<int> args - First parameter, a vector of integers
         * 
         * int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * args[0]- The number of vertices to be added
         * 
         * Graph<std::string,int> result - a variable to store the friendship graph
         * **/
        
        Graph<int,int> friendship(std::vector<int> args,int start=1)
        {
            if(args[0]<2)
                throw std::runtime_error("Not Possible : (n>1) not met ...");
            
            Graph<int,int> result = star({args[0]*2},start);
            
            int end=start+2*args[0];
            for(int i=start+1;i<=end;i+=2)
                result.insertEdge(i,i+1,1);
            
            return result;
        }
        
        /**
         * \brief - Returns a modius ladder graph
         * Reference Link - http://en.wikipedia.org/wiki/Möbius_ladder
         *  
         * std::vector<int> args - First parameter, a vector of integers
         * 
         * int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * args[0]- The number of vertices to be added
         * 
         * Graph<std::string,int> result - a variable to store the mobius ladder graph
         * **/
        
        Graph<int,int> mobius_ladder(std::vector<int> args,int start=1)
        {
            if(args[0]%2 != 0)
                throw std::runtime_error("Not Possible : 'n' must be even ...");
            
            Graph<int,int> result = cycle({args[0]},start);
            int end=start+args[0]-1;
            for(int i=start;i<=(start+end)/2;++i)
                result.insertEdge(i,i+args[0]/2,1);
            return result;
        }
        
        /**
         * \brief - Returns a grid graph
         * Reference Link - http://en.wikipedia.org/wiki/Grid_graph
         * 
         * std::vector<int> args - First parameter, a vector of integers
         * 
         * int start- TSecond parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * args[0]- The number of vertices to be added as y coordinates
         *  
         * args[1]- The number of vertices to be added as x coordinates
         * 
         * Graph<std::string,int> result - a variable to store the grid graph
         * **/
        
        Graph<int,int> grid(std::vector<int> args,int start=1)
        {
            if(args[0]<1 || args[1]<1)
                throw std::runtime_error("Not Possible : (m,n>0) not met ...");
            
            Graph<int,int> result;
            
            if(args[0]==1 && args[1]==1)
            {
                result.insertVertex(start);
                return result;
            }
            if(args[0]==1)
                return path({args[1]},start);
            if(args[1]==1)
                return path({args[0]},start);
            
            add_vertices(result,args[0]*args[1],start);
            
            for(int i=start;i<=start+args[0]*args[1]-1;i+=args[1])
                for(int j=i;j<=i+args[1]-2;++j)
                    result.insertEdge(j,j+1,1);
                for(int i=start;i<=start+args[1]-1;++i)
                    for(int j=i+args[1];j<=start+args[0]*args[1]-1;j+=args[1])
                        result.insertEdge(j-args[1],j,1);
                    
                    return result;
        }
        
        /**
         * \brief - Returns a generalized petersen graph
         * Reference Link - http://en.wikipedia.org/wiki/Generalized_Petersen_graph
         * 
         * std::vector<int> args - First parameter, a vector of integers
         * 
         * int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * args[0]- The number of vertices to be added
         *  
         * args[1]- The number of vertices between two vertices with an 
         * edge in the star polygon
         * 
         * Graph<std::string,int> result - a variable to store the generalized petersen graph
         * **/
        
        Graph<int,int> generalized_petersen(std::vector<int> args, int start=1)
        {
            Graph<int,int> result = Union(star_polygon({args[0],args[1]},start),cycle({args[0]},start+args[0]));
            for(int i=start;i<=start+args[0]-1;i++)
                result.insertEdge(i,i+args[0],1);
            
            return result;
        }
        
        Graph<int,int> k_ary_tree(std::vector<int> args,int start=1)   //args[0]=n, args[1]=k
        {
            Graph<int,int> result;
            add_vertices(result,args[0],start);
            
            for(int i=0;i<args[0];++i)
                for(int j=args[1]*i+1;j<=args[1]*i+args[1];++j)
                    if(j+1<=args[0])
                        result.insertEdge(i+1,j+1,1);
                    
                    return result;
        }
        
        /**
         * \brief - Returns a wagner graph
         * Reference Link - http://en.wikipedia.org/wiki/Wagner_graph
         * 
         * std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * int start- Parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * **/
        
        Graph<int,int> wagner(std::vector<int> /*args*/, int start=1)
        {
            return mobius_ladder({8},start);
        }
        
        /**
         * \brief - Returns a butterfly graph
         * Reference Link - http://en.wikipedia.org/wiki/Butterfly_graph
         * 
         * std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * int start- Parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * **/
        
        Graph<int,int> butterfly(std::vector<int> /*args*/, int start=1)
        {
            return friendship({2},start);
        }
        
        /**
         * \brief - Returns a petersen graph
         * Reference Link - http://en.wikipedia.org/wiki/Petersen_graph
         * 
         * std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * int start- Parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * **/
        
        Graph<int,int> petersen(std::vector<int> /*args*/, int start=1)
        {
            return generalized_petersen({5,2},start);
        }
        
        /**
         * \brief - Returns a durer graph
         * Reference Link - http://en.wikipedia.org/wiki/Durer_graph
         * 
         * std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * int start- Parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * **/
        
        Graph<int,int> durer(std::vector<int> /*args*/, int start=1)
        {
            return generalized_petersen({6,2},start);
        }
        
        /**
         * \brief - Returns a desargues graph
         * Reference Link - http://en.wikipedia.org/wiki/Desargues_graph
         * 
         * std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * int start- Parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * **/
        
        Graph<int,int> desargues(std::vector<int> /*args*/, int start=1)
        {
            return generalized_petersen({10,3},start);
        }
        
        /**
         * \brief - Returns a mobius kantor graph
         * Reference Link - http://en.wikipedia.org/wiki/Möbius–Kantor_graph
         * 
         * std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * int start- Parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * **/
        
        Graph<int,int> mobius_kantor(std::vector<int> /*args*/, int start=1)
        {
            return generalized_petersen({8,3},start);
        }
        
        /**
         * \brief - Returns a dodecahedron graph
         * Reference Link - http://en.wikipedia.org/wiki/Dodecahedron
         * 
         * std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * int start- Parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * **/
        
        Graph<int,int> dodecahedron(std::vector<int> /*args*/, int start=1)
        {
            return generalized_petersen({10,2},start);
        }
        
        /**
         * \brief - Returns a nauru graph
         * Reference Link - http://en.wikipedia.org/wiki/Nauru_graph
         * 
         * std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * int start- Parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * **/
        
        Graph<int,int> nauru(std::vector<int> /*args*/, int start=1)
        {
            return generalized_petersen({12,5},start);
        }
    }
}
#endif
