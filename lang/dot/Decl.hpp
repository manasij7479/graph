#ifndef DOT_DECL_HPP
#define DOT_DECL_HPP
#include "Stream.hpp"
namespace dot
{
    class DotDecl
    {
        //TODO
        //Not sure what the basic interface will be
        //Decide tomorrow
        
    };
    
    class MatchExact
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
            //TODO: Continue from here
        }
    private:
        std::string result;
    };
}
#endif