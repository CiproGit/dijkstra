#include "dijkstra.h"
#include <limits>

using namespace std;

namespace dijkstra {
	Dijkstra::Dijkstra(matrix::Matrix<int> *graph, int dim, Vertex source) {
		this->graph = graph;
		this->dim = dim;
		this->source = source;

		this->predecessors = new matrix::Matrix<Vertex>(this->dim, this->dim);
		this->shortest_path_estimate = new matrix::Matrix<int>(this->dim, this->dim);
		this->extracted = new matrix::Matrix<bool>(this->dim, this->dim);

		initialize_single_source();
	}

	Dijkstra::~Dijkstra() {
		delete this->predecessors;
		delete this->shortest_path_estimate;
		delete this->extracted;
	}

	void Dijkstra::initialize_single_source() {
		Vertex v;
		v.x = -1;
		v.y = -1;
		this->predecessors->set_all_elements(v);

		this->shortest_path_estimate->set_all_elements(numeric_limits<int>::max());
		this->shortest_path_estimate->set_element(this->source, 0);

		this->extracted->set_all_elements(false);
	}

	Vertex Dijkstra::extract_min() {
		Vertex min;
		int min_value = numeric_limits<int>::max();

		for (int i = 0; i < this->dim; i++) {
			for (int j = 0; j < this->dim; j++) {
				Vertex v;
				v.x = i;
				v.y = j;

				if (!(this->extracted->get_element(v))) { // If it hasn't already been extracted
					if (this->shortest_path_estimate->get_element(v) < min_value) {
						min_value = this->shortest_path_estimate->get_element(v);
						min.x = v.x;
						min.y = v.y;
					}
				}
			}
		}

		this->extracted->set_element(min, true);
		return min;
	}

	vector<Vertex> Dijkstra::get_adjacency_list(Vertex v) { // It only moves right, left, up, down
		vector<Vertex> adjacency_list;
		Vertex left, right, up, down;

		left.x = v.x;
		left.y = v.y - 1;
		if (left.y >= 0) adjacency_list.push_back(left);

		right.x = v.x;
		right.y = v.y + 1;
		if (right.y < this->dim) adjacency_list.push_back(right);

		up.x = v.x - 1;
		up.y = v.y;
		if (up.x >= 0) adjacency_list.push_back(up);

		down.x = v.x + 1;
		down.y = v.y;
		if (down.x < this->dim) adjacency_list.push_back(down);

		return adjacency_list;
	}

	void Dijkstra::relax(Vertex u, Vertex v) {
		if (this->shortest_path_estimate->get_element(v) > this->shortest_path_estimate->get_element(u) + this->graph->get_element(v)) {
			this->shortest_path_estimate->set_element(v, this->shortest_path_estimate->get_element(u) + this->graph->get_element(v)); // Update the estimate
			this->predecessors->set_element(v, u); // The predecessor of v becomes u
		}
	}

	void Dijkstra::run() {
		// For the number of vertices of the graph, repeat:
		for (int k = 0; k < this->dim * this->dim; k++) {
			cout << "Iteration " << k << ":\n";

			Vertex u = extract_min();
			cout << '(' << u.x << ", " << u.y << ")\n";

			vector<Vertex> adj = get_adjacency_list(u);
			cout << "Adjacency: ";
			for (Vertex v : adj) {
				cout << '(' << v.x << ", " << v.y << ')' << " - ";
				relax(u, v);
			}
			cout << '\n' << endl;
		}
	}

	void Dijkstra::print_path(Vertex source, Vertex destination) {
		Vertex pred = this->predecessors->get_element(destination);

		if (source.x == destination.x && source.y == destination.y) {}
		else if (pred.x == -1 || pred.y == -1) cout << "There are no paths" << endl;
		else print_path(source, pred);

		cout << '(' << destination.x << ", " << destination.y << ')' << endl;
	}
} // namespace dijkstra
