// Stack operations
// Push, Pop, Top, and Empy

#include <vector>
#include <iostream>
#include <stack>


template <class T>
struct GraphNode
{
    bool visited;
    std::vector<GraphNode> neighbors;
    T value;
};


template <class T>
void dfs(std::stack< GraphNode<T> > s)
{
    GraphNode<int> top;
    while (s.empty() == false)
    {
        top = s.top();
        s.pop();
        top.visited = true;
        std::cout << top.value << std::endl;
    }



}


int main()

{
    std::stack< GraphNode<int> > s;
    for (int i = 0; i < 10; ++i)
    {
        GraphNode<int> *n = new GraphNode<int>;
        n->visited = false;
        n->value = i;
        s.push(*n);
    }

    dfs(s);

    return 0;
}
