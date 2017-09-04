#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("test_case3.txt", "w+", stdout);
	srand(time(0));
	for(int i = 4; i <= 15; i+=1) {
		int n=i, adj[n][n];
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				adj[i][j] = 0;
			}			
		}
		cout << n << "\n";
		int edges = n*(n-1) / 2;
		float e_percent = 0.2 + (float) (rand()) / (float) (RAND_MAX/(0.8-0.2));
		edges *= e_percent;
		//cout << "edges = " << edges << "\n"; 
		while(edges--) {
			int i = rand() % n, j;
			do {
				j = rand() % n;
			} while(j == i || adj[i][j] == 1);
			adj[i][j]=1;
			adj[j][i]=1;
		}
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				cout << adj[i][j] << " ";
			}
			cout << "\n";			
		}
	} 
	return 0;
}