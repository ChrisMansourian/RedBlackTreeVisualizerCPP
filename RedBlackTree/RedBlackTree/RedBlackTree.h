#pragma once
#include <memory>
#include <iostream>
#include <Windows.h>
#include <stack>
#include <queue>
#include <vector>
#include <math.h>
#include <conio.h>

/// <summary>
/// Class to Create a Left Leaning Red Black Tree
/// </summary>
/// <typeparam name="T">The type the tree will be made of</typeparam>
template<typename T>
class RedBlackNode
{
private:
public:
	bool IsRed;
	std::shared_ptr<RedBlackNode<T>> Left;
	std::shared_ptr<RedBlackNode<T>> Right;
	T Value;

	RedBlackNode(T val) : Value(val)
	{
		IsRed = true;
	}
};

template<typename T>
class RedBlackTree
{
private:
	std::shared_ptr<RedBlackNode<T>> Add(T Value, std::shared_ptr<RedBlackNode<T>> Node);
	std::shared_ptr<RedBlackNode<T>> Remove(T Value, std::shared_ptr<RedBlackNode<T>> Node);
	std::shared_ptr<RedBlackNode<T>> MoveRedLeft(std::shared_ptr<RedBlackNode<T>> Node);
	std::shared_ptr<RedBlackNode<T>> MoveRedRight(std::shared_ptr<RedBlackNode<T>> Node);
	std::shared_ptr<RedBlackNode<T>> Fixup(std::shared_ptr<RedBlackNode<T>> Node);
	std::shared_ptr<RedBlackNode<T>> Minimum(std::shared_ptr<RedBlackNode<T>> node);
	bool Contains(T Value, std::shared_ptr<RedBlackNode<T>> Node);
	void VisualizeHelper();

public:
	size_t Count;
	std::shared_ptr<RedBlackNode<T>> Root;

	RedBlackTree();
	~RedBlackTree();
	void Add(T Value);
	void FlipColor(std::shared_ptr<RedBlackNode<T>> Node);
	std::shared_ptr<RedBlackNode<T>> RotateLeft(std::shared_ptr<RedBlackNode<T>> Node);
	std::shared_ptr<RedBlackNode<T>> RotateRight(std::shared_ptr<RedBlackNode<T>> Node);
	bool Remove(T Value);
	bool Contains(T Value);

	void Visualize();


	void Clear();
};

template<typename T>
RedBlackTree<T>::RedBlackTree() : Count(0)
{

}

template<typename T>
RedBlackTree<T>::~RedBlackTree()
{
	Clear();
}

template<typename T>
void RedBlackTree<T>::Clear()
{
	Count = 0;
	std::stack <std::shared_ptr<RedBlackNode<T>>> stack{};
	if (Root)
	{
		stack.push(Root);
		while (stack.size() > 0)
		{
			Root = std::move(stack.top());
			stack.pop();
			if (Root->Right)
			{
				stack.push(Root->Right);
			}
			if (Root->Left)
			{
				stack.push(Root->Left);
			}
			Root.reset();
		}
	}
}

template<typename T>
std::shared_ptr<RedBlackNode<T>> RedBlackTree<T>::RotateRight(std::shared_ptr<RedBlackNode<T>> Node)
{
	auto left = Node->Left;
	left->IsRed = Node->IsRed;
	Node->IsRed = true;
	Node->Left = std::move(left->Right);
	auto tempNode = Node;
	left->Right = std::move(tempNode);

	return left;
}

template<typename T>
std::shared_ptr<RedBlackNode<T>> RedBlackTree<T>::RotateLeft(std::shared_ptr<RedBlackNode<T>> Node)
{
	auto right = Node->Right;
	right->IsRed = Node->IsRed;
	Node->IsRed = true;
	Node->Right = std::move(right->Left);
	auto tempNode = Node;
	right->Left = std::move(tempNode);


	return right;
}

template<typename T>
void RedBlackTree<T>::Add(T Value)
{
	Root = Add(Value, Root);
	Root->IsRed = false;
	Count++;
}

