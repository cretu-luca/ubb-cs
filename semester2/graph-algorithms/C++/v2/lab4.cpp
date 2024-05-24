#pragma once
#include "graph.h"
#include <queue>
using namespace std;

/*  4. Write a program that, given a graph with costs, does the following:
    - verify if the corresponding graph is a DAG and performs a topological sorting of the activities
        using the algorithm based on predecessor counters;
    - if it is a DAG, finds a highest cost path between two given vertices, in O(m+n).
*/

bool Graph::checkIfDAG() {
    queue<int> q;
    vector<int> visited (numberOfNodes + 1, 0);
    vector<int> inDegree (numberOfNodes + 1, 0);
    int count = 0;

    for(int i = 0; i < this->numberOfNodes; i++) {
        inDegree[i] = getInDegree(i);
        if (inDegree[i] == 0) {
            q.push(i);
            visited[i] = 1;
        }
    }

    while(!q.empty()) {
        int v = q.front();
        q.pop();
        count++;
        for(int i: outEdges[v]) {
            if (!visited[i]) {
                inDegree[i]--;
                if (inDegree[i] == 0) {
                    q.push(i);
                    visited[i] = 1;
                }
            }
        }
    }
    return count == this->numberOfNodes;
}

/*
 *  1B. For an unknown tree, we are given two of the three lists representing the vertices parsed in pre-order,
 *  post-order an in-order. Reconstruct the tree.
*/

int Graph::search(vector<int> inOrder, int start, int end, int value) {
    int i;
    for(i = start; i <= end; i++)
        if(inOrder[i] == value)
            return i;

    return -1;
}

// Building Preorder, using Inorder and Postorder

Node* Graph::buildUtilFromInPost(vector<int>& inOrder, vector<int>& postOrder, int inStart, int inEnd, int* pIndex) {
    if(inStart > inEnd)
        return nullptr;

    Node* node = new Node(postOrder[*pIndex]);
    (*pIndex)--;

    if(inStart == inEnd)
        return node;

    int iIndex = search(inOrder, inStart, inEnd, node->data);
    node->right = buildUtilFromInPost(inOrder, postOrder, iIndex +  1, inEnd, pIndex);
    node->left = buildUtilFromInPost(inOrder, postOrder, inStart, iIndex - 1, pIndex);

    return node;
}

Node* Graph::buildPreOrder(vector<int>& inOrder, vector<int>& postOrder, int size) {
    int pIndex = size - 1;
    return buildUtilFromInPost(inOrder, postOrder, 0, size - 1, &pIndex);
}

void Graph::printPreOrder(Node* root) {
    if(root == nullptr)
        return;

    cout << root->data << " ";
    printPreOrder(root->left);
    printPreOrder(root->right);
}

// Building Postorder, using Inorder and Preorder

Node* Graph::buildUtilFromPreIn(vector<int>& preOrder, vector<int>& inOrder, int inStart, int inEnd, int* pIndex) {
    if (inStart > inEnd)
        return nullptr;

    Node* node = new Node(preOrder[*pIndex]);
    (*pIndex)++;

    if (inStart == inEnd)
        return node;

    int iIndex = search(inOrder, inStart, inEnd, node->data);
    node->left = buildUtilFromPreIn(preOrder, inOrder, inStart, iIndex - 1, pIndex);
    node->right = buildUtilFromPreIn(preOrder, inOrder, iIndex + 1, inEnd, pIndex);

    return node;
}

Node* Graph::buildTreeFromPreIn(vector<int>& preOrder, vector<int>& inOrder, int size) {
    int pIndex = 0;
    return buildUtilFromPreIn(preOrder, inOrder, 0, size - 1, &pIndex);
}

void Graph::printPostOrder(Node* root) {
    if(root == nullptr)
        return;

    printPostOrder(root->left);
    printPostOrder(root->right);
    cout << root->data << " ";
}

// Building Inorder, using Preorder and Postorder

