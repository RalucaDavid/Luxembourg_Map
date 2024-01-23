#pragma once

#include <vector>
#include <fstream>
#include "Arch.h"
#include <queue>
#include <limits>
#include <qDebug>
#include <set>

class Graph
{
private:
	std::vector<Node*> nodes;
	std::vector<Arch*> arches;
	std::vector < std::vector<Arch*>> adjacencyList;
	std::vector<Arch*> pathDijkstra;
	int totalLength;
public:
	Graph();
	void AddNode(Node* node);
	void AddArch(Arch* arch);
	void AddArch(Node* node1, Node* node2, int length);
	void AddAdjacencyList(int index, Arch* arch);
	std::vector<Node*>& GetNodes();
	std::vector<Arch*>& GetArches();
	void Dijkstra(Node* sourceNode, Node* destinationNode);
	std::vector<Arch*> GetPathDijkstra();
	int GetTotalLength();
	~Graph();
};

