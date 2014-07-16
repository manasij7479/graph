#ifndef DOT_STMT_DECL
#define DOT_STMT_DECL
#include "Decl.hpp"
#include <string>
namespace dot
{
    class StmtDecl : public DotDecl
    {
        
    };
    class NodeStmtDecl : public StmtDecl
    {
    public:
        std::string getName(){return name;} 
    private:
        std::string name;
    };
    class EdgeStmtDecl : public StmtDecl
    {
    public:
    private:
        NodeStmtDecl * node;
        EdgeStmtRHS* rhs;
    };
    class EdgeStmtRHS: public DotDecl
    {
    public:
    private:
        EdgeOp* op;
        NodeStmtDecl* node;
        EdgeStmtRHS* rhs; // optional
    };
}
#endif