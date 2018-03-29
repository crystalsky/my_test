import QtQuick 2.0 as Quick
import QtQuick.Controls 1.2
Quick.Rectangle{
    id:root
    width: 300
    height: 600
    color: "red"

    Quick.Text{
       id:normal;
       wrapMode: Text.WordWrap;
       font{
           bold: true;
           pixelSize: 24;
           underline: true;

       }
       text:"normal text";
       anchors{
           left: root.left;
           leftMargin: 20;
           top: parent.top;
       }


       color:"blue";
    }

    Quick.Text{
       id:raised;
       wrapMode: Text.WordWrap;
       font{
           bold: true;
           pixelSize: 24;
           underline: true;

       }
       text:"normal text";
       anchors{
           left: root.left;
           leftMargin: 20;
           top: normal.bottom;
           topMargin: 4;
       }
        style: Text.Raised;
        styleColor: "#AAAAAA"
       color:"yellow";
    }

    Quick.Text{
       id:outline;
       wrapMode: Text.WordWrap;
       font{
           bold: true;
           pixelSize: 24;
           underline: true;

       }
       text:"normal text";
       anchors{
           left: root.left;
           leftMargin: 20;
           top: raised.bottom;
           topMargin: 4;
       }
        style: Text.OutLine;
       color:"yellow";
    }

    Quick.Text{
       id:sunken;
       wrapMode: Text.WordWrap;
       font{
           bold: true;
           pixelSize: 24;
           underline: true;

       }
       text:"normal text";
       anchors{
           left: root.left;
           leftMargin: 20;
           top: outline.bottom;
           topMargin: 4;
       }
        style: Text.Sunken;
        styleColor: "#A00000"
       color:"yellow";
    }

    Button{
        text:"Quit";
        checkable:true;
        anchors{
            centerIn: parent;
            top: sunken.bottom;
            topMargin: 4;

            }
        onClicked:{
            console.log("Button Clicked!");
        }
    }

}
