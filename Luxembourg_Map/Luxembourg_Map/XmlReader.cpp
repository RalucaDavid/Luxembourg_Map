#include "XmlReader.h"

XmlReader::XmlReader(const QString& filePath) : m_filePath(filePath)
{
	/*empty*/
}

bool XmlReader::ReadData(Graph& graph)
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) 
    {
        qDebug() << "Failed to open the file: " << file.errorString();
        return false;
    }
    QDomDocument xmlDoc;
    if (!xmlDoc.setContent(&file)) 
    {
        qDebug() << "Failed to set content from XML file.";
        file.close();
        return false;
    }
    file.close();
    QDomElement root = xmlDoc.documentElement();
    QDomElement nodesElement = root.firstChildElement("nodes");
    QDomNodeList nodesList = nodesElement.elementsByTagName("node");

    // Calculations made according to Mercador Projection
    const int Width = 562;
    const int Height = 921;
    const int minLatitude = 4945029;
    const int maxLatitude = 5018275;
    const int minLongitude = 573929;
    const int maxLongitude = 652685;
    float deltaLong = maxLongitude - minLongitude;
    float deltaLat = maxLatitude - minLatitude;
    float  scaleFactorLat = Height / deltaLat;
    float  scaleFactorLong = Width / deltaLong;

    for (int index = 0; index < nodesList.size(); index++) 
    {
        QDomElement nodeElement = nodesList.at(index).toElement();
        if (!nodeElement.isNull()) 
        {
            Node* node = new Node;
            QDomNamedNodeMap attributes = nodeElement.attributes();
            int longitude = attributes.namedItem("longitude").nodeValue().toInt();
            int latitude = attributes.namedItem("latitude").nodeValue().toInt();
            float  y_scaled = ((longitude - minLongitude) * scaleFactorLong);
            float  x_scaled = ((latitude - minLatitude) * scaleFactorLat);
            double y = y_scaled+30;
            double x = Height - x_scaled+30;
            node->SetValue(nodeElement.attribute("id").toInt());
            node->SetCoordinates({ y,x });
            graph.AddNode(node);
        }
    }

    QDomElement arcsElement = root.firstChildElement("arcs");
    QDomNodeList archesList = arcsElement.elementsByTagName("arc");
    for (int index = 0; index < archesList.size(); index++) 
    {
        QDomElement archElement = archesList.at(index).toElement();
        if (!archElement.isNull()) 
        {
            Arch* arch = new Arch;
            int fromValue = archElement.attribute("from").toInt();
            int toValue = archElement.attribute("to").toInt();
            for (Node* node : graph.GetNodes())
            {
                if (node->GetValue() == fromValue)
                {
                    arch->SetSourceNode(node);
                }
                else if (node->GetValue() == toValue)
                {
                    arch->SetDestinationNode(node);
                }
            }
            arch->SetLength(archElement.attribute("length").toInt());
            arch->GetSourceNode()->AddNeighbor(arch->GetDestinationNode());
            arch->GetDestinationNode()->AddNeighbor(arch->GetSourceNode());
            graph.AddAdjacencyList(arch->GetSourceNode()->GetValue(), arch);
            graph.AddAdjacencyList(arch->GetDestinationNode()->GetValue(), arch);
            graph.AddArch(arch);
        }
    }
    return true;
}

void XmlReader::SetFilePath(const QString& filePath)
{
    m_filePath = filePath;
}
