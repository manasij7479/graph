#ifndef GRAPH_LAYOUT_LAYOUT_HPP
#define GRAPH_LAYOUT_LAYOUT_HPP
#include <vector>
namespace graph
{
    struct Point//Placeholders until geometry library is ready
    {
        float x,y;
    };
    typedef std::vector<Point> Curve;
    
    template<typename Graph>
    class Layout
    {
    public:
        typedef typename Graph::VertexType VertexType;
        virtual Point Vertex(VertexType v){return {0.0f,0.0f};};
        virtual Curve Edge(VertexType x, VertexType y) { return {};} 
        virtual void import(Layout& l){};
    };
}
#endif