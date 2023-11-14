#include <iostream>
#include <queue>


struct Node{
    float cost;
    std::string path;

    Node(float c): cost(c) {}
};

class Compare{
    public:
    bool operator()(const Node& n1, const Node& n2){return n1.cost > n2.cost;}

};

int main()
{
    std::priority_queue<int> maxHeap;
    std::priority_queue< int, std::vector<int>, std::greater<int> > minHeap;
    std::priority_queue<Node, std::vector<Node>, Compare> minHeap1;


    maxHeap.push(3);
    maxHeap.push(5);
    maxHeap.push(10);
    maxHeap.push(1);

    minHeap.push(3);
    minHeap.push(5);
    minHeap.push(10);
    minHeap.push(1);

    minHeap1.push(Node(3.5));
    minHeap1.push(Node(1.5));
    minHeap1.push(Node(2.5));

    while (!maxHeap.empty())
    {
        auto tmp = maxHeap.top();
        std::cout<<tmp<<"\n";
        maxHeap.pop();
    }

    while (!minHeap.empty())
    {
        auto tmp = minHeap.top();
        std::cout<<tmp<<"\n";
        minHeap.pop();
    }

    while(!minHeap1.empty())
    {
        auto tmp = minHeap1.top();
        std::cout<<tmp.cost<<"\n";
        minHeap1.pop();
    }
}