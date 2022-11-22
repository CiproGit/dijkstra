#include "dijkstra.h"

using namespace std;

int main(void) {
	cout << "**********************\n";
	cout << "*      DIJKSTRA      *\n";
	cout << "**********************\n" << endl;

	const int N = 5;

	matrix::Matrix<int> graph = matrix::Matrix<int>(N, N);

	int row_0[N] = {0, 1, 1, 0, 1};
	int row_1[N] = {0, 1, 0, 0, 0};
	int row_2[N] = {0, 0, 0, 1, 0};
	int row_3[N] = {1, 0, 1, 1, 0};
	int row_4[N] = {1, 0, 0, 1, 0};

	graph.set_row(0, row_0);
	graph.set_row(1, row_1);
	graph.set_row(2, row_2);
	graph.set_row(3, row_3);
	graph.set_row(4, row_4);

	cout << "Graph:" << endl;
	graph.print();

	dijkstra::Vertex source;
	source.x = 0;
	source.y = 0;

	cout << "Source:\n";
	cout << '(' << source.x << ", " << source.y << ")\n" << endl;

	dijkstra::Vertex destination;
	destination.x = 4;
	destination.y = 4;

	cout << "Destination:\n";
	cout << '(' << destination.x << ", " << destination.y << ")\n" << endl;

	dijkstra::Dijkstra dijkstra(&graph, N, source);
	dijkstra.run();

	cout << "Path:" << endl;
	dijkstra.print_path(source, destination);

	cout << "\nEnd" << endl;
	return EXIT_SUCCESS;
}
