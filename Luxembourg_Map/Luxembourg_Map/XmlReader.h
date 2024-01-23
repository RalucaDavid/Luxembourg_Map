#pragma once
#include <QFile>
#include <QDomDocument>
#include <QDebug>
#include "Graph.h"

class XmlReader
{
public:
	XmlReader() = default;
	XmlReader(const QString& filePath);
	bool ReadData(Graph& graph);
	void SetFilePath(const QString& filePath);
private:
	QString m_filePath;
};

