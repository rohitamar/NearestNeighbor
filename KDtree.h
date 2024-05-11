#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <queue>

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
int distance(const std::array<int, N>& a, const std::array<int, N>& b) {
    int dist = 0;
    for(size_t i = 0; i < N; i++) {
        dist += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return dist;
}

template<size_t N>
class KDTree {
    public:
        KDTree(std::vector<std::array<int, N>> pts);
        Node<N>* buildTree(std::vector<std::array<int, N>>& pts, int depth);
        void nearest(Node<N> *cur, const std::array<int, N>& point, std::priority_queue<std::pair<int, std::array<int, N>>>& closest, int k);
        std::vector<std::array<int, N>> nearestNeighbor(const std::array<int, N>& point, int K);
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
void KDTree<N>::nearest(Node<N> *cur, const std::array<int, N>& point, std::priority_queue<std::pair<int, std::array<int, N>>>& closest, int k) {

    if(cur == nullptr) return;

    int dist = distance(point, closest.top().second);
    if(cur->leaf) {
        closest.emplace(distance(point, cur->pt), cur->pt);
        if(closest.size() > k) closest.pop();
        return;
    }

    int median = cur->splitVal;
    int ind = cur->splitInd;

    if(point[ind] < median) {
        if(point[ind] - dist < median) nearest(cur->left, point, closest, k);
        if(point[ind] + dist >= median) nearest(cur->right, point, closest, k);
    } else {
        if(point[ind] + dist >= median) nearest(cur->right, point, closest, k);
        if(point[ind] - dist < median) nearest(cur->left, point, closest, k);
    }
}

template<size_t N>
std::vector<std::array<int, N>> KDTree<N>::nearestNeighbor(const std::array<int, N>& point, int K) {
    std::priority_queue<std::pair<int, std::array<int, N>>> ans;
    std::array<int, N> mx;
    for(size_t i = 0; i < N; i++) mx[i] = -550;
    ans.emplace(distance(point, mx), mx);
    nearest(_root, point, ans, K);
    std::vector<std::array<int, N>> indices;
    while(!ans.empty()) {
        auto [_, arr] = ans.top(); 
        ans.pop();
        indices.push_back(arr);
    }
    reverse(indices.begin(), indices.end());
    return indices;
}
