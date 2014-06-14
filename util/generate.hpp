#ifndef GRAPH_UTIL_GENERATE_HPP
#define GRAPH_UTIL_GENERATE_HPP
#include<string>
namespace graph
{
    namespace gen
    {
        Graph<std::string,int> cycle(int n)
        {
            Graph<std::string,int> result;
            for(int i=1;i<=n;++i)
                result.insertVertex(std::to_string(i));
            for(int i=0;i<n;++i)
                result.insertEdge(std::to_string(i+1),std::to_string((i+1)%n+1),1);

            return result;
        }
        
        Graph<std::string,int> complete(int n)
		{
			Graph<std::string,int> result;
			for(int i=1;i<=n;++i)
				result.insertVertex(std::to_string(i));
			for(int i=1;i<=n;++i)
				for(int j=1;j<n;++j)
					if(i!=j)
						result.insertEdge(std::to_string(i),std::to_string(j),1);
			
			return result;
		}
		
		Graph<std::string,int> wheel(int n)
		{
			Graph<std::string,int> result = cycle(n-1);
			result.insertVertex(std::to_string(n));
			for(int i=1;i<=n-1;++i)
				result.insertEdge(std::to_string(i),std::to_string(n),1);
			
			return result;
		}
		
		Graph<std::string,int> line(int n)
		{
			Graph<std::string,int> result;
			for(int i=1;i<=n;++i)
				result.insertVertex(std::to_string(i));
			for(int i=1;i<=n-1;++i)
				result.insertEdge(std::to_string(i),std::to_string(i+1),1);
			
			return result;
		}
		
		Graph<std::string,int> complete_bipartite(int m,int n)
		{
			Graph<std::string,int> result;
			for(int i=1;i<=m+n;++i)
				result.insertVertex(std::to_string(i));
			for(int i=1;i<=m;++i)
				for(int j=m+1;j<=m+n;++j)
					result.insertEdge(std::to_string(i),std::to_string(j),1);
			
			return result;
		}
		
		Graph<std::string,int> grid(int m,int n)
		{
			Graph<std::string,int> result;
			
			if(m==1 && n==1)
			{
				result.insertVertex("1");
				return result;
			}
			if(m==1)
				return line(n);
			if(n==1)
				return line(m);
			
			for(int i=1;i<=m*n;++i)
				result.insertVertex(std::to_string(i));
			
			for(int i=1;i<=m*n;i+=n)
				for(int j=i;j<=i+n-2;++j)
					result.insertEdge(std::to_string(j),std::to_string(j+1),1);
			for(int i=1;i<=n;++i)
				for(int j=i+n;j<=m*n;j+=n)
					result.insertEdge(std::to_string(j-n),std::to_string(j),1);
			
			return result;
		}
		
    }
}
#endif