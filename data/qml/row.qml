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

    function setTextColor(cr)
    {
        coloredText.color = cr;
    }

    Row{
        anchors{
            left: parent.left;
            leftMargin: 5;
            bottom: parent.bottom;
            bottomMargin: 5;
        }
        spacing: 5;

        ColorPicker{
            color: Qt.rgba(Math.random(), Math.random(), Math.random(), Math.random());
            onColorPicked: setTextColor(cr);
        }

        ColorPicker{
            color: Qt.rgba(Math.random(), Math.random(), Math.random(), Math.random());
            onColorPicked: setTextColor(cr);
        }

        ColorPicker{
            color: Qt.rgba(Math.random(), Math.random(), Math.random(), Math.random());
            onColorPicked: setTextColor(cr);
        }

        ColorPicker{
            color: Qt.rgba(Math.random(), Math.random(), Math.random(), Math.random());
            onColorPicked: setTextColor(cr);
        }
    }
}

