/*
what could be the issue with the following implementation?
*/

struct Node
{
    int x;
    int y;
    Node* next;
};

void process(Node* head)
{
    for (Node* node=head; node; node = node->next)
    {
        node->y += node->x;
    }
}

/* The issue is that the memory allocated to nodes is scattered and the cache cannot be used. The solution
is to increase the cache locality with contigious memory. */

#include <vector>

std::vector<int> x;
std::vector<int> y;

void process1(vector<int>& x, vector<int>& y)
{
    for (int i=0; i < x.size(); ++i)
    {
        y[i] += x[i];   // increased cache locality
    }
}

