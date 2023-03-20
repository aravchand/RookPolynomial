#include <bits/stdc++.h>
using namespace std;

// from gFg, I am still learning hashing... very interesting!
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
 
        if (hash1 != hash2) {
            return hash1 ^ hash2;             
        }

        return hash1;
    }
};

int n, m;
vector<string> board;
int numEmpty = 0;
vector<int> coeff;
vector<bool> forbiddenColumn;

bool valid(int i, int j) {
    return i >= 0 && i < n && j >= 0 && j < m;
}

void countPositions(int row, int numPlacedRooksTotal) {
    if (row == n) {
        coeff[numPlacedRooksTotal]++;
        return;
    }
    
    // try not placing anything in this row.
    countPositions(row + 1, numPlacedRooksTotal); 
    
    // try placing smthn
    for (int j = 0; j < m; j++) { 
        if(board[row][j] == '.' && !forbiddenColumn[j]) {
            forbiddenColumn[j] = true;
            countPositions(row + 1, numPlacedRooksTotal + 1);
            forbiddenColumn[j] = false;
        }
    }
}

int main() {
    cout << "Enter the rectangular format of the board, with '.' for empty places and '*' for obstructed places:\n";

    string s;
    while (getline(cin, s)) {
        if(s == "") break;
        n++;
        if (m == 0)
            m = s.length();
        else if (m != s.length()) {
            cout << "Please enter all rows with the same length so the board is in rectangular form, with places that cannot have rooks as '*'\n";
            continue;
        }
        board.push_back(s);
        for (char c : s) {
            numEmpty += (c == '.');
        }
    }
    cerr << "n,m=" << n << ", " << m << "\n";
    forbiddenColumn.assign(m, false);
    coeff.assign(numEmpty + 1, 0);

    // main call to recursive algorithm
    countPositions(0, 0); 

    vector<string> terms;
    for(int power = 0; power <= numEmpty && coeff[power] > 0; power++) 
        terms.push_back(to_string(coeff[power]) + "x^" + to_string(power));
    

    cout << "RookPolynomial(x) = ";
    for(int i = 0; i < terms.size(); i++) {
        if (i != 0) 
            cout << " + ";
        cout << terms[i];
    }
    cout << "\n";

}