#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef vector<pair<int, int> > VectorPairInt;
typedef pair<int, int> PairInt;

/*
	Vector Representation of a Graph.
	Each entry in the "edges" vector stores a pair of integers such that the first integer is starting
	and second is ending vertex of that edge.
*/
class VectorRep {
public:
	int n, e;
	VectorPairInt edges;
	
	VectorRep(int numberOfVertices, int numberOfEdges, VectorPairInt edgesVector) {
		n = numberOfVertices;
		e = numberOfEdges;
		edges = edgesVector;
	}
	
	void print() {
		cout << "Printing Vector Representation\n";
		VectorPairInt::iterator itr = edges.begin();
		
		for (; itr != edges.end(); itr++) {
			cout << (*itr).first << "\t" << (*itr).second << endl;
		}
	}
};

/*
	Incidence Matrix Representation of a Graph.
	0 denotes No Edge
	1 denotes Starting Vertex
	2 denotes Ending Vertex
	3 denotes Startint and Ending Vertex (Self Loop)
*/
class IncidenceMatrix {
public:
	int n, e;
	int **matrix;
	
	IncidenceMatrix(VectorRep graph) {
		n = graph.n;
		e = graph.e;
		
		matrix = new int*[n];
		for (int i=0; i<n; i++) {
			matrix[i] = new int[e];
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < e; j++) {
				matrix[i][j] = 0;
			}
		}
		
		VectorPairInt edges = graph.edges;
		VectorPairInt::iterator itr = edges.begin();
		
		for (int i = 0; i < e; i++) {
			int start = (*itr).first, end = (*itr).second;
			if (start != end) {
				matrix[start][i] = 1;
				matrix[end][i] = 2;
			}
			else {
				matrix[start][i] = 3;
			}
			itr++;
		}
	}

	IncidenceMatrix(int n, int e, int **matrix) {
		this->n = n;
		this->e = e;
		this->matrix = matrix;
	}
	
	VectorRep toVectorRep() {
		VectorPairInt edges;

		for (int i = 0; i < e; i++) {
			int start, end, self = -1;

			for (int j=0; j<n; j++) {
				if (matrix[j][i] == 1) {
					start = j;
				}
				else if (matrix[j][i] == 2) {
					end = j;
				}
				else if (matrix[j][i] == 3) {
					self = j;
					break;
				}
			}

			if (self != -1) {
				edges.push_back(make_pair(self, self));
			}
			else {
				edges.push_back(make_pair(start, end));
			}
		}

		VectorRep graph(n, e, edges);
		return graph;
	}

	void print() {
		cout << "Printing Incidence Matrix\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < e; j++) {
				cout << matrix[i][j] << "\t";
			}
			cout << endl;
		}
	}
};

/*
	Incidence Matrix (2) Representation of a Graph.
	edge[i][j] = k;
	denotes that edge j starts from i and ends at k
	edge[i] = -1
	denotes that in edge j, vertex i does not participate
*/
class IncidenceMatrixTwo {
public:
	int n, e;
	int **matrix;
	
	IncidenceMatrixTwo(VectorRep graph) {
		n = graph.n;
		e = graph.e;
		
		matrix = new int*[n];
		for (int i=0; i<n; i++) {
			matrix[i] = new int[e];
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < e; j++) {
				matrix[i][j] = -1;
			}
		}
		
		VectorPairInt edges = graph.edges;
		VectorPairInt::iterator itr = edges.begin();
		
		for (int i = 0; i < e; i++) {
			int start = (*itr).first, end = (*itr).second;
			matrix[start][i] = end;
			itr++;
		}
	}

	VectorRep toVectorRep() {
		VectorPairInt edges;

		for (int i = 0; i < e; i++) {
			int start, end, self = -1;

			for (int j=0; j<n; j++) {
				if (matrix[j][i] != -1) {
					edges.push_back(make_pair(j, matrix[j][i]));
					break;
				}
			}

		}
		VectorRep graph(n, e, edges);
		return graph;
	}
	
	void print() {
		cout << "Printing Incidence Matrix(2)\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < e; j++) {
				cout << matrix[i][j] << "\t";
			}
			cout << endl;
		}
	}
};

/*
	Condensed Incidence Matrix Representation of the Graph
	Each element of the array "edges" is an integer which is decimal representation
	of same row of Incidence Matrix considering Base 4 form.
*/
class CondensedIncidenceMatrix {
public:
	int n, e;
	int *edges;

	CondensedIncidenceMatrix(VectorRep graph) {
		n = graph.n;
		e = graph.e;

		IncidenceMatrix incidenceMatrix(graph);

		int **matrix = incidenceMatrix.matrix;
		edges = new int[n];
		for (int i=0; i<n; i++) {
			edges[i] = 0;
			for (int j=0; j<e; j++) {
				edges[i] += matrix[i][j]*pow(4, j);
			}
		}
	}

	VectorRep toVectorRep() {
		int **matrix = new int*[n];
		for (int i=0; i<n; i++) {
			matrix[i] = new int[e];
		}

		for (int i=0; i<n; i++) {
			int x = edges[i];
			for (int j=0; j<e; j++) {
				matrix[i][j] = x%4;
				x /= 4;
			}
		}

		IncidenceMatrix incidenceMatrix(n, e, matrix);
		return incidenceMatrix.toVectorRep();
	}

	void print() {
		cout << "Printing Condensed Incidence Matrix" << endl;
		for (int i=0; i<n; i++) {
			cout << edges[i] << endl;
		}
	}
};

int main() {
	
	int n; // number of vertices
	cout << "Enter the number of vertices\t";
	cin >> n;
	
	int e; // number of edges
	cout << "Enter the number of edges\t";
	cin >> e;
	
	cout << "Numbering of vertices starts from " << 0 << " to " << n-1 << endl;
	
	VectorPairInt edges;
	int start, end;
	for (int i=0; i<e; i++) {
		cout << "For edge " << i+1 << ":" << endl;
		
		cout << "Enter starting vertex\t";
		cin >> start;
		while (start >= n && start < 0) {
			cout << "Invalid vertex number entered. Please try again.\n";
			cout << "Enter starting vertex\t"; 
			cin >> start;
		}
		
		cout << "Enter ending vertex\t";
		cin >> end;
		while (end >= n && end < 0) {
			cout << "Invalid vertex number entered. Please try again.\n";
			cout << "Enter ending vertex\t";
			cin >> end;
		}

		edges.push_back(make_pair(start, end));
	}
	
	VectorRep vectorRep(n, e, edges);
	vectorRep.print();
	cout << endl;
	
	IncidenceMatrix incidenceMatrix(vectorRep);
	incidenceMatrix.print();
	cout << endl;
	
	VectorRep graph = incidenceMatrix.toVectorRep();
	graph.print();
	cout << endl;

	IncidenceMatrixTwo incidenceMatrix2(vectorRep);
	incidenceMatrix2.print();
	cout << endl;

	VectorRep graph1 = incidenceMatrix2.toVectorRep();
	graph1.print();
	cout << endl;

	CondensedIncidenceMatrix condensed(vectorRep);
	condensed.print();
	cout << endl;

	VectorRep graph2 = condensed.toVectorRep();
	graph2.print();


	return 0;
}