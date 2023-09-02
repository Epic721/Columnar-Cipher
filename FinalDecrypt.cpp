//
//  main.cpp
//  ColumnarCipherDecoder
//
//  Created by Adrish Kar
//
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
#define MAXN 105
#define PRINT(x) cout << x << " ";
#define PRINTLN(x) cout << x << endl;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

double scores[26][26] = {
	-8, 1,  2,  1,  -8, -1, 0,  -7, -1, -2, 2,  2,  1,  3,  -8, 1,  -1, 1,  2,
	1,  -3, 3,  -1, -2, 1,  2,  0,  -2, -8, -8, 3,  -8, -8, -8, -1, 3,  -8, 3,
	-6, -8, 1,  -8, -8, 1,  -4, -7, 5,  -8, -8, -8, 4,  -8, 1,  -8, -1, -8, 1,
	-8, -8, 3,  -1, -8, 6,  0,  -8, -8, 3,  -8, 3,  0,  -8, -1, 0,  -8, -8, -8,
	-4, -2, 1,  3,  0,  -2, 0,  0,  -1, -1, 1,  3,  -3, -1, 0,  -2, 0,  -1, 0,
	-2, 0,  1,  -1, -2, 1,  -8, 0,  -8, 0,  1,  1,  2,  -3, 0,  -2, -3, -2, 0,
	-2, 0,  1,  1,  -3, 1,  2,  3,  1,  -1, -5, 2,  1,  5,  0,  -1, 1,  -1, -2,
	-5, -1, 2,  -4, -2, 1,  1,  -7, 0,  0,  -8, 2,  -1, -3, 1,  -3, 2,  1,  -4,
	-1, -8, -2, -6, 1,  0,  -3, -5, 0,  -1, 0,  3,  1,  1,  -7, 0,  -2, -4, 1,
	-3, -3, 0,  -1, -1, 1,  -4, 0,  -8, -4, -8, 2,  -5, -7, -8, 4,  -6, -8, -5,
	2,  -3, -8, -8, -5, -8, 0,  -6, -5, -4, -6, -2, -2, -8, -4, -8, -3, -8, -5,
	-2, 2,  0,  -4, 0,  2,  -6, -8, -1, 1,  1,  2,  4,  -2, -2, -2, -1, 2,  1,
	-8, 3,  -2, 2,  -8, 5,  1,  -8, -8, -8, 0,  -8, -8, -8, 2,  -5, -8, -8, -8,
	-8, 2,  -8, -8, -8, -8, -8, 8,  -8, -8, -8, -8, -8, 0,  0,  -4, -6, 3,  -1,
	-6, -3, 3,  0,  -8, -2, -3, 1,  -1, -4, -2, -7, 0,  -2, -3, -7, 0,  -8, 0,
	-8, 1,  -2, -4, 2,  1,  0,  -5, -5, 2,  -3, 0,  4,  -3, -7, 1,  -2, -3, -6,
	-2, -3, -1, -1, -2, -8, 4,  1,  2,  2,  -5, -8, 2,  -3, -6, -5, 1,  -1, -7,
	-6, -1, -7, 1,  3,  -4, -4, -1, -3, 0,  -8, -2, -8, 4,  -8, -1, -1, 1,  4,
	-1, -2, 5,  -3, -1, 1,  1,  -3, -3, -5, 0,  -3, 1,  -8, -1, 1,  -4, -3, -1,
	-3, -1, -3, -4, 0,  -1, -2, -8, 4,  -2, -4, -4, -1, 2,  0,  3,  2,  -1, 1,
	-2, 2,  -2, -1, 5,  2,  3,  -2, -3, 0,  2,  -4, -7, -8, 1,  -5, -8, -3, 0,
	-3, -8, 3,  -5, -8, 2,  4,  -4, 2,  -2, -1, 1,  -8, -3, -8, -3, -8, -8, -8,
	-8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, 8,
	-8, -8, -8, -8, -8, 0,  -1, -1, -1, 2,  -1, 0,  -3, 1,  0,  1,  -2, 0,  -2,
	1,  -1, 0,  -2, 0,  -1, -1, 0,  -1, -3, 2,  -8, 1,  1,  0,  -4, 0,  -1, -3,
	1,  0,  1,  0,  -2, -1, -4, 1,  2,  3,  -6, 0,  2,  0,  -3, 1,  -8, -3, 0,
	-1, -1, -2, -5, -1, -3, -5, 5,  1,  0,  -4, -2, -2, -6, 1,  -4, -2, -2, -2,
	-1, -1, -7, 1,  -8, 0,  -5, -4, 0,  2,  -2, -5, -3, 2,  -7, -3, -3, -2, 3,
	0,  2,  -8, 4,  -6, 3,  2,  2,  -8, -5, -3, -4, -7, 2,  -1, -8, -8, -8, 5,
	-8, -8, -8, 2,  -8, -8, -8, -8, -8, -1, -8, -8, -8, -8, -8, -8, -8, -8, -8,
	-3, -8, 3,  -4, -5, -6, 1,  -5, -8, 3,  2,  -2, -6, -5, -4, -1, 1,  -6, -6,
	-5, -4, -5, -7, -7, -3, -8, -4, -4, 0,  -4, 5,  -7, -1, -3, -8, -2, 2,  -8,
	-8, -8, -3, -8, -5, 7,  4,  -8, -5, 2,  -3, 0,  -3, 6,  -2, -8, 0,  3,  1,
	-1, -2, 1,  -1, -1, 0,  3,  -2, -2, 1,  -4, 3,  0,  1,  -3, 1,  0,  -4, -1,
	2,  -8, -2, -8, 1,  4,  -7, -7, 4,  -7, -5, -6, 1,  -4, 0,  0,  -5, -8, -1,
	-5, -8, -8, -8, -7, -6, -8, -8, -8, 2,  8};

