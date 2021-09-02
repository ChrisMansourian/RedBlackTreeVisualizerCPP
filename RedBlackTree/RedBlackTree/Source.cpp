#pragma once
#include <Iostream>
#include "RedBlackTree.h"
#include "Functions.h" 


int main()
{
	RedBlackTree<int> tree{};

	/*for (size_t i = 0; i < 20; i++)
	{
		tree.Add(i);
		std::cout << IsValid(tree) << std::endl;
	}

	std::cout << std::endl;
	IsValid(tree);

	bool result = tree.Remove(10);
	std::cout << IsValid(tree) << std::endl;
	bool result2 = tree.Remove(55);
	std::cout << IsValid(tree) << std::endl;
	bool result3 = tree.Remove(7);
	std::cout << IsValid(tree) << std::endl;
	bool result4 = tree.Remove(4);
	std::cout << IsValid(tree) << std::endl;
	bool result5 = tree.Remove(5);
	std::cout << IsValid(tree) << std::endl;
	bool result6 = tree.Remove(2);
	std::cout << IsValid(tree) << std::endl;
	bool result7 = tree.Remove(14);
	std::cout << IsValid(tree) << std::endl;
	for (size_t i = 15; i < 20; i++)
	{
		tree.Remove(i);

		std::cout << IsValid(tree) << std::endl;
	}
	tree.Visualize();
	int test;
	std::cin >> test;*/

	int choice = GetMenuChoice();
	while (choice != 3)
	{
		if (choice == 1)
		{
			tree.Add(GetIntInput());
		}
		else if (choice == 2)
		{
			tree.Remove(GetIntInput());
		}
		tree.Visualize();
		choice = GetMenuChoice();

	}



	return 0;
}