template<typename T>
std::shared_ptr<RedBlackNode<T>> RedBlackTree<T>::Add(T Value, std::shared_ptr<RedBlackNode<T>> Node)
{
	if (!Node)
	{
		return std::make_shared<RedBlackNode<T>>(Value);
	}

	if (Node->Right && Node->Left && Node->Right->IsRed && Node->Left->IsRed)
	{
		FlipColor(Node);
	}

	if (Value >= Node->Value)
	{
		Node->Right = Add(Value, Node->Right);
	}
	else
	{
		Node->Left = Add(Value, Node->Left);
	}

	if (Node->Right && Node->Right->IsRed)
	{
		Node = std::move(RotateLeft(Node));
	}
	if (Node->Left && Node->Left->Left && Node->Left->IsRed && Node->Left->Left->IsRed)
	{
		Node = std::move(RotateRight(Node));
	}

	return Node;
}

template<typename T>
void RedBlackTree<T>::FlipColor(std::shared_ptr<RedBlackNode<T>> Node)
{
	Node->IsRed = !Node->IsRed;
	if (Node->Right)
	{
		Node->Right->IsRed = !Node->Right->IsRed;
	}
	if (Node->Left)
	{
		Node->Left->IsRed = !Node->Left->IsRed;
	}
}

template<typename T>
bool RedBlackTree<T>::Contains(T Value)
{
	return Contains(Value, Root);
}


template<typename T>
bool RedBlackTree<T>::Contains(T Value, std::shared_ptr<RedBlackNode<T>> Node)
{
	if (!Node)
	{
		return false;
	}


	if (Value > Node->Value)
	{
		return Contains(Value, Node->Right);
	}
	else if (Value < Node->Value)
	{
		return Contains(Value, Node->Left);
	}

	return true;
}

template<typename T>
bool RedBlackTree<T>::Remove(T Value)
{
	if (!Contains(Value))
	{
		return false;
	}
	Root = Remove(Value, Root);
	Count--;
	if (Root && Root->IsRed)
	{
		Root->IsRed = false;
	}
	return true;
}

template<typename T>
std::shared_ptr<RedBlackNode<T>> RedBlackTree<T>::Remove(T Value, std::shared_ptr<RedBlackNode<T>> Node)
{
	if (Value < Node->Value)
	{
		if (!Node->Left->IsRed && Node->Left->Left && !Node->Left->Left->IsRed)
		{
			Node = std::move(MoveRedLeft(Node));
		}

		Node->Left = std::move(Remove(Value, Node->Left));
	}
	else
	{
		if (Node->Left && Node->Left->IsRed)
		{
			Node = std::move(RotateRight(Node));
		}

		if (Node->Value == Value && !Node->Right && !Node->Left)
		{
			Node = std::move(nullptr);
			return Node;
		}

		if (Node->Right)
		{
			if (!Node->Right->IsRed && Node->Right->Left && !Node->Right->Left->IsRed)
			{
				Node = std::move(MoveRedRight(Node));
			}

			if (Node->Value == Value)
			{
				std::shared_ptr<RedBlackNode<T>> min = Minimum(Node->Right);
				Node->Value = min->Value;
				Node->Right = std::move(Remove(min->Value, Node->Right));
			}
			else
			{
				Node->Right = std::move(Remove(Value, Node->Right));
			}

		}
	}

	return Fixup(Node);
}

template<typename T>
std::shared_ptr<RedBlackNode<T>> RedBlackTree<T>::MoveRedLeft(std::shared_ptr<RedBlackNode<T>> Node)
{
	FlipColor(Node);

	if (Node->Right && Node->Right->Left && Node->Right->Left->IsRed)
	{
		Node->Right = std::move(RotateRight(Node->Right));
		Node = std::move(RotateLeft(Node));
		FlipColor(Node);

		if (Node->Right && Node->Right->Right && Node->Right->Right->IsRed)
		{
			Node->Right = std::move(RotateLeft(Node->Right));
		}
	}
	return Node;
}

