#include <iostream>
#include <vector>
#include <algorithm>

struct Node{
    float cost;
    std::string path;

    Node(float c): cost(c) {}
};


int main()
{
    std::vector<Node> nodes;

    nodes.push_back(Node(3));
    nodes.push_back(Node(1));
    nodes.push_back(Node(2));

    std::sort(nodes.begin(), nodes.end(), [](const Node& n1, const Node& n2) { return n1.cost < n2.cost;});

    std::cout<<"....."<<"\n";
    for (int i=0; i < nodes.size(); ++i)
    {
        std::cout<<nodes[i].cost<<"\n";
    }

   
}