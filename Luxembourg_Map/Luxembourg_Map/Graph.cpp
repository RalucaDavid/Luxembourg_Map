#include "Graph.h"

Graph::Graph()
{
	/*empty*/
}

void Graph::AddNode(Node* node)
{
	nodes.push_back(node);
    if (adjacencyList.size() < nodes.size()) 
        adjacencyList.resize(nodes.size());
}

void Graph::AddArch(Arch* arch)
{
	arches.push_back(arch);
}

void Graph::AddArch(Node* node1, Node* node2, int length)
{
	Arch* newArch = new Arch(node1, node2, length);
	arches.push_back(newArch);
	node1->AddNeighbor(node2);
	node2->AddNeighbor(node1);
}

void Graph::AddAdjacencyList(int index, Arch* arch)
{
    adjacencyList[index].push_back(arch);
}

std::vector<Node*>& Graph::GetNodes()
{
	return nodes;
}

std::vector<Arch*>& Graph::GetArches()
{
	return arches;
}

struct Comparator
{
	bool operator()(const std::pair<int, Node*>& pair1, const std::pair<int, Node*>& pair2)
	{
		return pair1.first > pair2.first;
	}
};

void Graph::Dijkstra(Node* sourceNode, Node* destinationNode)
{
    const int infinity = std::numeric_limits<int>::max();
    std::vector<int> distances(nodes.size(), infinity);
    std::vector<bool> visitedNodes(nodes.size(), false);
    std::priority_queue<std::pair<int, Node*>, std::vector<std::pair<int, Node*>>, Comparator> pq;
    std::vector<Node*> p(nodes.size(),nullptr); //predecessors
    distances[sourceNode->GetValue()] = 0;
    pq.push({ 0, sourceNode });
    bool found = false;
    Node* currentNode;
    while (!pq.empty())
    {
        currentNode = pq.top().second;
        pq.pop();
        if (visitedNodes[currentNode->GetValue()])
            continue;
        visitedNodes[currentNode->GetValue()] = true;
        if (currentNode == destinationNode)
        {
            found = true;
            break;
        }
        for (Arch*& arch: adjacencyList[currentNode->GetValue()])
        {
            Node* anotherNode;
            if (arch->GetSourceNode() == currentNode)
                anotherNode = arch->GetDestinationNode();
            else
                anotherNode = arch->GetSourceNode();
            int length = arch->GetLength();
            if ((!visitedNodes[anotherNode->GetValue()]) && (distances[currentNode->GetValue()] + length < distances[anotherNode->GetValue()]))
            {
                distances[anotherNode->GetValue()] = distances[currentNode->GetValue()] + length;
                p[anotherNode->GetValue()] = currentNode;
                pq.push({distances[anotherNode->GetValue()],anotherNode});
            }
        }
    }
    if (found)
    {
        qDebug() << "The path was found.\n";
        totalLength = 0;
        Node* currentNode = destinationNode;
        while (currentNode != nullptr)
        {
            auto it = std::find_if(arches.begin(), arches.end(),
                [&](Arch*& arch) {
                    return arch->GetSourceNode() == currentNode && arch->GetDestinationNode() == p[currentNode->GetValue()];
                });
            if (it == arches.end())
            {
                it = std::find_if(arches.begin(), arches.end(),
                    [&](Arch*& arch) {
                        return arch->GetSourceNode() == p[currentNode->GetValue()] && arch->GetDestinationNode() == currentNode;
                    });
            }
            if (it != arches.end())
            {
                (*it)->SetColor(1);
                totalLength += (*it)->GetLength();
                pathDijkstra.push_back(*it);
            }
            currentNode = p[currentNode->GetValue()];
        }
    }
    else
    {
        qDebug() << "The path was not found.\n";
    }
}

std::vector<Arch*> Graph::GetPathDijkstra()
{
    return pathDijkstra;
}

int Graph::GetTotalLength()
{
	return totalLength;
}

Graph::~Graph()
{
	for (Node*& node : nodes) 
	{
		delete node;
	}
	for (Arch*& arch : arches) 
	{
		delete arch;
	}
}
