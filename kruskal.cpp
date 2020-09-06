// mst with kruskal's algorithm
#include <iostream>
#include <vector>
#include <utility>
#include <map>

#include <set_lists.h> // for the disjoint sets implemented with linked lists


int main(void) {
    // read the graph as the number of vertices and the out degree
    int order;
    std::cin >> order;
    
    // a graph is a vector of pairs (int:double) of vertex:weight
    std::vector<std::pair<int, double>> *graph = new std::vector<std::pair<int, double>>[order];
    // the map of edges (weight:{u,v}), ordered by increasing weight
    std::multimap<double, std::pair<int, int>> sorted_edges;
    
    // various utility variables
    int i, j;
    int out_deg;
    int dest;
    double weight;
    char c; // just to ignore the ':' in the input stream
    
    // reads the graph 
    for(i = 0; i < order; i++) {
        std::cin >> out_deg;
        for(j = 0; j < out_deg; j++) {
            std::cin >> dest >> c >> weight;
            // insert the pair in the current adjacency list
            graph[i].push_back(std::make_pair(dest, weight));
            // and add the edge to the map
            sorted_edges.insert({weight, std::make_pair(i, dest)});
        }
    }

    // print the graph
    std::cout << "GRAPH\n";
    for(i = 0; i < order; i++) {
        std::cout << i << " => ";
        for(std::pair<int, double> x : graph[i]) {
            std::cout << x.first << " (" << x.second << "), ";
        }
        std::cout << "\n";
    }
    
    /*
     * std::std::cout << "SORTED EDGES\n";
     * for(auto e : sorted_edges) {
     * std::std::cout << e.second.first << " -> " << e.second.second << " [" << e.first << "]\n";
     * }
     */

    // variable to hold the total weight of the mst
    double mst_total = 0.0;

    // the disjont set is an array of sets, dynamically alloc'd
    Set<int> *forest = new Set<int>[order];
    
    // initialize an empty set that represents the mst
    Set<int> A;

    // initialize the vector of sets with single nodes
    for(i = 0; i < order; i++) {
        forest[i].make_set(i);
    }

    // get an iterator for the map of edges
    auto edge = sorted_edges.begin();

    // other useful variables
    Element<int> *x;
    Element<int> *y;
    bool found = false;
    int u, v;           // abbreviations for edges'endpoints
    int set_u, set_v;   // the sets where edge u, v are found respectively
    
    std::cout << "MST of G:\n";
    
    // while there are edges to examine
    while(edge != sorted_edges.end())  {
        u = edge->second.first;
        v = edge->second.second;
        
        // find the set(s) that contain u and v and return their representatives 
        x = nullptr;
        set_u = 0;
        found = false;
        while(!found && set_u < order) {
            x = forest[set_u].find(v);
            if(x != nullptr) {
                found = true;
            }
            else {
                set_u++;
            }
        }
        
        y = nullptr;
        set_v = 0;
        found = false;
        while(!found && set_v < order) {
            y = forest[set_v].find(u);
            if(y != nullptr) {
                found = true;
            }
            else {
                set_v++;
            }
        }
        // then compare the representatives and merge the set iff they are not the same
        if(x != y) {
            std::cout << "A = A U (" << u << ", " << v << ") [" << edge->first << "]\n";
            // update the sum with this edge
            mst_total += edge->first;
            std::cout << "current weight: " << mst_total << "\n";
            // then the edge can be added to A (undirected, thus both u and v are added)
            A.add_element(u);
            A.add_element(v);
            // merge the sets
            merge_sets(forest[set_u], forest[set_v]);
        }
        
        // get the next edge
        ++edge;
    }
    
    // print current sets
    std::cout << "SETS\n";
    int k;
    for(k = 0; k < order; k++) {
        if(!forest[k].empty()) {
            forest[k].print_set();
        }
    }
    
    std::cout << "\nTotal weight: " << mst_total << "\n";
    
    x = nullptr; // x is an Element<int>* 
    // delete the sets
    for(k = 0; k < order; k++) {
        // delete the list
        while(!forest[k].empty()) {
            x = forest[k].get_head();
            forest[k].set_head(forest[k].get_head()->get_next());
            delete x; // delete element*
            forest[k].set_size(forest[k].get_size() - 1); // update size
        }
    }
    // now the disjoint set can be deleted
    delete[] forest;

    return 0;
}
