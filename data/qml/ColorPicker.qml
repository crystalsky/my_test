import QtQuick 2.2

Rectangle
{
    id:colorpicker;
    width:50;
    height:30;
    signal colorPicked(color cr);

    function configureBorder(){
        colorpicker.border.width = colorpicker.focus ? 2 : 0;
        colorpicker.border.color = colorpicker.focus ? "#90D750" : "#808080";
    }

    MouseArea{
        anchors.fill: parent;
        onClicked: {
            colorpicker.colorPicked(colorpicker.color);
            mouse.accepted = true;
            colorpicker.focus = true;
        }
    }

    Keys.onReturnPressed: {
        colorpicker.colorPicked(colorpicker.color);
        event.accepted = true;//已处理的按键事件
    }

    Keys.onSpacePressed: {
        colorpicker.colorPicked(colorpicker.color);
        event.accepted = true;//已处理的按键事件
    }

    onFocusChanged: {
        configureBorder();
    }

    Component.onCompleted: {
        configureBorder();
    }
}