char cipherMatrix[MAXN][MAXN];
string cphr, pruningLevel;
int keylength, traverseOrder[MAXN];
vector<int> minPruneAdjList[MAXN], maxPruneAdjList[MAXN];
bool maxPruneVisited[MAXN], visited[MAXN];

void matricize(string ciphertext) {
	int lim = ciphertext.length() / keylength;
	int st = 0;
	for (int i = 0; i < keylength; i++) {
		for (int r = st; r < (st + lim); r++) {
			cipherMatrix[r - st][i] = ciphertext[r];
		}
		st += lim;
	}
	cout << "Here is the transposition matrix: " << endl;
	for (int r = 0; r < lim; r++) {
		for (int c = 0; c < keylength; c++) {
			cout << cipherMatrix[r][c] << " ";
		}
		cout << endl;
	}
}
void findAvg() {
	int lim = cphr.length() / keylength;
	double dlim = cphr.length() / keylength;
	for (int f = 0; f < keylength; f++) {
		double maxScore = -30.0, avgArr[MAXN];
		for (int s = 0; s < keylength; s++) {
			double avg = 0.0;
			if (f == s) {
				cout << "- ";
				continue;
			}
			for (int i = 0; i < lim; i++) {
				int fchar = cipherMatrix[i][f] - 'a';
				int schar = cipherMatrix[i][s] - 'a';
				avg += scores[fchar][schar];
			}
			avg /= dlim;
			if (avg > 0) {
				minPruneAdjList[f].push_back(s);
				maxPruneVisited[s] = true;
			}
			if (avg > maxScore) {
				maxScore = avg;
			}
			avgArr[s] = avg;
			cout << avg << " ";
		}
		cout << endl;
		for (int i = 0; i < keylength; i++) {
			if (avgArr[i] == maxScore) {
				maxPruneAdjList[f].push_back(i);
			}
		}
	}
}

