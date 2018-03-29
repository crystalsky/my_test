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

Item{
    id:sattliteTime
    width: 322; height: 71
    property string sattliteName: "Sattlite"

    Rectangle{
        id:totalRect
        width: parent.width
        height: parent.height
        color: "black"
        anchors.fill: parent

        //标题
        Rectangle{
            id:titleSattliteStationRect
            width:parent.width
            height: 20
            color: "white"
            border.color: "black"
            Text {
                color: "black"
                anchors {
                    topMargin: 5
                    left: parent.left
                    leftMargin: 5
                }
                text: sattliteName
                font.family: "华文宋体"
                font.pointSize: 12
                font.bold: true
                style: Text.Raised
            }
        }

        //下部时隙状态
        Rectangle{
            id: timeCellsRect
            anchors {
                top: titleSattliteStationRect.bottom
                topMargin: 4
                left: parent.left
                leftMargin: 2
            }
            //height: parent.height - titleSattliteStationRect.height

            Column{
                anchors.left: parent.left
                anchors.leftMargin: 2
                anchors.verticalCenter:parent.verticalCenter
                spacing: 3

                SattliteTimeCells{
                    id:sat1
                }

                SattliteTimeCells{
                    id:sat2
                }
            }

            Component.onCompleted: {
                sat1.sattliteName = "SAT1"
                sat2.sattliteName = "SAT2"
            }
        }

        Component.onCompleted: {
        }
    }
}




//![0]
