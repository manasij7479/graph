#ifndef GRAPH_UTIL_GENERATE_HPP
#define GRAPH_UTIL_GENERATE_HPP
#include "../algorithm/operations.hpp"
#include<stdexcept>
namespace graph
{
	/**     \brief generate.hpp - Contains a library of standard graphs
	* **/
    namespace gen
    {
        /**
         * \brief - Adds n vertices to Graph g
         *  
         * @param Graph<std::string,int>& g - First parameter, a pointer to a graph datastructure
         *   
         * @param int n- Second parameter, the number of vertices to be added
         * 
         * @param int start- Third parameter, the starting position from which the vertices are to be added
         * **/
        
        void add_vertices(Graph<int,int>& g,int n,int start)
        {
            for(int i=start;i<=start+n-1;++i)
                g.insertVertex(i);
        }
        /**
         * \brief - Returns an undirected empty graph 
         * 
         * An undirected empty graph has no vertices, no edges and is undirected
         * 
         * @param std::vector<int>- First parameter, a vector of integers, not used here
         * 
         * @param int- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1, not used here
         * 
         * @returns Graph<int,int> result - a variable to store the empty graph
         * **/
        Graph<int,int> empty(std::vector<int> ,int=1)   
        {
            Graph<int,int> result;
            return result;
        }
        /**
         * \brief - Returns an directed empty graph 
         * 
         * An undirected empty graph has no vertices, no edges and is directed
         * 
         * @param std::vector<int>- First parameter, a vector of integers, not used here
         * 
         * @param int- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1, not used here
         * 
         * @returns Graph<int,int> result - a variable to store the empty graph
         * **/
        Graph<int,int> empty_directed(std::vector<int> ,int=1)   
        {
            Graph<int,int> result(true);
            return result;
        }
        
        /**
         * \brief - Returns a path graph 
         * 
         * In a path graph, each vertex but the first and last has two adjacent vertices.
         * The first and last vertex is adjacent to one vertex each.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Path_graph">Path Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @param args[0] - the number of vertices to be added
         * 
         * @returns Graph<int,int>  result - a variable to store the path graph
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
         * 
         * In a cycle graph, each vertex is adjacent to two vertices.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Cycle_graph">Cycle Graph</a>
         *          *  
         * @param std::vector<int> args - First parameter, a vector of integers
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @param args[0]- The number of vertices to be added
         * 
         * @returns Graph<int,int> result - a variable to store the cycle graph
         * **/
        
        Graph<int,int> cycle(std::vector<int> args,int start=1)
        {
            if (args.size() < 1)
                throw std::runtime_error("Not possible : Argument needed for generating cycle graph ...");
            if (args[0] < 3)
                throw std::runtime_error("Not possible : (n>2) not met ...");
            
            Graph<int,int> result = path({args[0]},start);
            result.insertEdge(start,start+args[0]-1,1);
            
            return result;
        }
        
        /**
         * \brief - Returns a hypercube graph
         * 
         * A hypercube is a n-dimensional analog of a square(n=2) or a cube(n=3).
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Hypercube">Hypercube</a>
         *  
         * @param std::vector<int> args - First parameter, a vector of integers
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @param args[0]- The number of vertices to be added
         * 
         * @returns Graph<int,int> result - a variable to store the hypercube graph
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
         * 
         * In a complete graph, each vertex is adjacent to all the other vertices.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Complete_graph">Complete Graph</a>
         *  
         * @param std::vector<int> args - First parameter, a vector of integers
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @param args[0]- The number of vertices to be added
         * 
         * @returns Graph<int,int> result - a variable to store the complete graph
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
         * 
         * A wheel graph of n vertices contains a cycle of (n-1) vertices and
         * another single vertex joined with all the (n-1) vertices.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Wheel_graph">Wheel Graph</a>
         *  
         * @param std::vector<int> args - First parameter, a vector of integers
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @param args[0]- The number of vertices to be added
         * 
         * @returns Graph<int,int> result - a variable to store the wheel graph
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
         * 
         * In a complete bipartite graph, there are two sets of vertices.
         * Each of the vertices of first set is adjacent to all the vertices of the second set and vice versa.
         * None of the vertices of first set is adjacent to any other vertex in the same set.
         * None of the vertices of second set is adjacent to any other vertex in the same set.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Complete_bipartite_graph">Comlete-Bipartite Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers
         * 
         * @param int start- Third parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @param args[0]- The number of vertices to be added on one side
         *  
         * @param args[1]- The number of vertices to be added on the other side
         * 
         * @returns Graph<int,int> result - a variable to store the complete bipartite graph
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
         * 
         * Star graph is a complete bipartite graph of n vertices with first set containing
         * 1 vertex and second set containin (n-1) vertices.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Star_graph">Star Graph</a>
         *  
         * @param std::vector<int> args - First parameter, a vector of integers
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @param args[0]- The number of vertices to be added
         * 
         * @returns Graph<int,int> result - a variable to store the star graph
         * **/
        
