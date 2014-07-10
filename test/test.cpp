#include "../graph.hpp"
#include "../algorithm/enumeration.hpp"
#include "../algorithm/predicates.hpp"
#include "../algorithm/operations.hpp"
#include "../util/generate.hpp"
#include "../util/io.hpp"
#include<iostream>
int main()
{
    auto g=graph::gen::path(1);
    auto h=graph::gen::cycle(5,2);
    auto g1=graph::join(g,h);
    graph::displayGraph(g1);
    auto w=graph::gen::wheel(6);
    graph::displayGraph(w);
    
    
    /*auto g1=graph::gen::cycle(5);
     *    
     *    auto g=graph::gen::path(5);
     *    
     *    auto h=complement(g1);
     *    
     *    if(isComplement(g,g1))
     *		std::cout<<"1";
     *	else
     *		std::cout<<"0";*/
    
    /* auto x=Union(g1,g);
     *    
     *    if (isComplete(x))
     *		std::cout<<"1";
     *	else
     *		std::cout<<"0";*/
    
    /*if(isEulerian(g1))
     *		std::cout<<"1";
     *	int k=nregular(g1);
     *	if(k!=0)
     *		std::cout<<k;*/
    
    /*auto g2=graph::gen::wheel(6);
     *    auto g=graph::intersection(g1,g2);
     *    graph::displayGraph(g);*/
    //std::cout<<graph::degree(g,g.begin()->first);
    //std::cout<<g.begin()->first;
}
