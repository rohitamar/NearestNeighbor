#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

template<size_t N>
struct Node {
    Node *left;
    Node *right;
    std::array<int, N> pt;
    bool leaf;
    int splitVal;
    int splitInd;

    Node() : left(nullptr), right(nullptr), pt({}), leaf(false), splitVal(0), splitInd(0) {}
};

template<size_t N>
class KDTree {
    public:
        KDTree(std::vector<std::array<int, N>> pts);
        Node<N>* buildTree(std::vector<std::array<int, N>>& pts, int depth);
        void nearest(Node<N> *cur, const std::array<int, N>& point, std::array<int, N>& closest);
        std::array<int, N> nearestNeighbor(const std::array<int, N>& point);
    private:
        Node<N> *_root;
};

template<size_t N>
KDTree<N>::KDTree(std::vector<std::array<int, N>> pts) {
    _root = buildTree(pts, 0);
}

template<size_t N>
Node<N>* KDTree<N>::buildTree(std::vector<std::array<int, N>>& pts, int depth) {
    Node<N> *cur = new Node<N>();
    if(pts.size() == 1) {
        cur->pt = pts[0];
        cur->leaf = true;
        return cur;
    }

    int ind = depth % N;
    auto mid = pts.begin() + pts.size() / 2;

    std::nth_element(pts.begin(), mid, pts.end(), [ind](std::array<int, N>& a, std::array<int, N>& b) {
        return a[ind] < b[ind];
    });

    cur->splitVal = (*mid)[ind];
    cur->splitInd = ind;
    cur->leaf = false;

    std::vector<std::array<int, N>> left(pts.begin(), mid);
    std::vector<std::array<int, N>> right(mid, pts.end());

    cur->left = buildTree(left, depth + 1);
    cur->right = buildTree(right, depth + 1);

    return cur;
}

template<size_t N>
int distance(const std::array<int, N>& a, const std::array<int, N>& b) {
    int dist = 0;
    for(size_t i = 0; i < N; i++) {
        dist += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return dist;
}

template<size_t N>
void KDTree<N>::nearest(Node<N> *cur, const std::array<int, N>& point, std::array<int, N>& closest) {

    if(cur == nullptr) return;

    int dist = distance(point, closest);
    if(cur->leaf) {
        if(distance(point, cur->pt) < dist) closest = cur->pt;
        return;
    }

    int median = cur->splitVal;
    int ind = cur->splitInd;

    if(point[ind] < median) {
        if(point[ind] - dist < median) nearest(cur->left, point, closest);
        if(point[ind] + dist >= median) nearest(cur->right, point, closest);
    } else {
        if(point[ind] + dist >= median) nearest(cur->right, point, closest);
        if(point[ind] - dist < median) nearest(cur->left, point, closest);
    }
}

template<size_t N>
std::array<int, N> KDTree<N>::nearestNeighbor(const std::array<int, N>& point) {
    std::array<int, N> ans;
    for(size_t i = 0; i < N; i++) ans[i] = -1500;
    nearest(_root, point, ans);
    return ans;
}
