#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "matrix.h"
#include <vector>

namespace dijkstra {
	using Vertex = types::Ordered_pair<int>;

	class Dijkstra {
	private:
		matrix::Matrix<int> *graph; // Interpret the input matrix as a cost graph, as follows: (i, j) is the cost to reach the vertex (i, j) from its neighbours
		int dim;
		Vertex source;

		matrix::Matrix<Vertex> *predecessors;
		matrix::Matrix<int> *shortest_path_estimate;
		matrix::Matrix<bool> *extracted; // Boolean matrix which flanks shortest_path_estimate to track if the element has been extracted

		void initialize_single_source();
		Vertex extract_min();
		std::vector<Vertex> get_adjacency_list(Vertex v);
		void relax(Vertex u, Vertex v);
	public:
		Dijkstra(matrix::Matrix<int> *graph, int dim, Vertex source);
		virtual ~Dijkstra();
		void run();
		void print_path(Vertex source, Vertex destination);
	};
} // namespace dijkstra

#endif // DIJKSTRA_H
