#ifndef DOT_GRAPH_DECL_HPP
#define DOT_GRAPH_DECL_HPP
#include "Decl.hpp"
#include "StmtListDecl.hpp"
#include "DotExceptions.hpp"
#include <string>
#include <istream>
namespace dot
{
    class GraphDecl : public DotDecl
    {
    public:
        bool isDigraph();
        bool hasID();
        std::string getID();
        bool parse(Stream& in)
        {
            bool keyword = MatchExact("graph").parse(in);
            if(!keyword)
                throw Exception("'graph' keyword expected.\n",in);
            id = MatchIdentifier().parse(in);
            bool openBrace  = MatchExact("{").parse(in);
            statements = new StmtListDecl();
            bool stmtResult =  statements.parse(in);
            bool closeBrace  = MatchExact("{").parse(in);
        }
    private:
        StmtListDecl* statements;
        std::string id;
    };
}
#endif