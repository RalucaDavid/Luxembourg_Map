#pragma once
#include "Node.h"

class Arch
{
private:
	Node* m_firstNode;
	Node* m_secondNode;
	int m_length;
	int m_color;
public:
	Arch();
	Arch(Node* firstNode, Node* secondNode, int length);
	Arch(const Arch& other);
	void SetSourceNode(Node* firstNode);
	void SetDestinationNode(Node* secondNode);
	void SetLength(int length);
	void SetColor(int color);
	Node* GetSourceNode();
	Node* GetDestinationNode();
	int GetLength();
	int GetColor();
};

