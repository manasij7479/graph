#ifndef GRAPH_UTIL_GENERATE_HPP
#define GRAPH_UTIL_GENERATE_HPP
#include<string>
#include<stdexcept>
namespace graph
{
    namespace gen
    {
        void add_vertices(Graph<std::string,int>& g,int n,int start)
        {
            for(int i=start;i<=start+n-1;++i)
                g.insertVertex(std::to_string(i));
        }
        
        Graph<std::string,int> line(int n,int start=1)
        {
            Graph<std::string,int> result;
            add_vertices(result,n,start);
            for(int i=start;i<=start+n-2;++i)
                result.insertEdge(std::to_string(i),std::to_string(i+1),1);

            return result;
        }
        
        Graph<std::string,int> cycle(int n,int start=1)
        {
            Graph<std::string,int> result = line(n,start);
            result.insertEdge(std::to_string(start),std::to_string(start+n-1),1);

            return result;
        }

        Graph<std::string,int> complete(int n,int start=1)
        {
            Graph<std::string,int> result;
            add_vertices(result,n,start);
            for(int i=start;i<=start+n-1;++i)
            for(int j=start;j<=start+n-1;++j)
                if(i!=j)				
                    result.insertEdge(std::to_string(i),std::to_string(j),1);
             
            return result;
        }

        Graph<std::string,int> wheel(int n,int start=1)
        {
            Graph<std::string,int> result = cycle(n-1,start+1);
            result.insertVertex(std::to_string(start));
            for(int i=start+1;i<=start+n-1;++i)
                result.insertEdge(std::to_string(start),std::to_string(i),1);

            return result;
        }
        
        Graph<std::string,int> complete_bipartite(int m,int n,int start=1)
        {
            Graph<std::string,int> result;
            add_vertices(result,m+n,start);
            for(int i=start;i<=start+m-1;++i)
                for(int j=start+m;j<=start+m+n-1;++j)
                    result.insertEdge(std::to_string(i),std::to_string(j),1);

            return result;
        }
        
        Graph<std::string,int> star(int n,int start=1)
        {
            Graph<std::string,int> result;
            add_vertices(result,n+1,start);
            
            for(int i=start+1;i<=start+n;++i)
                result.insertEdge(std::to_string(start),std::to_string(i),1);
            
            return result;
        }

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
        
        Graph<std::string,int> grid(int m,int n,int start=1)
        {
            Graph<std::string,int> result;

            if(m==1 && n==1)
            {
                result.insertVertex(std::to_string(start));
                return result;
            }
            if(m==1)
                return line(n,start);
            if(n==1)
                return line(m,start);

            add_vertices(result,m*n,start);

            for(int i=start;i<=start+m*n-1;i+=n)
                for(int j=i;j<=i+n-2;++j)
                    result.insertEdge(std::to_string(j),std::to_string(j+1),1);
            for(int i=start;i<=start+n-1;++i)
                for(int j=i+n;j<=start+m*n-1;j+=n)
                    result.insertEdge(std::to_string(j-n),std::to_string(j),1);

            return result;
        }

    }
}
#endif
