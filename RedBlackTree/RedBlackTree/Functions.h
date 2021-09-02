#pragma once
#include "RedBlackTree.h"
#include <iomanip>
#include <limits>

/// <summary>
/// Validates if a given tree follows the red black tree rules
/// </summary>
/// <param name="tree">The tree to check</param>
/// <returns>True when it is a valid red black tree.  False when it is not</returns>
bool IsValid(const RedBlackTree<int>& tree);

bool IsAdjacentRed(std::shared_ptr<RedBlackNode<int>> node);

bool IsBlackNodeSame(const RedBlackTree<int>& tree);

void BlackNodeTraverse(std::shared_ptr<RedBlackNode<int>> node, std::vector<int>& blackCount, int current);

int GetMenuChoice();

int GetIntInput();

void ClearCin();