#ifndef DOT_STMT_DECL
#define DOT_STMT_DECL
#include "Decl.hpp"
#include <string>
namespace dot
{
    class StmtDecl 
    {
        
    };
    class NodeStmtDecl : public StmtDecl
    {
    public:
        std::string getName(){return name;} 
    private:
        std::string name;
    };
    
    class EdgeStmtRHS;
    class EdgeOp;
    class EdgeStmtDecl : public StmtDecl
    {
    public:
    private:
        NodeStmtDecl * node;
        EdgeStmtRHS* rhs;
    };
    class EdgeStmtRHS
    {
    public:
    private:
        EdgeOp* op;
        NodeStmtDecl* node;
        EdgeStmtRHS* rhs; // optional
    };
    class EdgeOp
    {
        
    };
}
#endif