// Copyright 2022 NNTU-CS
#include <vector>
#include <memory>
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <algorithm>
#include  "tree.h"

PMTree::PMTree(const std::vector<char>& input) : original(input) {
    root = std::make_shared<PMNode>('*');
    build(root, input);
}

void PMTree::build(std::shared_ptr<PMNode> node, std::vector<char> remaining) {
    if (remaining.empty()) return;

    std::sort(remaining.begin(), remaining.end());

    for (size_t i = 0; i < remaining.size(); ++i) {
        char val = remaining[i];
        auto child = std::make_shared<PMNode>(val);
        node->children.push_back(child);

        std::vector<char> next_remaining = remaining;
        next_remaining.erase(next_remaining.begin() + i);

        build(child, next_remaining);
    }
}

void dfs(std::shared_ptr<PMNode> node, std::vector<char>& path,
    std::vector<std::vector<char>>& result) {
    if (node->value != '*') path.push_back(node->value);

    if (node->children.empty()) {
        if (!path.empty())
            result.push_back(path);
    } else {
        for (auto& child : node->children) {
            dfs(child, path, result);
        }
    }

    if (node->value != '*') path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    dfs(tree.root, path, result);
    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    auto perms = getAllPerms(tree);
    if (num < 1 || num > static_cast<int>(perms.size())) return {};
    return perms[num - 1];
}

bool getNthPath(std::shared_ptr<PMNode> node, int& n,
    std::vector<char>& path, std::vector<char>& result) {
    if (node->value != '*') path.push_back(node->value);

    if (node->children.empty()) {
        if (--n == 0) {
            result = path;
            return true;
        }
    } else {
        for (auto& child : node->children) {
            if (getNthPath(child, n, path, result)) return true;
        }
    }

    if (node->value != '*') path.pop_back();
    return false;
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> path, result;
    getNthPath(tree.root, num, path, result);
    return result;
}
