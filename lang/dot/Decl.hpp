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
    public:
        bool parse(Stream& in);
    };
}
#endif