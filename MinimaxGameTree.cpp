//
// Created by yitong on 2023/10/2.
//

#include "MinimaxGameTree.h"

using namespace std;

std::string MinimaxGameTree::findRoot() {
    unordered_set<string> childNodes;
    set<string> possibleRoots;
    for (const auto& pair : graph) {
        possibleRoots.insert(pair.first);
    }
    for (const auto& pair : graph) {
        for (const auto& child : pair.second.children) {
            childNodes.insert(child);
            possibleRoots.erase(child);
        }
    }
    if (possibleRoots.size() > 1) {
        cerr << "Multiple roots detected: ";
        for (const auto& root : possibleRoots) {
            cerr << "\"" << root << "\" ";
        }
        cerr << endl;
        exit(1);
    }
    for (const auto& pair : graph) {
        if (childNodes.find(pair.first) == childNodes.end()) {
            return pair.first;
        }
    }
    return "";
}

void MinimaxGameTree::printTree(const string& root) {
    auto it = graph.find(root);
    if (it == graph.end()) return;

    const Node& node = it->second;
    if (node.isLeaf) {
        cout << it->first << "=" << node.value << endl;
    } else {
        cout << it->first << ": [";
        for (const auto& child : node.children) {
            cout << child;
            if (&child != &node.children.back()) cout << ", ";
        }
        cout << "]" << endl;
        for (const auto& child : node.children) {
            printTree(child);
        }
    }
}

bool MinimaxGameTree::DFS(const string& nodeName, const string& parentName) {
    if (graph.find(nodeName) == graph.end()) {
        if (!parentName.empty()) {
            cerr << "Error: child node \"" << nodeName << "\" of \"" << parentName << "\" not found." << endl;
        } else {
            cerr << "Error: node \"" << nodeName << "\" not found." << endl;
        }
        exit(1);
    }

    if (graph[nodeName].isLeaf) {
        return true;
    }

    for (const auto& child : graph[nodeName].children) {
        if (!DFS(child, nodeName)) {
            cerr << "Error: child node \"" << child << "\" of \"" << nodeName << "\" not found." << endl;
            exit(1);
        }
    }
    return true;
}

int MinimaxGameTree::minimax(const string& nodeLabel, bool isMax, int alpha, int beta, bool verbose, bool useAB) {
    Node& node = graph[nodeLabel];
    bool isPruned = false;

    if (node.isLeaf) return node.value;

    if (isMax) {
        int maxValue = INT_MIN;
        string bestMove;
        for (const auto& child : node.children) {
            int val = minimax(child, false, alpha, beta, verbose, useAB);
            if (val > maxValue) {
                maxValue = val;
                bestMove = child;
            }
            alpha = max(alpha, val);
            if (beta < alpha) {
                if (useAB) isPruned = true;
                break;
            }
        }
        if (verbose && !isPruned) {
            cout << "max(" << nodeLabel << ") chooses " << bestMove << " for " << maxValue << endl;
        } else if (nodeLabel == findRoot()) {
            cout << "max(" << nodeLabel << ") chooses " << bestMove << " for " << maxValue << endl;
        }
        return maxValue;
    } else {
        int minValue = INT_MAX;
        string bestMove;
        for (const auto& child : node.children) {
            int val = minimax(child, true, alpha, beta, verbose, useAB);
            if (val < minValue) {
                minValue = val;
                bestMove = child;
            }
            beta = min(beta, val);
            if (beta < alpha) {
                if (useAB) isPruned = true;
                break;
            }
        }
        if (verbose && !isPruned) {
            cout << "min(" << nodeLabel << ") chooses " << bestMove << " for " << minValue << endl;
        } else if (nodeLabel == findRoot()) {
            cout << "min(" << nodeLabel << ") chooses " << bestMove << " for " << minValue << endl;
        }
        return minValue;
    }
}

MinimaxGameTree::MinimaxGameTree(const string& filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        string label;
        if (line.empty() || line[0] == '#') continue;

        if (line.find('=') != string::npos) {
            size_t pos = line.find('=');
            label = line.substr(0, pos);
            int value = stoi(line.substr(pos + 1));
            graph[label].value = value;
            graph[label].isLeaf = true;
        } else if (line.find(':') != string::npos) {
            size_t pos = line.find(':');
            label = line.substr(0, pos);
            stringstream ss(line.substr(pos + 1));
            string child;
            while (getline(ss, child, ',')) {
                child.erase(remove(child.begin(), child.end(), ' '), child.end());
                child.erase(remove(child.begin(), child.end(), '['), child.end());
                child.erase(remove(child.begin(), child.end(), ']'), child.end());
                if (!child.empty()) {
                    graph[label].children.push_back(child);
                    graph[label].isLeaf = false;
                }
            }
        }
    }
}

int MinimaxGameTree::executeMinimax(bool isMaxPlayer, int range, bool verbose, bool useAB) {
    string root = findRoot();
    DFS(root); //verified if the tree is complete
    return minimax(root, isMaxPlayer, -range, range, verbose, useAB);
}


