
#include "random.hpp"

#include <random>
#include <string>
#include <functional>

namespace chf
{

struct node
{
    std::vector<node> children;
};

void random_class_index(std::mt19937_64& g, uint64_t depth, uint64_t max_depth, uint64_t max_children, node& root)
{
    std::uniform_int_distribution<uint64_t> dis(0, max_children);
    auto child_index = dis(g);
    if (child_index == 0)
        return;

    root.children.resize(child_index);
    if (depth < max_depth)
        random_class_index(g, depth + 1, max_depth, max_children, root.children[child_index - 1]);
}

void random_test(std::ostream& out, uint64_t n, uint64_t max_depth, uint64_t max_children)
{
    std::random_device rd;
    std::mt19937_64 gen(rd());

    node root;

    for (uint64_t i = 0; i < n; ++i)
        random_class_index(gen, 1, max_depth, max_children, root);

    std::function<void(node const&, std::string const&, uint64_t)> print = [&out, &print](node const& nd, std::string const& base, uint64_t depth)
    {
        char dname = char('A' + depth - 1);
        auto prefix = (depth == 1 ? std::string{} : base + '_') + dname;
        for (size_t i = 0; i < nd.children.size(); ++i)
        {
            auto name = prefix + std::to_string(i + 1);
            out << "struct " << name << " : " << base << " {};" << std::endl;
            print(nd.children[i], name, depth + 1);
        }
    };

    out << "struct Root {};" << std::endl;
    print(root, "Root", 1);
}

}