#ifndef GRAPH_STRUCTURE_PARENT
#define GRAPH_STRUCTURE_PARENT
#include <map>
#include <vector>
#include <algorithm>
namespace graph
{
    template<typename Graph>
    class ParentArray
    {
    public:
        typedef typename Graph::VertexType V;
        
        //FInal Interface yet to be designed
        //Use compatibility interface in the meantime
        //(mirrors std::map)
        
        std::vector<V> getPath(V v)
        {
            std::vector<V> result;
            V temp=v;
            while(map[temp]!=temp)
            {
                result.push_back(temp);
                temp=map[temp];
            }
            result.push_back(temp);
            std::reverse(result.begin(),result.end());
            return result;
        }
    private:
        std::map<V,V> map;
    public:
        //compatibility interface
        typedef typename decltype(map)::iterator iterator;
        iterator begin(){return map.begin();}
        iterator end(){return map.end();}
        iterator find(V v){return map.find(v);}

        V& operator[](V v) // do NOT call if may be unknown
        {
            return map[v];            
        }
        
        
    };
}
#endif