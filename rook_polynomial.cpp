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
unordered_map<pair<int, int>, bool, hash_pair> placed;
int numEmpty = 0;
vector<int> coeff;
vector<bool> forbiddenColumn;

vector<int> dx = {0, -1, 0, 1};
vector<int> dy = {-1, 0, 1, 0};

bool valid(int i, int j) {
    return i >= 0 && i < n && j >= 0 && j < m;
}

bool canPlace(int oi, int oj) {
    if(board[oi][oj] == '*') return 0;

    for (int d = 0; d < 4; d++) {
        int i = oi, j = oj;
        while (valid(i, j)) {
            // * -> break is not actually a condition. since here, the rooks can "jump"! 
            // (actually this whole method canPlace is overkill and slower as its: O(n + m) in this format of the problem)
            // once I understoon this, the code is much simplifer including recursion aspect lol
            // if (board[i][j] == '*')
            //     break;
            if (placed[{i, j}])
                return 0;
            i += dx[d];
            j += dy[d];
        }
    }
    return 1;
}

// set<string> board_seen;
void countPositions(int row, int numPlacedRooksTotal) {
    if (row == n) {
        coeff[numPlacedRooksTotal]++;
        // // debugging
        // vector<string> mb = board;
        // for(auto rook : placed) {
        //     if(rook.second) mb[rook.first.first][rook.first.second] = 'R';
        // }
        // string s = "";
        // for(int i = 0; i < n; i++) {
        //     if(placedRooks == 2) cerr << mb[i] << "\n";
        //     s += mb[i];
        // }
        // if(board_seen.count(s) != 0) cerr << "\n\nBAD \nBAD \nBAD\n\n ";
        // board_seen.insert(s);
        // if(placedRooks == 2) cerr << "\n";
        return;
    }
    
    // try not placing anything in this row.
    countPositions(row + 1, numPlacedRooksTotal); 
    
    // try placing smthn
    for (int j = 0; j < m; j++) { 
        // if(canPlace(row, j)) 
        if(board[row][j] == '.' && !forbiddenColumn[j]) {
            // placed[{row, j}] = 1;
            forbiddenColumn[j] = true;
            countPositions(row + 1, numPlacedRooksTotal + 1);
            // placed[{row, j}] = 0;
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