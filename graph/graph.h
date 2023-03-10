#ifndef _graph
#define _graph

#include <map>
#include <vector>

template <typename DT>
class Node {
    public:
        DT data;
        int id;
};

template <typename DT>
class Edge {
    public:
        DT weight;
        int idFrom, idTo;
};

template <typename DT>
class Graph {
    private:
        int _size;
    public:
        std :: vector <Node <DT> > vertexes;
        std :: vector <std :: vector <Edge <DT> > > edges;
        Graph () {

        }
        ~ Graph () {
            vertexes.clear ();
        }
        void addEdge (int u, int v, int w);
};

#endif