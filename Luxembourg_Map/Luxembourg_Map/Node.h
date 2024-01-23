#pragma once
#include <QPainter>

class Node
{
private:
	int m_value;
	std::pair<double, double> m_coordinates;
	std::list<Node*> neighbors;
public:
	Node();
	Node(std::pair<double, double> coordinates, int value);
	Node(Node*& other);
	void AddNeighbor(Node* node);
	void SetValue(int value);
	void SetCoordinates(std::pair<double, double> coordinates);
	std::list<Node*> GetNeighbors();
	int GetValue();
	std::pair<double, double> GetCoordinates();
	bool operator==(Node* node);
	float operator-(Node*& node);
};
