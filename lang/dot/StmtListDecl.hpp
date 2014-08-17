#ifndef DOT_STMT_LIST_HPP
#define DOT_STMT_LIST_HPP
#include "Decl.hpp"
#include "StmtDecl.hpp"
#include <vector>
namespace dot
{
    class StmtListDecl
    {
    public:
        int size(){return Statements.size();}
    private:        
        std::vector<StmtDecl*> Statements;
    };
}
#endif