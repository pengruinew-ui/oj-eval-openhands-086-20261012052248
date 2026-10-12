#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Node structure for the binary tree
struct Node {
    int left, right;  // Indices of left and right children
    Node(int l = -1, int r = -1) : left(l), right(r) {}
};

// Function to perform in-order traversal of the tree
void inorderTraversal(const vector<Node>& tree, int root, vector<int>& result) {
    if (root == -1) return;
    
    // Traverse left subtree
    inorderTraversal(tree, tree[root].left, result);
    
    // Visit root
    result.push_back(root);
    
    // Traverse right subtree
    inorderTraversal(tree, tree[root].right, result);
}

// Function to calculate depth of each node
vector<int> calculateDepths(const vector<Node>& tree, int n) {
    vector<int> depth(n + 1, 0);
    queue<int> q;
    
    // Root is node 1, depth 1
    depth[1] = 1;
    q.push(1);
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        // Add children to queue if they exist
        if (tree[node].left != -1) {
            depth[tree[node].left] = depth[node] + 1;
            q.push(tree[node].left);
        }
        if (tree[node].right != -1) {
            depth[tree[node].right] = depth[node] + 1;
            q.push(tree[node].right);
        }
    }
    
    return depth;
}

// Function to swap left and right children of a node
void swapNode(Node& node) {
    swap(node.left, node.right);
}

int main() {
    int n;
    cin >> n;
    
    // Read tree structure
    vector<Node> tree(n + 1);  // 1-indexed
    for (int i = 1; i <= n; i++) {
        int left, right;
        cin >> left >> right;
        tree[i] = Node(left, right);
    }
    
    // Calculate depths of all nodes
    vector<int> depth = calculateDepths(tree, n);
    
    int t;
    cin >> t;
    
    // Process each query
    for (int i = 0; i < t; i++) {
        int k;
        cin >> k;
        
        // For each node, if its depth is a multiple of k, swap its children
        for (int node = 1; node <= n; node++) {
            if (depth[node] % k == 0) {
                swapNode(tree[node]);
            }
        }
        
        // Perform in-order traversal and output result
        vector<int> result;
        inorderTraversal(tree, 1, result);  // Start from root (node 1)
        
        for (size_t j = 0; j < result.size(); j++) {
            cout << result[j];
            if (j < result.size() - 1) cout << " ";
        }
        cout << endl;
    }
    
    return 0;
}