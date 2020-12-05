#include "ResourceLoader.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <iostream>

std::string ResourceLoader::loadResourceFileToString(const std::string &resourcePath)
{
    QString vertFilePath = QString::fromStdString(resourcePath);
    QFile vertFile(vertFilePath);
    if (vertFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream vertStream(&vertFile);
        QString contents = vertStream.readAll();
        std::cout << "successfully opened: " << resourcePath << std::endl;
        return contents.toStdString();
    }
    throw CS123::IOException("Could not open file: " + resourcePath);
}
