#ifndef DOT_GRAPH_DECL_HPP
#define DOT_GRAPH_DECL_HPP
#include "Decl.hpp"
#include "StmtListDecl.hpp"
#include <string>
#include <istream>
namespace dot
{
    class GraphDecl : public DotDecl
    {
    public:
        GraphDecl(std::ifstream& in);
        bool isDigraph();
        bool hasID();
        std::string getID();
        bool parse(Stream& in);
    private:
        StmtListDecl* statements;
    };
}
#endif