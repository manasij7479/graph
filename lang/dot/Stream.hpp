#ifndef DOT_STREAM_HPP
#define DOT_STREAM_HPP
#include <vector>
#include <map>
#include <istream>
namespace dot
{
    class Stream
    {
    public:
        Stream(std::istream& in);
        int pos(){return position;}
        char get()
        {
            if(position>=data.size())
                return 0;
            return data[position--];
        }
        int remember()
        {
            int result = bookmarks.size();
            bookmarks[result]=position;
            return result;
        }
        void reset(int p)
        {
            position = bookmarks[p];
        }
    private:
        std::vector<char> data;
        int position;
        std::map<int,int> bookmarks;
        
    };
}
#endif