        Graph<int,int> star(std::vector<int> args,int start=1)
        {
            if(args[0]<3)
                throw std::runtime_error("Not Possible : (n>2) not met ...");
            
            return complete_bipartite({1,args[0]},start);
        }
        
        /**
         * \brief - Returns a star polygon graph
         * 
         * In a star polygon graph of p vertices seperated by q vertices, each vertex is 
         * adjacent to the qth vertex starting from itself.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Star_polygon">Star-Polygon Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers
         * 
         * @param int start- Third parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @param args[0]- The number of vertices to be added
         *  
         * @param args[1]- The number of vertices between two vetices with an edge
         * 
         * @returns Graph<int,int> result - a variable to store the star polygon graph
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
         * 
         * A friendship graph of 2n+1 vertices has n cycle graphs with one vertex common
         * to each cycle.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Friendship_graph">Friendship Graph</a>
         *  
         * @param std::vector<int> args - First parameter, a vector of integers
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @param args[0]- The number of vertices to be added
         * 
         * @returns Graph<int,int> result - a variable to store the friendship graph
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
         * 
         * A mobius ladder of n vertices if formed from an n-cycle by adding an edge between
         * opposite pairs of vertices.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Mobius_ladder">Mobius Ladder</a>
         *  
         * @param std::vector<int> args - First parameter, a vector of integers
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @param args[0]- The number of vertices to be added
         * 
         * @returns Graph<int,int> result - a variable to store the mobius ladder graph
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
         * 
         * A grid graph of m x n vertices has m rows, n columns and a vertex
         * at the intersection of each row and column.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Grid_graph">Grid Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @param args[0]- The number of vertices to be added as y coordinates
         *  
         * @param args[1]- The number of vertices to be added as x coordinates
         * 
         * @returns Graph<int,int> result - a variable to store the grid graph
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
         * 
         * A generalized petersen graph of n vertices is obtained by adding an edge between
         * the vertices of a regular polygon of n vertices with the corresponding vertices
         * of a star polygon of n vertices.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Generalized_Peteren_graph">Generalized Petersen Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @param args[0]- The number of vertices to be added
         *  
         * @param args[1]- The number of vertices between two vertices with an 
         * edge in the star polygon
         * 
         * @returns Graph<int,int> result - a variable to store the generalized petersen graph
         * **/
        
        Graph<int,int> generalized_petersen(std::vector<int> args, int start=1)
        {
            Graph<int,int> result = Union(star_polygon({args[0],args[1]},start),cycle({args[0]},start+args[0]));
            for(int i=start;i<=start+args[0]-1;i++)
                result.insertEdge(i,i+args[0],1);
            
            return result;
        }
        
         /**
         * \brief - Returns a k-ary tree
         * 
         * A k-ary tree (k>=2) is a tree with each vertex having <= k childs.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/K-ary_tree">K-ary Tree</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @param args[0]- The number of vertices to be added
         *  
         * @returns Graph<int,int> result - a variable to store the k-ary tree
         * **/
        
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
         * 
         * A wagner graph has 8 vertices and 12 edges. Each vertex is connected by an edge with
         * the 3rd next vertices starting from itself.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Wagner_graph">Wagner Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @returns a mobius_ladder graph of 8 vertices
         * **/
        
        Graph<int,int> wagner(std::vector<int> /*args*/, int start=1)
        {
            return mobius_ladder({8},start);
        }
        
        /**
         * \brief - Returns a butterfly graph
         * 
         * A butterfly graph graph has 5 vertices and 6 edges, with 2 cycles
         * having one common vertex.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Butterfly_graph">Butterfly Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @returns a friendship (2) graph
         * **/
        
        Graph<int,int> butterfly(std::vector<int> /*args*/, int start=1)
        {
            return friendship({2},start);
        }
        
        /**
         * \brief - Returns a petersen graph
         * 
         * A petersen graph is a (5,2) generalized petersen graph
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Petersen_graph">Petersen Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @returns a generalized petersen (5,2) graph
         * **/
        
        Graph<int,int> petersen(std::vector<int> /*args*/, int start=1)
        {
            return generalized_petersen({5,2},start);
        }
        
        /**
         * \brief - Returns a durer graph
         * 
         * A durer graph is a (6,2) generalized petersen graph
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Durer_graph">Durer Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @returns a generalized petersen (6,2) graph
         * **/
        
        Graph<int,int> durer(std::vector<int> /*args*/, int start=1)
        {
            return generalized_petersen({6,2},start);
        }
        
        /**
         * \brief - Returns a desargues graph
         * 
         * A desargues is a (10,3) generalized petersen graph
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Desargues_graph">Desargues Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @returns a generalized petersen (10,3) graph
         * **/
        
        Graph<int,int> desargues(std::vector<int> /*args*/, int start=1)
        {
            return generalized_petersen({10,3},start);
        }
        
        /**
         * \brief - Returns a mobius kantor graph
         * 
         * A mobius kantor graph is a (8,3) generalized petersen graph
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Möbius–Kantor_graph">Möbius–Kantor Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @returns a generalized petersen (8,3) graph
         * **/
        
        Graph<int,int> mobius_kantor(std::vector<int> /*args*/, int start=1)
        {
            return generalized_petersen({8,3},start);
        }
        
