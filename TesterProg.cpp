//
//  main.cpp
//  ColumnarCipherv0
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

// Variables
string k, msg, cphr;
int permutations[MAXN], kl;
bool visited[MAXN];

// Functions
bool comp(char a, char b) {
	return a < b;
}

string removeSpaces(string a) {
	string b = "";
	for (int counter = 0; counter < a.length(); counter++) {
		if (a[counter] != ' ') {
			b += a[counter];
		}
	}
	return b;
}

void encryption(string key, string message) {
	int order[MAXN];
	string copykey = key;
	sort(key.begin(), key.end(), comp);

	for (int i = 0; i < copykey.length(); i++) { // Loop 1
		int pos =
			upper_bound(key.begin(), key.end(), copykey[i]) - key.begin() - 1;
		order[pos] = i;
	}

	int N = key.length();
	string plaintext = removeSpaces(message);
	char matrix[MAXN][N];
	string ciphertext[MAXN] = {""};

	cout << "Here is your original message: " << endl
		 << message << endl
		 << endl
		 << "Here is the plaintext being used (your message without spaces):"
		 << endl
		 << plaintext << endl
		 << endl
		 << "Here is the transposition matrix:" << endl;

	for (int counter = 0; counter < plaintext.length(); counter++) { // Loop 2
		int r = counter / N;
		int c = counter % N;
		matrix[r][c] = plaintext[counter];
		ciphertext[c] += plaintext[counter];
	}

	for (int r = 0; r <= (plaintext.length() - 1) / N; r++) { // Loop 3
		for (int c = 0; c < N; c++) {
			cout << matrix[r][c] << " ";
		}
		cout << endl;
	}

	cout << endl
		 << "Here is the encrypted message without permuting the columns "
			"according to the key: "
		 << endl;
	for (int counter = 0; counter < N; counter++) { // Loop 4
		cout << ciphertext[counter] << " ";
	}

	cout << endl
		 << endl
		 << "Here is the final encrypted message which is strung together ("
		 << copykey << " -> " << key << "):" << endl;
	for (int counter = 0; counter < N; counter++) { // Loop 5
		cout << ciphertext[order[counter]];
	}
	cout << endl;
}

void decryption(string key, string ciphertext) {
	string subCiphertext[MAXN];
	vector<string> plaintext;

	int order[MAXN];
	string copykey = key;
	sort(key.begin(), key.end(), comp);
	for (int i = 0; i < copykey.length(); i++) { // Loop 1
		int pos =
			upper_bound(key.begin(), key.end(), copykey[i]) - key.begin() - 1;
		order[pos] = i;
	}

	int mod = ciphertext.length() % key.length();
	if (mod == 0) {
		mod -= key.length();
	}
	int chunkNum = ciphertext.length() / key.length();
	int st = 0;
	for (int counter = 0; counter < key.length(); counter++) { // Loop 2
		int chunk = chunkNum;
		if ((order[counter] + 1) <= mod) {
			chunk++;
		}
		int en = st + chunk;
		string emptystr = "";
		for (int v = st; v < en; v++) {
			emptystr += ciphertext[v];
		}
		subCiphertext[order[counter]] = emptystr;
		st = en;
	}

	for (int r = 0; r <= chunkNum; r++) { // Loop 3
		string emp = "";
		for (int m = 0; m < key.length(); m++) {
			if (subCiphertext[m].size() < (r + 1)) {
				continue;
			}
			emp += subCiphertext[m][r];
		}
		plaintext.push_back(emp);
	}

	cout << "Here is the tranposition matrix: " << endl;
	for (int r = 0; r <= chunkNum; r++) { // Loop 4
		cout << plaintext[r] << endl;
	}
	cout << endl;
	cout << "Here is the final decrypted message: " << endl;
	for (int r = 0; r <= chunkNum; r++) { // Loop 5
		cout << plaintext[r];
	}
	cout << endl;
}

void decryptionWithoutKey(int keylength) {
	string subCiphertext[MAXN];
	vector<string> plaintext;
	int mappingOrder[MAXN], chunkMapper[MAXN];
	int mod = cphr.length() % keylength;
	if (mod == 0) {
		mod += keylength;
	}
	int chunkNum = cphr.length() / keylength;
	int st = 0;
	for (int counter = 0; counter < keylength; counter++) {
		int chunk = chunkNum;
		mappingOrder[permutations[counter]] = counter;
		if ((counter + 1) <= mod) {
			chunk++;
		}
		chunkMapper[permutations[counter]] = chunk;
	}
	for (int counter = 0; counter < keylength; counter++) {
		int en = st + chunkMapper[counter];
		string emptystr = "";
		for (int v = st; v < en; v++) {
			emptystr += cphr[v];
		}
		subCiphertext[mappingOrder[counter]] = emptystr;
		st = en;
	}
	for (int r = 0; r <= chunkNum; r++) {
		string emp = "";
		for (int m = 0; m < keylength; m++) {
			if (subCiphertext[m].size() < (r + 1)) {
				continue;
			}
			emp += subCiphertext[m][r];
		}
		plaintext.push_back(emp);
	}
	for (int r = 0; r <= chunkNum; r++) {
		cout << plaintext[r];
	}
	cout << endl;
}

void dfs(int pos, int N) {
	if (pos == N) {
		decryptionWithoutKey(N);
		return;
	}
	for (int it = 0; it < N; it++) {
		if (visited[it]) {
			continue;
		}

		visited[it] = true;
		permutations[pos] = it;
		dfs(pos + 1, N); // Recursive step
		visited[it] = false;
	}
}

int main() {
	string inp, dummy;
	cout << "Enter e for encryption, d for decryption, or anything else for a "
			"brute force decryption without a key: ";
	cin >> inp;
	if (inp == "e") {
		getline(cin, dummy);
		cout << "Enter the message you would like to encrypt: " << endl;
		getline(cin, msg);
		cout << "Enter the key:" << endl;
		cin >> k;
		encryption(k, msg);
	} else if (inp == "d") {
		getline(cin, dummy);
		cout << "Enter the message you would like to decrypt: " << endl;
		getline(cin, cphr);
		cout << "Enter the key:" << endl;
		cin >> k;
		decryption(k, cphr);
	} else {
		getline(cin, dummy);
		cout << "Enter the message you would like to decrypt: " << endl;
		getline(cin, cphr);
		cout << "Enter the key length:" << endl;
		cin >> kl;
		cout << "Here are all the possible permutation sequences:" << endl;
		dfs(0, kl);
		cout << endl;
		cout << "You can either launch a dictionary attack or CTRL+F to find "
				"common English words in one of the permutations"
			 << endl;
	}
}
