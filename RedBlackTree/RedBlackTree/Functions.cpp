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

int GetMenuChoice()
{
	int input = -1;

	//Display menu
	std::cout << "\n\nWhat would you like to do?\n" << std::setw(5) << "" << "1)Add To Tree\n" << std::setw(5) << "" << "2)Remove From Tree\n" << std::setw(5) << "" << "3)Exit\n" << std::endl;
	
	bool validInput = false;
	
	while (!validInput)
	{
		if (!(std::cin >> input) || input < 1 || input > 3)//Get user input
		{
			//failed to get input, set it to -1 and cin clear and ignore
			input = -1;
			ClearCin();
			std::cout << "Please enter a valid choice: ";
		}
		else
		{
			validInput = true;
		}
	}

	return input;//Return the input as an int 
}


int GetIntInput()
{
	int input = -1;

	//Display menu
	std::cout << "\n\nEnter the Integer you want:" << std::endl;

	bool validInput = false;

	while (!validInput)
	{
		if (!(std::cin >> input))//Get user input
		{
			//failed to get input, set it to -1 and cin clear and ignore
			input = -1;
			ClearCin();
			std::cout << "Please enter a number: ";
		}
		else
		{
			validInput = true;
		}
	}

	return input;//Return the input as an int 
}

void ClearCin()
{
	std::cin.clear();
	std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}
