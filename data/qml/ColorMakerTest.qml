import QtQuick 2.2
import QtQuick.Controls 1.2
import example.qt.ColorMaker 1.0

Rectangle
{
    id:rectAll;
    width:480;
    height:320;

    Text{
        id:timeLable;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.top: parent.top;
        anchors.topMargin: 4;
        font.pixelSize: 25;
    }

    ColorMaker{
        id:colorMaker;
        color:Qt.green;
    }

    Rectangle{
        id:colorRect;
        anchors.centerIn: parent;
        width:200;
        height:200;
        color:"blue";
    }

    Button{
        id: start;
        text: "start";
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        onClicked:{
            colorMaker.start();
            start.enabled = false;
            stop.enabled = true;
        }
    }

    Button{
        id: stop;
        text: "stop";
        anchors.left: start.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        onClicked:{
            colorMaker.stop();
            start.enabled = true;
            stop.enabled = false;
        }
    }

    function changeAlgorithm(button, algorithm){
        switch(algorithm)
        {
        case 0:
            button.text = "RandomRGB";
            break;
        case 1:
            button.text = "RandomGreen";
            break;
        case 2:
            button.text = "RandomRed";
            break;
        case 3:
            button.text = "RandomBlue";
            break;
        case 4:
            button.text = "LinearIncrease";
            break;
        }
    }

    Button{
        id: colorAlgorithm;
        text: "RandomRGB";
        anchors.left: stop.right;
        anchors.leftMargin: 10;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        onClicked:{
            var algorithm = (colorMaker.algorithm() + 1) % 5;
            changeAlgorithm(colorAlgorithm, algorithm);
            colorMaker.setAlgorithm(algorithm);
        }
    }

    Component.onCompleted: {
        start.enabled = true;
        stop.enabled = false;
        colorMaker.color = Qt.rgba(0, 180, 120, 255);
        colorMaker.setAlgorithm(ColorMaker.LinearIncrease);
        changeAlgorithm(colorAlgorithm, colorMaker.algorithm());
    }

    Connections{
        target: colorMaker;
        onCurrentTime:{
            timeLable.text = strTime;
            timeLable.color = colorMaker.timeColor;
        }
    }

    Connections{
        target: colorMaker;
        onColorChanged:{
            colorRect.color = color;
        }
    }
}

