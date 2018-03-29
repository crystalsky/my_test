/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
//![0]
import QtQuick 2.0
import QtQuick 2.0 as Quick
Item{
    width: 400; height: 800

    Quick.Rectangle{
        id:titleRect
        width:parent.width
        height: 30
        border.color: "red"
        Text {
            color: "#e81d1d"
            anchors { horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter}
            text: "Property Binding"
            font.family: "华文宋体"
            font.bold: true
            font.pointSize: 13
            style: Text.Raised
        }
    }

    Rectangle{
        anchors.top: titleRect.bottom
        anchors.topMargin: 5
        width: parent.width
        height: parent.height - titleRect.height
        border.color: "green"

        Rectangle{
            id:rect1
            width:parent.width - 10
            height: 200
            border.color: "blue"
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            Column {
                id: column
                width: 200
                height: 200

                Rectangle {
                    id: topRect
                    width: Math.max(bottomRect.width, parent.width/2)
                    height: (parent.height / 3) + 10
                    color: "yellow"
                    anchors.topMargin: parent.top + 50
                    TextInput {
                        id: myTextInput
                        text: "Hello QML!"
                    }
                }

                Rectangle {
                    id: bottomRect
                    width: 100
                    height: 50
                    color: myTextInput.text.length <= 10 ? "red" : "blue"
                }
            }
        }

        Rectangle{
            id:rect2
            width:100
            height: width / 2
            anchors.top: rect1.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 5
            border.color: "green"

            focus: true
            Keys.onUpPressed: {
                height += 10
            }
            Keys.onDownPressed: {
                height -= 10
            }
        }


    }

}



//![0]
