#include "Functions.h"


bool IsValid(const RedBlackTree<int>& tree)
{
	if (tree.Root->IsRed || IsAdjacentRed(tree.Root) || !IsBlackNodeSame(tree))
	{
		return false;
	}

	return true;
}

bool IsAdjacentRed(std::shared_ptr<RedBlackNode<int>> node)
{
	if (node == nullptr)
	{
		return false;
	}

	if (node->IsRed && node->Left != nullptr && node->Left->IsRed || node->IsRed && node->Right != nullptr && node->Right->IsRed)
	{
		return true;
	}

	bool isLeftValid = IsAdjacentRed(node->Left);
	bool isRightValid = IsAdjacentRed(node->Right);

	return isLeftValid && isRightValid;

}


bool IsBlackNodeSame(const RedBlackTree<int>& tree)
{
	std::vector<int> blackNodeCounter{};
	BlackNodeTraverse(tree.Root, blackNodeCounter, 0);
	if (blackNodeCounter.size() > 0)
	{
		int amount = blackNodeCounter.front();
		for (auto num : blackNodeCounter)
		{
			if (num != amount)
			{
				return false;
			}
		}
	}
	return true;
}

void BlackNodeTraverse(std::shared_ptr<RedBlackNode<int>> node, std::vector<int>& blackCount, int current)
{
	if (node != nullptr)
	{
		int val = current;
		if (!node->IsRed)
		{
			val++;
		}
		BlackNodeTraverse(node->Left, blackCount, val);
		BlackNodeTraverse(node->Right, blackCount, val);
	}
	else
	{
		blackCount.push_back(current);
	}
}