import QtQuick 2.2
import QtQuick.Controls 1.2

Rectangle
{
    width:400;
    height:320;
    BusyIndicator{
        id:busy;
        running: true;
        anchors.centerIn: parent;
        z:2;
    }

    Text
    {
     id:stateLable;
     visible:false;
     anchors.centerIn: parent;
     z:3;
    }

    Image
    {
        id:img;
        asynchronous: true;
        cache:false;
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit;
        onStatusChanged: {
            if(img.state === Image.Loading)
            {
                busy.running=true;
                stateLable.visible=false;
            }
            else if(img.state === Image.Ready)
            {
                busy.running=false;
            }
            else if(img.state===Image.Error)
            {
                busy.running = false;
                stateLable.text="Error";
                stateLable.visible = true;
            }
        }
    }
    Component.onCompleted: {
        img.source="http://image.cuncunle.com/images/editorimages/2013/01/01/19/20130001194920468.jpg"
    }
}

