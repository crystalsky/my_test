import QtQuick 2.2
import QtQuick.Controls 1.2

Rectangle
{
    id:rectAll;
    width:800;
    height:320;

    function slotOutPutName(name)
    {
        coloredText.text = name + "Item Clicked!";
    }

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


    signal signal_connect_signal_signal(string colorstr);
    onSignal_connect_signal_signal: {
        text2.text = colorstr + " signal_connect_signal_signal";
    }

    Text
    {
     id:text2;
     visible:true;
     anchors{
         horizontalCenter: parent.horizontalCenter;
         top:coloredText.bottom;
         topMargin: 20;
     }
     text:"text2";
     color: "black";
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

         property string strName;
         signal outPutName(string name);

         property string strSCSS;
         signal s_c_s_s(string name);
         MouseArea{
             id:ma;
             anchors.fill: parent;
             onPressed: {
                 colorPicker.colorPicked(colorPicker.color);
                 colorPicker.outPutName(colorPicker.strName);
                 colorPicker.s_c_s_s(colorPicker.strSCSS);
             }
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
            item.strName = "redName";
            item.strSCSS = "red_s_c_s_s";
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
            item.strName = "blueName";
            item.strSCSS = "blue_s_c_s_s";
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

    Component.onCompleted: {
        redLoader.item.outPutName.connect(slotOutPutName);
        blueLoader.item.outPutName.connect(slotOutPutName);

        redLoader.item.s_c_s_s.connect(signal_connect_signal_signal);
        blueLoader.item.s_c_s_s.connect(signal_connect_signal_signal);

    }

    Rectangle{
        id:textMouseButton;
        width:200;
        height:50;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
        color:"#FF992233";
        Text
        {
         id:testMouseButton;
         visible:true;
         anchors.centerIn: parent;
         text:"TestMouseButtonArea";
         color: "black";
         font.pixelSize: 13;
         font.underline: true;
         z:1;
        }

        MouseArea{
            anchors.fill: parent;
            acceptedButtons: Qt.LeftButton | Qt.RightButton;
            onClicked: {
                if(mouse.button == Qt.LeftButton)
                {
                    rectAll.color = "yellow";
                }
                else if(mouse.button == Qt.RightButton)
                {
                    rectAll.color = "green";
                }
            }

            onDoubleClicked:{
                rectAll.color = "gray";
            }
        }
    }


}

