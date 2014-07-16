#ifndef DOT_EXCEPTIONS_HPP
#define DOT_EXCEPTIONS_HPP
#include <exception>
namespace dot
{
    class Exception : public std::excpetion
    {
    public:
        Exception(std::string msg_,Stream& in):msg(msg_),in(in_)
        {
            pos  = in.pos();
        }
        std::string what()
        {
            return msg;
            //would support more elaborate diagnostics later
        }
    private:
        Stream& in;
        int pos;
        std::string msg;
    };
}
#endif