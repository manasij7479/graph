#ifndef DOT_STMT_LIST_HPP
#define DOT_STMT_LIST_HPP
#include "Decl.hpp"
#include <vector>
namespace dot
{
    class StmtListDecl : public DotDecl
    {
    public:
        int size(){return Statements.size();}
    private:        
        std::vector<StmtDecl*> Statements;
    };
}
#endif