Node* Graph::buildFromPrePost(vector<int>& pre, vector<int>& post, int* preIndex, int l, int h, int size) {
    if (*preIndex >= size || l > h)
        return nullptr;

    Node* root = new Node(pre[*preIndex]);
    ++(*preIndex);

    if (l == h)
        return root;

    int i;
    for (i = l; i <= h; ++i)
        if (post[i] == pre[*preIndex])
            break;

    if (i <= h) {
        root->left = buildFromPrePost(pre, post, preIndex, l, i, size);
        root->right = buildFromPrePost(pre, post, preIndex, i + 1, h - 1, size);
    }

    return root;
}

Node* Graph::buildTreePrePost(vector<int>& preOrder, vector<int>& postOrder, int size) {
    int preIndex = 0;
    return buildFromPrePost(preOrder, postOrder, &preIndex, 0, size - 1, size);
}

void Graph::printInOrder(Node* root) {
    if(root == nullptr)
        return;

    printInOrder(root->left);
    cout << root->data << " ";
    printInOrder(root->right);
}

// Reconstructing the tree

void Graph::ReconstructTree() {
    vector<int> inOrder = {8, 4, 9, 2, 5, 1, 6, 3, 7};
    vector<int> postOrder = {8, 9, 4, 5, 2, 6, 7, 3, 1};
    vector<int> preOrder = {1, 2, 4, 8, 9, 5, 3, 6, 7};
    int size = postOrder.size();

    Node* rootPreOrder = this->buildPreOrder(inOrder, postOrder, size);
    cout << "Using Inorder and Postorder lists.\n";
    cout << "Preorder: ";
    this->printPreOrder(rootPreOrder);
    cout << '\n';

    Node* rootPostOrder = this->buildTreeFromPreIn(preOrder, inOrder, size);
    cout << "Using Inorder and Preorder lists.\n";
    cout << "Postorder: ";
    this->printPostOrder(rootPostOrder);
    cout << '\n';

    Node* rootInOrder = this->buildTreePrePost(preOrder, postOrder, size);
    cout << "Using Preorder and Postorder lists.\n";
    cout << "Inorder: ";
    this->printInOrder(rootInOrder);
    cout << '\n';
}

/*
 *  2B. Write a program that, given a graph, does the following:

    verify if the corresponding graph is a DAG and performs a topological sorting of the activities;
    if it is a DAG, finds the number of distinct paths between two given vertices, in O(m+n).
*/

int Graph::numberOfPathsDP(int source, int destination) {
    std::stack<int> order = topSort();
    std::vector<int> pathCounts(this->numberOfNodes, 0);
    pathCounts[source] = 1;

    while(!order.empty()) {
        int current = order.top();
        order.pop();

        for(auto neighbor: outEdges[current])
            pathCounts[neighbor] += pathCounts[current];
    }

    return pathCounts[destination];
}

/*
 *  3B. Write a program that, given a graph with costs, does the following:

    verify if the corresponding graph is a DAG and performs a topological sorting of the activities;
    if it is a DAG, finds the number of distinct lowest cost paths between two given vertices, in O(m+n).
 */

std::pair<int, int> Graph::numberOfLowestCostPaths(int source, int destination) {
    std::stack<int> order = topSort();
    std::vector<int> pathCounts(this->numberOfNodes, 0);
    std::vector<int> minCost(this->numberOfNodes, 1e9);

    pathCounts[source] = 1;
    minCost[source] = 0;

    while(!order.empty()) {
        int current = order.top();
        order.pop();

        for(auto neighbor: outEdges[current]) {
            int cost = getEdgeCost(current, neighbor);

            if(minCost[neighbor] > minCost[current] + cost) {
                minCost[neighbor] = minCost[current] + cost;
                pathCounts[neighbor] = pathCounts[current];
            } else if(minCost[neighbor] == minCost[current] + cost) {
                pathCounts[neighbor] += pathCounts[current];
            }
        }
    }

    return {pathCounts[destination], minCost[destination]};
}