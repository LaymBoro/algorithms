#include <iostream>
#include <random>
#include <vector>
#include <iomanip>

int min = 0;
int max = 10;

int randomize() 
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int32_t> uni(min, max);

    return uni(rng);
}

unsigned short findMinPath(std::vector<std::vector<unsigned short>>& graph, const size_t& a, const size_t& b) {
    std::vector<std::vector<unsigned short>> shortestPath(graph);

    unsigned short i, j, k;
    unsigned short maxSum = 10000;
    for (i = 0; i < graph.size(); i++)
    {
        for (j = 0; j < graph.size(); j++)
        {
            if (shortestPath[i][j] == 0 && i != j)
            {
                shortestPath[i][j] = maxSum;
            }
        }
    }
    for (k = 0; k < graph.size(); k++)
    {
        for (i = 0; i < graph.size(); i++)
        {
            for (j = 0; j < graph.size(); j++)
            {
                if (shortestPath[i][k] + shortestPath[k][j] < shortestPath[i][j])
                {
                    shortestPath[i][j] = shortestPath[i][k] + shortestPath[k][j];
                }
            }
        }
    }
    return shortestPath[a - 1][b - 1];
}

int main() 
{

    size_t size;
    std::cout << "Input number of points(size)" << "\n";
    std::cin >> size;

    std::vector<std::vector<unsigned short>> graph(size, std::vector<unsigned short>(size));
    for (size_t i = 0; i < graph.size(); i++) 
    {
        for (size_t j = i; j < graph.size(); j++) 
        {
            if (i == j)
            {
                graph[i][j] = 0;
            }
            else 
            {
                graph[i][j] = randomize();
                graph[j][i] = graph[i][j];
            }
        }
    }

    std::cout << "graph" << "\n";
    for (size_t i = 0; i < graph.size(); i++) 
    {
        std::cout << i + 1 << ": ";
        for (size_t j = 0; j < graph.size(); j++) 
        {
            std::cout << std::setw(3) << graph[i][j];
        }
        std::cout << "\n";
    }
    
    size_t a, b;
    std::cout << "Input start & end point" << "\n";
    std::cin >> a >> b;

    std::cout << "Shortest path = " << findMinPath(graph, a, b) << "\n";

    return 0;
}