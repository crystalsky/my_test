import QtQuick 2.0

Item {
    width: 400
    height: 800


    Rectangle {
        id: titleRect
        width: parent.width
        height: 30
        border.color: "red"
        Text {
            color: "#e81d1d"
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            text: "Base Info"
            font.family: "华文宋体"
            font.bold: true
            font.pointSize: 13
            style: Text.Raised
        }
    }

    Rectangle {
        anchors.top: titleRect.bottom
        anchors.topMargin: 5
        width: parent.width
        height: parent.height - titleRect.height
        border.color: "green"
        focus: true
        Keys.enabled: true
        Keys.onEscapePressed: Qt.quit()
        Keys.onBackPressed: Qt.quit()
        Keys.onPressed: {
            switch (event.key) {
            case Qt.Key_0:

            case Qt.Key_1:

            case Qt.Key_2:

            case Qt.Key_3:

            case Qt.Key_4:

            case Qt.Key_5:

            case Qt.Key_6:

            case Qt.Key_7:

            case Qt.Key_8:

            case Qt.Key_9:
                event.accepted = true
                keyView.text = event.key - Qt.Key_0;
                console.log("pressed The " + event.key);
                break
            }
        }
        Text{
            id:keyView;
            font.bold: true;
            font.pixelSize: 25;
            text:qsTr("text");
            anchors.centerIn: parent;
        }

        Column {
            SquareButton {
                width: 50
                height: 50
            }
            SquareButton {
                x: 50
                color: "blue"
            }
            SquareButton {
                radius: 10
            }
            SquareButton {
                id: spcialItem
                x: 25
                radius: 10
                onButtonClicked: {
                    console.log("Clicked", xpos, yPos)
                    randomizeColor()
                }
                Text {
                    anchors.centerIn: parent.Center
                    text: squareButton.pressed ? "Down" : "Up"
                }

                onColorChanged: {
                    console.log("spcialItem Color Changed", color)
                }
            }
            SquareButton {
                id: spcialItem1
                x: 30
                width: 30
                radius: 10
                property int state

                function getRamdomState() {
                    return Math.random() * 1000 % 4
                }

                function getcolor() {
                    return Qt.rgba(Math.random(), Math.random(),
                                   Math.random(), 1)
                }

                onButtonClicked: {
                    console.log("Clicked", xpos, yPos)
                    randomizeColor()
                    state = getRamdomState()
                    spcialItem.color = getcolor()
                }

                onStateChanged: {
                    console.log("StateChanged", state)
                }

                Text {
                    anchors.centerIn: parent.Center
                    text: squareButton.pressed ? "Down" : "Up"
                }
            }
        }
    }
}
//![0]

