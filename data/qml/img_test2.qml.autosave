import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1
import QtQuick.Controls.Styles 1.2
import QtQuick.Dialogs 1.1

Window
{
    visible: true;
    width: 600;
    height:480;
    minimumWidth: 480;
    minimumHeight: 380;

    BusyIndicator{
        id:busy;
        running: false;
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

    Button{
        id:openfile;
        text:"Open";
        anchors.left: parent.left;
        anchors.leftMargin:8;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 8;
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 70
                implicitHeight: 25
                color:control.hovered? "#c0c0c0" : "#a0a0a0";
                border.width: control.pressed ? 2 : 1
                border.color: (control.hovered || control.pressed) ?
                                  "green" : "#888888";
                radius: 4
                gradient: Gradient {
                    GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                    GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                }
            }
        }
        onClicked:fileDialog.open();
        z:4;
    }

    Text{
        id:imagePath;
        anchors.left: openfile.right;
        anchors.leftMargin:8;
        anchors.verticalCenter: openfile.verticalCenter;
        font.pixelSize: 18;

    }

    FileDialog{
        id:fileDialog;
        title:"Please choose a Picture file...";
        nameFilters: ["Image Files (*.jpg *.png *.gif)"];
        onAccepted: {
            img.source=fileDialog.fileUrl;
            var imageFile = new String(fileDialog.fileUrl);
            imagePath.text = imageFile.slice(8);

            console.log(typeof imageFile);
        }
    }
}

