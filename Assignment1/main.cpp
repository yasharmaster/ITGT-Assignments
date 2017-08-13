#include <iostream>
#include <vector>
using namespace std;

typedef vector<pair<int, int> > VectorPairInt;
typedef pair<int, int> PairInt;

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
		
		cout << "Enter ending vertex\t";
		cin >> end;
		
		edges.push_back(make_pair(start, end));
	}
	
	VectorRep vectorRep(n, e, edges);
	vectorRep.print();
	
	IncidenceMatrix incidenceMatrix(vectorRep);
	incidenceMatrix.print();
	

	return 0;
}