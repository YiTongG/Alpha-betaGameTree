//
// Created by yitong on 2023/10/2.
//

#ifndef MINIMAX_MINIMAXGAMETREE_H
#define MINIMAX_MINIMAXGAMETREE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <climits>
#include <algorithm>
#include <unordered_set>
#include <set>

struct Node {
    int value = 0;
    bool isLeaf = true;
    std::vector<std::string> children;
};

class MinimaxGameTree {
public:
    MinimaxGameTree(const std::string& filename);
    int executeMinimax(bool isMaxPlayer, int range, bool verbose, bool useAB);

private:
    std::unordered_map<std::string, Node> graph;
    std::string findRoot();
    void printTree(const std::string& root);
    bool DFS(const std::string& nodeName, const std::string& parentName = "");
    int minimax(const std::string& nodeLabel, bool isMax, int alpha, int beta, bool verbose, bool useAB);
};
#endif //MINIMAX_MINIMAXGAMETREE_H
