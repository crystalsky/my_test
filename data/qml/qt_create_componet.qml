import QtQuick 2.2
import QtQuick.Controls 1.2

Rectangle
{
    width:400;
    height:320;
    color:"#EEEEEE";
    id:rootItem;
    property var count: 0
    property var colorPickerShow: false;
    property Component component: null;
    Text
    {
     id:coloredText;
     visible:true;
     anchors{
         centerIn: parent;
     }
     text:"Hello World!";
     color: "blue";
     font.pixelSize: 32;
    }

    function changeTextColor(cr)
    {
        coloredText.color = cr;
    }

    function createColorPicker(cr)
    {
        if(rootItem.component == null)
        {
            rootItem.component = Qt.createComponent("ColorPicker.qml");
        }

        var colorpicker;
        if(rootItem.component.status == Component.Ready){
            colorpicker = rootItem.component.createObject(rootItem,
                                                          {"color":cr, "x":rootItem.count * 55, "y":10});
            colorpicker.colorPicked.connect(rootItem.changeTextColor);
        }

        ++rootItem.count;
    }

    Button{
        id:ctrlButton;
        text:"Add";
        anchors{
            left: parent.left;
            leftMargin: 4;
            bottom: parent.bottom;
            bottomMargin: 5;
        }

        onClicked:{
            createColorPicker(Qt.rgba(Math.random(), Math.random(), Math.random(), 1));
        }
    }
}

