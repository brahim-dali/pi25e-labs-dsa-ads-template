#pragma once
#include <cstddef>
#include <stdexcept>

#include "dsa/DynamicArray.hpp"
#include "dsa/Queue.hpp"


namespace dsa {

class Graph {
public:
    
    Graph(int vertices, bool directed = false)
        : V_(vertices), directed_(directed), adj_() 
    {
        if (vertices <= 0) throw std::invalid_argument("Number of vertices must be positive");
        for (int i = 0; i < V_; ++i)
            adj_.push_back(DynamicArray<int>()); 
    }

 
    int vertex_count() const { return V_; }

  
    void add_edge(int u, int v) {
        validate_vertex(u);
        validate_vertex(v);
        adj_[u].push_back(v);
        if (!directed_) adj_[v].push_back(u);
    }

  
    void bfs(int start, void (*visit)(int)) const {
        validate_vertex(start);
        bool* visited = new bool[V_]();
        Queue<int> q;

        visited[start] = true;
        q.enqueue(start);

        while (!q.empty()) {
            int u = q.front();
            q.dequeue();
            visit(u);

            for (std::size_t i = 0; i < adj_[u].size(); ++i) {
                int v = adj_[u][i];
                if (!visited[v]) {
                    visited[v] = true;
                    q.enqueue(v);
                }
            }
        }

        delete[] visited;
    }

    
    void dfs(int start, void (*visit)(int)) const {
        validate_vertex(start);
        bool* visited = new bool[V_]();
        dfs_rec(start, visited, visit);
        delete[] visited;
    }

  
    void bfs_all(void (*visit)(int)) const {
        bool* visited = new bool[V_]();

        for (int u = 0; u < V_; ++u) {
            if (!visited[u]) {
                Queue<int> q;
                visited[u] = true;
                q.enqueue(u);

                while (!q.empty()) {
                    int curr = q.front();
                    q.dequeue();
                    visit(curr);

                    for (std::size_t i = 0; i < adj_[curr].size(); ++i) {
                        int v = adj_[curr][i];
                        if (!visited[v]) {
                            visited[v] = true;
                            q.enqueue(v);
                        }
                    }
                }
            }
        }

        delete[] visited;
    }

    void dfs_all(void (*visit)(int)) const {
        bool* visited = new bool[V_]();

        for (int u = 0; u < V_; ++u) {
            if (!visited[u])
                dfs_rec(u, visited, visit);
        }

        delete[] visited;
    }

private:
    void validate_vertex(int v) const {
        if (v < 0 || v >= V_)
            throw std::out_of_range("Vertex out of range");
    }

  
    void dfs_rec(int v, bool* visited, void (*visit)(int)) const {
        visited[v] = true;
        visit(v);

        for (std::size_t i = 0; i < adj_[v].size(); ++i) {
            int u = adj_[v][i];
            if (!visited[u])
                dfs_rec(u, visited, visit);
        }
    }

private:
    int V_;
    bool directed_;
    DynamicArray< DynamicArray<int> > adj_;
};

} // namespace dsa
