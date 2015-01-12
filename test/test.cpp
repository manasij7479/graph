#include "../graph.hpp"
#include "../algorithm/sssp.hpp"
#include "../algorithm/predicates.hpp"
#include "../algorithm/enumeration.hpp"
#include "../algorithm/operations.hpp"
#include "../algorithm/collections.hpp"
#include "../algorithm/search.hpp"
#include "../util/generate.hpp"
#include "../util/visitors.hpp"
#include "../util/io.hpp"
#include "../structures/attribute.hpp"
#include "../algorithm/coloring.hpp"
#include <iostream>
#include <functional>
int main()
{
    auto g=graph::gen::path({12});
    graph::displayGraph(g);
    graph::BreadthFirstSearch<decltype(g)> search(g, "1");
    search();
    for (auto v : graph::VertexList(g))
    {
//             std::cout << v <<'\t' << search.getParentArray()[v]<<std::endl;
        auto path = search.getParentArray().getPath(v);
        for(auto x : path)
            std::cout << x <<' ';
        std::cout<<std::endl;
    }
}
