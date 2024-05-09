#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> v{1,8,3,4,2,6,5,7,9, 10};
    vector<int> x{7, 2};
    x = v;
    x[0] = 5;
    cout << v[0] << "\n";
}