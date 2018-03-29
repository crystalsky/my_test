import QtQuick 2.2

Rectangle
{
    id:rectAll;
    width:480;
    height:320;
    color:"#EEEEEE";

    Text
    {
     id:coloredText;
     visible:true;
     anchors{
         horizontalCenter: parent.horizontalCenter;
         top:parent.top;
         topMargin: 20;
     }
     text:"Hello World!!!";
     color: "blue";
     font.pixelSize: 32;
    }

    function setTextColor(clr)
    {
        coloredText.color = clr;
    }

    ColorPicker{
        id:red_colorPicker;
        color:"red";
        focus:true;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4
        KeyNavigation.right: blue_colorPicker;
        KeyNavigation.tab: blue_colorPicker;
        onColorPicked: {
            coloredText.color = cr;
        }
    }

    ColorPicker{
        id:blue_colorPicker;
        color:"blue";
        focus:true;
        anchors.left: red_colorPicker.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4

        KeyNavigation.left: red_colorPicker;
        KeyNavigation.right: blue_colorPicker;
        KeyNavigation.tab: pink_colorPicker;
        onColorPicked: {
            coloredText.color = cr;
        }
    }

    ColorPicker{
        id:pink_colorPicker;
        color:"pink";
        focus:true;
        anchors.left: blue_colorPicker.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4

        KeyNavigation.left: blue_colorPicker;
        KeyNavigation.tab: red_colorPicker;
    }

    Component.onCompleted: {
        red_colorPicker.colorPicked.connect(setTextColor);
        blue_colorPicker.colorPicked.connect(setTextColor);
        pink_colorPicker.colorPicked.connect(setTextColor);
    }
}

