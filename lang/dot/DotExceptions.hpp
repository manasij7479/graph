#ifndef DOT_EXCEPTIONS_HPP
#define DOT_EXCEPTIONS_HPP
namespace dot
{
    class Exception 
    {
    public:
        Exception(std::string msg_,Stream& in_):msg(msg_),in(in_)
        {
            pos  = in.pos();
        }
        std::string what() const
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