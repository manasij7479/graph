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
    auto g=graph::gen::hypercube({4},1);
    displayGraph(g);
}
