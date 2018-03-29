import QtQuick 2.0 as Quick

Quick.Rectangle{
    id:root
    width: 100
    height: 100
    color: "red"

    property bool pressed: mouseArea.pressed;

    signal buttonClicked(real xpos, real yPos)

    function randomizeColor(){
        root.color = Qt.rgba(Math.random(), Math.random(), Math.random(), 1)
    }

    Quick.MouseArea{
        id:mouseArea
        anchors.fill: parent
        onClicked: root.buttonClicked(mouse.x, mouse.y)
    }
}