void Jumble() {
	char shuffled[MAXN][MAXN];
	int lim = cphr.length() / keylength;
	string emp = "";
	// Debugging
	// for(int counter=0; counter<keylength; counter++){
	//   cout<<traverseOrder[counter];
	// }
	// cout<<endl;
	for (int k = 0; k < keylength; k++) {
		for (int r = 0; r < lim; r++) {
			shuffled[r][k] = cipherMatrix[r][traverseOrder[k]];
		}
	}
	for (int r = 0; r < lim; r++) {
		for (int c = 0; c < keylength; c++) {
			emp += shuffled[r][c];
		}
	}
	cout << emp << endl << endl;
}
void lDfsTraverse(int node, int pos) {
	traverseOrder[pos] = node;
	if (pos == keylength - 1) {
		Jumble();
		return;
	}
	for (int j = 0; j < minPruneAdjList[node].size(); j++) {
		int possNextNode = minPruneAdjList[node][j];
		if (visited[possNextNode]) {
			continue;
		}
		visited[possNextNode] = true;
		lDfsTraverse(possNextNode, pos + 1);
		visited[possNextNode] = false;
	}
}

void meHiDfsTraverse(int node, int pos) {
	traverseOrder[pos] = node;
	if (pos == keylength - 1) {
		Jumble();
		return;
	}
	for (int j = 0; j < maxPruneAdjList[node].size(); j++) {
		int possNextNode = maxPruneAdjList[node][j];
		if (visited[possNextNode]) {
			continue;
		}
		visited[possNextNode] = true;
		meHiDfsTraverse(possNextNode, pos + 1);
		visited[possNextNode] = false;
	}
}

void Low() {
	// start from all columns and traverse all edges with weights>0
	for (int counter = 0; counter < keylength; counter++) {
		cout << counter << "-> ";
		for (int i = 0; i < minPruneAdjList[counter].size(); i++) {
			cout << minPruneAdjList[counter][i] << ", ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Here are the pruned permutation strings:" << endl;
	for (int n = 0; n < keylength; n++) {
		visited[n] = true;
		lDfsTraverse(n, 0);
		visited[n] = false;
	}
}
void Medium() {
	// start from all columns and traverse all edges with the maximum weight in
	// the row
	for (int counter = 0; counter < keylength; counter++) {
		cout << counter << "-> ";
		for (int i = 0; i < maxPruneAdjList[counter].size(); i++) {
			cout << maxPruneAdjList[counter][i] << ", ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Here are the pruned permutation strings:" << endl;
	for (int n = 0; n < keylength; n++) {
		visited[n] = true;
		meHiDfsTraverse(n, 0);
		visited[n] = false;
	}
}
void High() {
	// start from columns that have an indegree of 0 and traverse all edges with
	// the maximum weight in the row
	for (int counter = 0; counter < keylength; counter++) {
		cout << counter << "-> ";
		for (int i = 0; i < maxPruneAdjList[counter].size(); i++) {
			cout << maxPruneAdjList[counter][i] << ", ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Here are the pruned permutation strings:" << endl;
	for (int n = 0; n < keylength; n++) {
		if (!maxPruneVisited[n]) {
			visited[n] = true;
			meHiDfsTraverse(n, 0);
			visited[n] = false;
		}
	}
}

int main() {
	cout << "Enter the ciphertext:" << endl;
	cin >> cphr;
	cout << "Enter the key length:" << endl;
	cin >> keylength;
	cout << "Enter the pruning level:" << endl;
	cin >> pruningLevel;
	matricize(cphr);
	cout << endl;
	cout << "Here is the score matrix for each pair of columns:" << endl;
	findAvg();
	cout << endl;
	if (pruningLevel == "low") {
		cout << "Here is the adjacency list for the columns:" << endl;
		Low();
	} else if (pruningLevel == "medium") {
		cout << "Here is the adjacency list for the columns:" << endl;
		Medium();
	} else if (pruningLevel == "high") {
		cout << "Here is the adjacency list for the columns:" << endl;
		High();
	}
}
