#include "Arch.h"

Arch::Arch()
{
	m_color = 0;
}

Arch::Arch(Node* firstNode, Node* secondNode, int length) :m_firstNode(firstNode), m_secondNode(secondNode), m_length(length)
{
	m_color = 0;
}

Arch::Arch(const Arch& other)
{
	m_firstNode = other.m_firstNode;
	m_secondNode = other.m_secondNode;
	m_length = other.m_length;
	m_color = other.m_color;
}

void Arch::SetSourceNode(Node* firstNode)
{
	m_firstNode = firstNode;
}

void Arch::SetDestinationNode(Node* secondNode)
{
	m_secondNode = secondNode;
}

void Arch::SetLength(int length)
{
	m_length = length;
}

void Arch::SetColor(int color)
{
	m_color = color;
}

Node* Arch::GetSourceNode()
{
	return m_firstNode;
}

Node* Arch::GetDestinationNode()
{
	return m_secondNode;
}

int Arch::GetLength()
{
	return m_length;
}

int Arch::GetColor()
{
	return m_color;
}
