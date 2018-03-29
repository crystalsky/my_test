import QtQuick 2.2
import QtQuick.Controls 1.2

Rectangle
{
    width:400;
    height:320;
    color:"#EEEEEE";
    id:rootItem;
    property var colorPickerShow: false;

    Text
    {
     id:coloredText;
     visible:true;
     anchors{
         horizontalCenter: parent.horizontalCenter;
         top:parent.top;
         topMargin: 20;
     }
     text:"Hello World!";
     color: "blue";
     font.pixelSize: 32;
    }

    Button{
        id:ctrlButton;
        text:"Show";
        anchors{
            left: parent.left;
            leftMargin: 4;
            bottom: parent.bottom;
            bottomMargin: 5;
        }

        onClicked:{
            if(rootItem.colorPickerShow){
                redLoader.sourceComponent = undefined;
                blueLoader.sourceComponent = undefined;
                redLoader.source = "";
                blueLoader.source = "";
                rootItem.colorPickerShow = false;
                ctrlButton.text = "Show";
                console.log("Onclicked!!!");
            }
            else
            {
                redLoader.source = "ColorPicker.qml";
                redLoader.item.colorPicked.connect(onPickedRed);

                blueLoader.source = "ColorPicker.qml";
                blueLoader.item.colorPicked.connect(onPickedBlue);

                rootItem.colorPickerShow = true;
                ctrlButton.text = "Hide";
                redLoader.focus = true;
            }
        }
    }

    Loader{
        id:redLoader;
        anchors.left: ctrlButton.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;

        KeyNavigation.right: blueLoader;
        KeyNavigation.tab: blueLoader;
        onLoaded:{
            if(item != null){
                item.color = "red";
                item.focus = true;
            }
        }

        onFocusChanged: {
            if(item != null){
                item.focus = focus;
            }
        }
    }

    Loader{
        id:blueLoader;
        anchors.left: redLoader.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;

        KeyNavigation.left: redLoader;
        KeyNavigation.tab: redLoader;

        onLoaded:{
            if(item != null){
                item.color = "blue";
            }
        }

        onFocusChanged: {
            if(item != null){
                item.focus = focus;
            }
        }
    }

    function onPickedRed(cr){
        coloredText.color = cr;
        if(!redLoader.focus){
            redLoader.focus = true;
            blueLoader.focus = false;
        }
    }

    function onPickedBlue(cr){
        coloredText.color = cr;
        if(!blueLoader.focus){
            blueLoader.focus = true;
            redLoader.focus = false;
        }
    }
}

