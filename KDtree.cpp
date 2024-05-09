#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

template<size_t N>
struct Node {
    Node *left;
    Node *right;
    std::array<int, N> pt;

    Node() : left(nullptr), right(nullptr), pt({}) {}

};

template<size_t N>
class KDTree {
    public:
        KDTree<N>(std::vector<std::array<int, N>>& pts);
        Node<N>* buildTree(std::vector<std::array<int, N>>& pts, int depth);

    private:
        Node<N> *_root;
};

template<size_t N>
KDTree<N>::KDTree(std::vector<std::array<int, N>>& pts) {
    _root = buildTree(pts, 0);
}

template<size_t N>
Node<N>* KDTree<N>::buildTree(std::vector<std::array<int, N>>& pts, int depth) {
    Node<N> *cur = new Node<N>();
    if(pts.size() == 1) {
        cur->pt = pts[0];
        return cur;
    }

    int ind = depth % N;
    auto mid = pts.begin() + pts.size() / 2;
    
    std::nth_element(pts.begin(), mid, pts.end(), [ind](std::array<int, N>& a, std::array<int, N>& b) {
        return a[ind] < b[ind];
    });

    std::vector<std::array<int, N>> left(pts.begin(), mid);
    std::vector<std::array<int, N>> right(mid, pts.end());

    cur->left = buildTree(left, depth + 1);
    cur->right = buildTree(right, depth + 1);

    return cur;
}

int main() {
    std::vector<std::array<int, 3>> pts = {
        {1, 13, 5},
        {6, 9, 2},
        {8, 10, 8},
        {7, 4, 1},
        {5, 9, 15}
    };

    KDTree<3> kd(pts);
}