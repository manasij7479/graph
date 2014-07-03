#include "../graph.hpp"
#include "../algorithm/enumeration.hpp"
#include "../algorithm/predicates.hpp"
#include "../algorithm/operations.hpp"
#include "../util/generate.hpp"
#include<iostream>
int main()
{
    auto g1=graph::gen::cycle(5);
    if (isComplete(g1))
		std::cout<<"1";
	else
		std::cout<<"2";
    /*if(isEulerian(g1))
		std::cout<<"1";
	int k=nregular(g1);
	if(k!=0)
		std::cout<<k;*/
	
    /*auto g2=graph::gen::wheel(6);
    auto g=graph::intersection(g1,g2);
    graph::displayGraph(g);*/
    //std::cout<<graph::degree(g,g.begin()->first);
    //std::cout<<g.begin()->first;
}
