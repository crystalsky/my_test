import QtQuick 2.2
import QtQuick.Controls 1.2

Rectangle
{
    width:400;
    height:320;


    Text
    {
     id:text1;
     visible:true;
     anchors{
         horizontalCenter: parent.horizontalCenter;
         top:parent.top;
         topMargin: 20;


     }
     text:"text1";
     color: "blue";
     font.pixelSize: 20;
     z:3;
    }

    Text
    {
     id:text2;
     visible:true;
     anchors{
         horizontalCenter: parent.horizontalCenter;
         top:text1.bottom;
         topMargin: 8;


     }
     text:"text2";
     color: "red";
     font.pixelSize: 20;
     z:3;
    }

    Button{
        id:changeButton;
        anchors{
            horizontalCenter: parent.horizontalCenter;
            top:text2.bottom;
            topMargin: 8;
        }
        text:"Click Me!";
    }

    Connections{
        target: changeButton;
        onClicked:{
            text1.color = Qt.rgba(Math.random(),
                                  Math.random(),
                                  Math.random(),
                                  Math.random());
            text2.color = Qt.rgba(Math.random(),
                                  Math.random(),
                                  Math.random(),
                                  Math.random());
        }
    }

    Component.onCompleted: {
        console.log("Component.onCompleted!");
    }
}