template<typename T>
std::shared_ptr<RedBlackNode<T>> RedBlackTree<T>::MoveRedRight(std::shared_ptr<RedBlackNode<T>> Node)
{
	FlipColor(Node);
	if (Node->Left && Node->Left->Left && Node->Left->Left->IsRed)
	{
		Node = std::move(RotateRight(Node));
		FlipColor(Node);
	}
	return Node;
}

template<typename T>
std::shared_ptr<RedBlackNode<T>> RedBlackTree<T>::Fixup(std::shared_ptr<RedBlackNode<T>> Node)
{
	if (Node->Right && Node->Right->IsRed)
	{
		Node = std::move(RotateLeft(Node));
	}

	if (Node->Left && Node->Left->Left && Node->Left->IsRed && Node->Left->Left->IsRed)
	{
		Node = std::move(RotateRight(Node));
	}

	if (Node->Right && Node->Left && Node->Right->IsRed && Node->Left->IsRed)
	{
		FlipColor(Node);
	}

	if (Node->Left && Node->Left->Right && Node->Left->Left && Node->Left->Right->IsRed && !Node->Left->Left->IsRed || Node->Left && Node->Left->Right && Node->Left->Right->IsRed)
	{
		Node->Left = std::move(RotateLeft(Node->Left));
		if (Node->Left->IsRed)
		{
			Node = std::move(RotateRight(Node));
		}
	}

	if (!Node->Right && Node->Left && Node->IsRed && !Node->Left->IsRed)
	{
		FlipColor(Node);
	}

	if (Node->Right && Node->Left && !Node->Left->IsRed && Node->IsRed && !Node->Right->IsRed && !Node->Right->Left && Node->Right->Right)
	{
		FlipColor(Node);
		Node->Right->IsRed = false;
		Node->Right->Right->IsRed = true;
	}

	return Node;
}

template<typename T>
std::shared_ptr<RedBlackNode<T>> RedBlackTree<T>::Minimum(std::shared_ptr<RedBlackNode<T>> Node)
{
	std::shared_ptr<RedBlackNode<T>> current = Node;
	while (Node->Left)
	{
		Node = Node->Left;
	}
	return Node;
}


template<typename T>
void RedBlackTree<T>::Visualize()
{
	system("CLS");
	VisualizeHelper();

	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, 7);
	std::cout << std::endl;
	//system("Color 07");//white text
	//system("Color 04");//red text
}

template<typename T>
void RedBlackTree<T>::VisualizeHelper()
{
	auto current = Root;
	int depth = std::ceil(std::log2(Count));
	int x = 0;
	if (Count == 0)
	{
		return;
	}
	std::queue<int> xCords{};
	xCords.push(std::pow(2, depth)*3);
	std::queue <std::shared_ptr<RedBlackNode<T>>> Nodes{};
	Nodes.push(Root);
	while (Nodes.size() > 0)
	{
		if (Nodes.front() == nullptr)
		{
			xCords.pop();
			Nodes.pop();
			continue;
		}
		int xCord = xCords.front();
		xCords.pop();
		bool shouldGoDown = false;
		if (xCords.size() == 0 || xCords.front() < xCord)
		{
			shouldGoDown = true;
		}
		while (x < xCord)
		{
			std::cout << " ";
			x++;
		}
		if (Nodes.front()->IsRed)
		{

			HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hcon, 4);//red for the red nodes
		}
		else
		{

			HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hcon, 7);//white for the black nodes
		}
		std::cout << Nodes.front()->Value;
		Nodes.push(Nodes.front()->Left);
		Nodes.push(Nodes.front()->Right);
		xCords.push(xCord - std::pow(2, depth-1) *3);
		xCords.push(xCord + std::pow(2, depth-1) *3);
		//xCords.pop();
		Nodes.pop();
		if (shouldGoDown)
		{
			x = 0;
			std::cout << std::endl;
			depth--;
		}
	}

}