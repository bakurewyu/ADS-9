// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMNode {
public:
    char value;
    std::vector<std::shared_ptr<PMNode>> children;

    PMNode(char val) : value(val) {}
};

class PMTree {
public:
    std::shared_ptr<PMNode> root;
    std::vector<char> original;

    PMTree(const std::vector<char>& input);

private:
    void build(std::shared_ptr<PMNode> node, std::vector<char> remaining);
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
