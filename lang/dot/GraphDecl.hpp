#ifndef DOT_GRAPH_DECL_HPP
#define DOT_GRAPH_DECL_HPP
#include "Decl.hpp"
#include "StmtListDecl.hpp"
#include "DotExceptions.hpp"
#include <string>
#include <istream>
namespace dot
{
    class GraphDecl
    {
    public:
        bool isDigraph();
        bool hasID();
        std::string getID();
        
        bool parse(Stream& in)
        {
            bool keyword = MatchExactString("graph").parse(in);
            
            if (!keyword)
                throw Exception("'graph' keyword expected.\n",in);
            
            id = MatchIdentifier().parse(in);
            
            if (id=="")
                throw Exception("Identifier expected\n",in);
            
            bool openBrace  = MatchExactString("{").parse(in);
            
            if (!openBrace)
                throw Exception("{ expected\n",in);
            
            statements = MatchStmtList().parse(in);
            
            bool closeBrace  = MatchExactString("}").parse(in);
            if (!closeBrace)
                throw Exception("} expected\n",in);
            return true;
        }
    private:
        StmtListDecl* statements;
        std::string id;
    };
}
#endif