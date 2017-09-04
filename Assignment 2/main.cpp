#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#define NOT_IN_STACK 0
#define IN_STACK 1
#define MAXN 500

set<vector<int> > myset;

void print(vector<int> v) {
    for (int i=0; i<v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void print_set(set<vector<int> > &myset){
	set<vector<int> >::iterator itr;
	for (itr=myset.begin(); itr != myset.end(); itr++) {
		vector<int> v = *itr;
		print(v);
	}
}

bool dfs(int v, vector<vector<bool> > &adj, int label[MAXN], int instack_count, int n, vector<int> &myvec){
	int top = myvec[myvec.size()-1], bottom = myvec[0];
        if(instack_count == n && myvec.size()==n && adj[top][bottom] ){
		myset.insert(myvec);
            return true;
        }
        for(int i=0; i<n; i++)
            if(adj[v][i] && label[i] == NOT_IN_STACK){
                label[i]=IN_STACK;
                myvec.push_back(i);
                if(dfs(i, adj, label, instack_count+1, n, myvec)){
                    // return true;
                }
                label[i]=NOT_IN_STACK;
                myvec.pop_back();
            }
        return false;
}

bool check_using_dfs(vector<vector<bool> > &adj, int n){
	myset.clear();
        int label[MAXN];
        for(int i=0; i<n; i++)
            label[i]=NOT_IN_STACK;
        vector<int> myvec;

        for(int i=0; i<n; i++){
            label[i]=IN_STACK;
            myvec.push_back(i);
            if(dfs(i, adj, label, 1, n, myvec)){
                myset.insert(myvec);
                // return true;
            }
            label[i]=NOT_IN_STACK;
            myvec.pop_back();

        }
        if (myset.empty()) {
            // cout << "There is no hamiltonian circuit in the graph.\n";
            return false;
        } else {
		// print_set(myset);
            return true;
        }
}

bool check_all_permutations(vector<vector<bool> > &adj, int n){
        vector<int>v;
        for(int i=0; i<n; i++)
            v.push_back(i);
        bool hamil_gph = false;
        do{
            bool valid=true;
            for(int i=0; i<v.size()-1; i++){
                if(adj[v[i]][v[i+1]] == false){
                    valid=false;
                    break;
                }     
            }
            if(valid) {
                hamil_gph = true;
                for(int i : v) {
                    // cout << i << " ";
                }
                // cout << "\n";
            }
        } while(next_permutation(v.begin(), v.end()));
         if(!hamil_gph){
            // cout << "There is no hamiltonian circuit in the graph.\n";

         }
}

int main() {
    int n;
    // freopen("output_naive.txt", "w+", stdout);
    // freopen("test_case.txt", "r", stdin);

    // for(int t=4; t <= 11; t++) {
    //     cin >> n;
    //     vector<vector<bool> > adj(n);   
    //     for(int i=0; i<n; i++) {
    //         for(int j=0; j<n; j++) {
    //             int temp;
    //             cin >> temp;
    //             adj[i].push_back(temp);
    //         }
    //     }
    //     double tt=0;
    //     for(int j=1; j<=10; j++) {
    //         high_resolution_clock::time_point t1 = high_resolution_clock::now();
    //         check_all_permutations(adj, n);
    //         high_resolution_clock::time_point t2 = high_resolution_clock::now();
    //         auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    //         tt += duration/10;
    //     }
    //     cout << n <<  " " << int(tt) << "\n";
    //     //cout << "\n";
    // }

    freopen("output_backtracking.txt", "w+", stdout);
    freopen("test_case.txt", "r", stdin);

    for(int t=4; t <= 15; t++) {
        cin >> n;
        vector<vector<bool> > adj(n);   
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                int temp;
                cin >> temp;
                adj[i].push_back(temp);
            }
        }
        double tt=0;
        for(int j=1; j<=10; j++) {
            high_resolution_clock::time_point t1 = high_resolution_clock::now();
            check_using_dfs(adj, n);
            high_resolution_clock::time_point t2 = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>( t2 - t1 ).count();
            tt += duration/10;
        }
        cout << n <<  " " << int(tt) << "\n";
        //cout << "\n";
    }
    
    return 0;
}
