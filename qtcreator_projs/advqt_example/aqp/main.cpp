/*
    Copyright (c) 2009-10 Qtrac Ltd. All rights reserved.

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include "aqp.hpp"
#include <QApplication>
#include <QStringList>
#include <QTextStream>
#include <QtCore>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv, false);

    QString strDir =
            QApplication::applicationDirPath()
            + "/TestQXmlStreamWriter1.xml";
    QFile file(strDir);
    if(file.open( QIODevice::WriteOnly))
    {
        QXmlStreamWriter writer(&file);
        //writer.setCodec(Q);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        //writer.writeComment("Mytag is the test tag!!!");
        writer.writeStartElement("Mytag");

        //writer.writeAttribute("kkk","val","111");
        writer.writeAttribute("111","111");
        writer.writeAttribute("222","222");
        writer.writeAttribute("333","333");
        writer.writeTextElement("A", "testAAA");
        writer.writeEndElement();
        file.close();
    }

    QTextStream out(stdout);
    out << "Application's executable directory is "
        << AQP::applicationPathOf() << "\n";
    out << "Application's images directory is "
        << AQP::applicationPathOf("images") << "\n";
    out << AQP::filenameFilter("HTML", QStringList() << "text/html")
        << "\n";
    out << AQP::filenameFilter("Audio", QStringList() << "audio/mpeg"
        << "audio/ogg") << "\n";
    out << AQP::filenameFilter("Video", QStringList() << "video/3gpp"
        << "video/dv" << "video/mpeg") << "\n";
}

