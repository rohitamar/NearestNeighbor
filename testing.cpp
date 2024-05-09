#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> v{1,8,3,4,2,6,5,7,9, 10};
    vector<int> x{1, 2};
    swap(x, v);
    cout << v.size() / 2 << "\n";
    auto m = v.begin() + v.size() / 2;
    nth_element(v.begin(), m, v.end());
    cout << "\nThe median is " << v[v.size() / 2] << '\n';
    for(int x : v) cout << x << " ";
    cout << "\n";
}