        /**
         * \brief - Returns a dodecahedron graph
         * 
         * A dodecahedron graph is a (10,2) generalized petersen graph
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Dodecahedron">Dodecahedron</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @returns a generalized petersen (10,2) graph
         * **/
        
        Graph<int,int> dodecahedron(std::vector<int> /*args*/, int start=1)
        {
            return generalized_petersen({10,2},start);
        }
        
        /**
         * \brief - Returns a nauru graph
         * 
         * A nauru graph is a (12,5) generalized petersen graph
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Nauru_graph">Nauru Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @returns a generalized petersen (12,5) graph
         * **/
        
        Graph<int,int> nauru(std::vector<int> /*args*/, int start=1)
        {
            return generalized_petersen({12,5},start);
        }
        
        /**
         * \brief - Returns a Heawood graph
         * 
         * The Heawood graph is an undirected graph with 14 vertices and 21 edges, 
         * named after Percy John Heawood. It is bipartite, cubic, cage, Hamiltonian.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Heawood_graph">Nauru Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @returns Graph<int,int> - a Heawood graph
         * **/
        Graph<int,int> heawood(std::vector<int> , int start=1)
        {
            auto result = cycle({14},start);
            for(int i=start;i<start+13;i+=2)
            {
                if((i+5)%start+13 == 0)
                    result.insertEdge(i,start+13,1);
                else
                    result.insertEdge(i,(i+5)%start+13,1);
            }
            return result;
        }
        
        /**
         * \brief - Returns a Pappus graph
         * 
         * The Pappus graph is a bipartite 3-regular undirected graph with 18 vertices and 27 edges.
         * It has girth 6, diameter 4, radius 4, chromatic number 2, chromatic index 3 and is both 
         * 3-vertex-connected and 3-edge-connected.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Pappus_graph">Nauru Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @returns Graph<int,int> - a Pappus graph
         * **/
        Graph<int,int> pappus(std::vector<int> , int start=1)
        {
            auto result = cycle({18},start);
            std::vector<int> inc ={5,7,11,7,11};
            int j=start, counter=0;
            for(int i=1;i<=3;i++)
            {
                for(;j<start+6*i-1;++j)
                {
                    if((j + inc[counter]) % 18 == 0)
                        result.insertEdge(j,start+17,1);
                    else
                        result.insertEdge(j,(j + inc[counter]) % start+17,1);
                    counter++;
                }
                counter = 0;
                j++;
            }
            return result;
        }
        
        /**
         * \brief - Returns a Franklin graph
         * 
         * The Franklin graph a 3-regular graph with 12 vertices and 18 edges.It is Hamiltonian 
         * and has chromatic number 2, chromatic index 3, radius 3, diameter 3 and girth 4.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Franklin_graph">Nauru Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @returns Graph<int,int> - a Franklin graph
         * **/
        Graph<int,int> franklin(std::vector<int>, int start=1)
        {
            auto result = cycle({12},start);
            for(int i=start;i<start+5;i+=2)
            {
                result.insertEdge(i,i+7,1);
                result.insertEdge(i+1,i+6,1);
            }
            return result;
        }
        
        /**
         * \brief - Returns a Diamond graph
         * 
         * The diamond graph is a planar undirected graph with 4 vertices and 5 edges. It has 
         * radius 1, diameter 2, girth 3, chromatic number 3 and chromatic index 3. It is also 
         * a 2-vertex-connected and a 2-edge-connected Hamiltonian graph.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Franklin_graph">Nauru Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @returns Graph<int,int> - a Diamond graph
         * **/
        Graph<int,int> diamond(std::vector<int>, int start=1)
        {
            auto result = cycle({4},start);
            result.insertEdge(start+1,start+3,1);
            return result;
        }
        
        /**
         * \brief - Returns a Tietze's graph
         * 
         * Tietze's graph is an undirected cubic graph with 12 vertices and 18 edges It has 
         * diameter 3, girth 3, chromatic number 3 and chromatic index 4. It is also a 
         * 2-vertex-connected non Hamiltonian graph. It is not hypohamiltonian.
         * Reference Link - <a href="http://en.wikipedia.org/wiki/Tietze%27s_graph">Nauru Graph</a>
         * 
         * @param std::vector<int> args - First parameter, a vector of integers, not used here,
         * included for consistency
         * 
         * @param int start- Second parameter, the starting position from which the vertices are 
         * to be added, default value 1
         * 
         * @returns Graph<int,int> - a Tietze's graph
         * **/
        Graph<int,int> tietze(std::vector<int>, int start=1)
        {
            auto g1 = cycle({3},start);
            auto g2 = cycle({9},start+3);
            auto result = graph::Union(g1,g2);
            
            int start2 = start+3;
            for(int i=start,j=start2;i<start+3;++i,j+=3)
                result.insertEdge(i,j,1);
            result.insertEdge(start2+1,start2+5,1);
            result.insertEdge(start2+2,start2+7,1);
            result.insertEdge(start2+4,start2+8,1);
            
            return result;
        }
    }
}
#endif
