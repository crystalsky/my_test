import QtQuick 2.2
import QtQuick.Controls 1.2

Rectangle
{
    width:400;
    height:320;


    Text
    {
     id:coloredText;
     visible:true;
     anchors{
         horizontalCenter: parent.horizontalCenter;
         top:parent.top;
         topMargin: 20;
     }
     text:"text1";
     color: "blue";
     font.pixelSize: 32;
     z:3;
    }

    Component{
     id:colorComponent;
     Rectangle{
         id:colorPicker;
         width:50;
         height:30;
         signal colorPicked(color cr);
         MouseArea{
             anchors.fill: parent;
             onPressed: colorPicker.colorPicked(colorPicker.color);
         }
     }
    }

    Loader{
        id:redLoader;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        sourceComponent: colorComponent;
        onLoaded:{
            item.color = "red";
        }
    }

    Loader{
        id:blueLoader;
        anchors.left: redLoader.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        sourceComponent: colorComponent;
        onLoaded:{
            item.color = "blue";
        }
    }

    Connections{
        target: redLoader.item;
        onColorPicked:{
            coloredText.color = cr;
        }
    }

    Connections{
        target: blueLoader.item;
        onColorPicked:{
            coloredText.color = cr;
        }
    }
}

