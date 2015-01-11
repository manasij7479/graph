//expected output 102010
#include "../graph.hpp"
#include "../algorithm/collections.hpp"
#include "../util/generate.hpp"
#include<iostream>
int main()
{
    auto g1=graph::gen::cycle({10});
    //auto g4=graph::gen::cycle(3,11);
    //auto g5=graph::Union(g1,g4);
    
    auto v=graph::VertexList(g1);
    auto etrue=graph::EdgeList(g1);
    auto efalse=graph::EdgeList(g1,false);
    std::cout<<v.size()<<etrue.size()<<efalse.size();
}
