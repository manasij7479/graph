// #include "../graph.hpp"
// #include "../algorithm/enumeration.hpp"
// #include "../algorithm/predicates.hpp"
// #include "../algorithm/operations.hpp"
// #include "../util/generate.hpp"
// #include "../util/io.hpp"
// #include<iostream>
// int main()
// {
// //     auto g=graph::gen::path(2);
// //     auto h=graph::gen::cycle(5,3);
// //     auto g1=graph::cartesian_product(g,h);
// //     //auto w=graph::gen::wheel(6);
// //     std::cout<<g1.order()<<std::endl;
// //     int count=0;
// //     for(auto i=g1.begin();i!=g1.end();++i)
// //         for(auto j=g1.nbegin(i->first);j!=g1.nend(i->first);++j)
// //             count++;
// //     std::cout<<count<<std::endl;
// //     graph::displayGraph(g1);
// //     graph::Graph<std::string,int> g,h;
// //     g.insertVertex("1");
// //     g.insertVertex("2");
// //     g.insertVertex("3");
// //     g.insertVertex("4");
// //     g.insertEdge("4","1",1);
// //     g.insertEdge("4","2",1);
// //     g.insertEdge("4","3",1);
// //     g.insertEdge("1","2",1);
// //     g.insertEdge("1","3",1);
// //     g.insertEdge("2","3",1);
// //     
// //     h.insertVertex("1");
// //     h.insertVertex("3");
// //     h.insertVertex("5");
// //     h.insertVertex("7");
// //     h.insertVertex("9");
// //     h.insertEdge("9","1",1);
// //     h.insertEdge("9","3",1);
// //     h.insertEdge("9","5",1);
// //     h.insertEdge("9","7",1);
// //     h.insertEdge("1","3",1);
// //     h.insertEdge("1","7",1);
// //     h.insertEdge("5","7",1);
// //     h.insertEdge("5","3",1);
//     
//     //auto sd=graph::symmetric_difference(g,h);
//     //graph::displayGraph(sd);
//     
//     
//     /*auto g1=graph::gen::cycle(5);
//      *    
//      *    auto g=graph::gen::path(5);
//      *    
//      *    auto h=complement(g1);
//      *    
//      *    if(isComplement(g,g1))
//      *		std::cout<<"1";
//      *	else
//      *		std::cout<<"0";*/
//     
//     /* auto x=Union(g1,g);
//      *    
//      *    if (isComplete(x))
//      *		std::cout<<"1";
//      *	else
//      *		std::cout<<"0";*/
//     
//     /*if(isEulerian(g1))
//      *		std::cout<<"1";
//      *	int k=nregular(g1);
//      *	if(k!=0)
//      *		std::cout<<k;*/
//     
//     /*auto g2=graph::gen::wheel(6);
//      *    auto g=graph::intersection(g1,g2);
//      *    graph::displayGraph(g);*/
//     //std::cout<<graph::degree(g,g.begin()->first);
//     //std::cout<<g.begin()->first;
//     
//     
// }
// 

        

    #include "../graph.hpp"
    #include "../search/bfs.hpp"
    #include "../util/generate.hpp"
    int main()
    {
        auto g=graph::gen::path(2);
        graph::BreadthFirstSearch<decltype(g)> b(g,g.begin()->first);
    }

