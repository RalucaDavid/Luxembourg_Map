#include "Node.h"

Node::Node()
{
    m_value = -1;
}

Node::Node(std::pair<double, double> coordinates, int value) :m_coordinates(coordinates), m_value(value)
{
    /*empty*/
}

Node::Node(Node*& other)
{
    m_coordinates = other->m_coordinates;
    m_value = other->m_value;
    neighbors = other->neighbors;
}

void Node::AddNeighbor(Node* node)
{
    neighbors.push_back(node);
}

void Node::SetValue(int value)
{
    m_value = value;
}

void Node::SetCoordinates(std::pair<double, double> coordinates)
{
    m_coordinates = coordinates;
}

std::list<Node*> Node::GetNeighbors()
{
    return neighbors;
}

int Node::GetValue()
{
    return m_value;
}

std::pair<double, double> Node::GetCoordinates()
{
    return m_coordinates;
}

bool Node::operator==(Node* node)
{
    if ((m_value == node->m_value) && (m_coordinates == node->m_coordinates))
        return true;
    return false;
}

float Node::operator-(Node*& node)
{
    return sqrt(((m_coordinates.first- node->m_coordinates.first) * (m_coordinates.first - node->m_coordinates.first)) + (m_coordinates.second- node->m_coordinates.second) * (m_coordinates.second- node->m_coordinates.second));
}
