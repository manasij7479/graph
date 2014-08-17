#ifndef DOT_DECL_HPP
#define DOT_DECL_HPP
#include "Stream.hpp"
#include "StmtListDecl.hpp"
namespace dot
{
    class MatchExactString
    {
    public:
        MatchExactString(std::string str_):str(str_){};
        bool parse(Stream& in)
        {
            bool matched=true;
            in.skipSpace();
            for(int i=0;i<str.length();++i)
                if(str[i]!=in.get())
                {
                    matched=false;
                    break;
                }
            return matched;
        }
    private:
        std::string str;
    };
    
    class MatchIdentifier
    {
    public:
        std::string parse(Stream& in)
        {
            in.skipSpace();
            while(std::isalpha(in.peek()))
                result+=in.get();
        }
    private:
        std::string result;
    };
    
    class MatchStmtList
    {
    public:
        StmtListDecl* parse(Stream& in)
        {
            decl = new StmtListDecl();
        }
    private:
        StmtListDecl* decl;
        
    };
    
}
#endif