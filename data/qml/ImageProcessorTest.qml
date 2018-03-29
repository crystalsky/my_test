import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1
import QtQuick.Controls.Styles 1.2
import QtQuick.Dialogs 1.1
import My.ImageProcessor 1.0

Rectangle
{
    visible: true;
    width: 600;
    height:480;
    color: "#121212"

    BusyIndicator{
        id:busy;
        running: false;
        anchors.centerIn: parent;
        z:2;
    }

    Label{
        id:stateLabel;
        visible:false;
        anchors.centerIn: parent;
    }

    Image
    {
        objectName: "imageViewer";
        id:imageViewer;
        asynchronous: true;
        cache:false;
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit;
        onStatusChanged: {
            if(imageViewer.state === Image.Loading)
            {
                busy.running=true;
                stateLabel.visible=false;
            }
            else if(imageViewer.state === Image.Ready)
            {
                busy.running=false;
            }
            else if(imageViewer.state===Image.Error)
            {
                busy.running = false;
                stateLabel.text="Error";
                stateLabel.visible = true;
            }
        }
    }

    ImageProcessor{
        id:processor;
        onFinished:{
            imageViewer.source="file:///" + newFile;
        }
    }

    FileDialog{
        id:fileDialog;
        title:"Please choose a Picture file...";
        nameFilters: ["Image Files (*.jpg *.png *.gif)"];
        onAccepted: {
            console.log(fileDialog.fileUrl);
            imageViewer.source=fileDialog.fileUrl;
        }
    }

    Component{
        id:btnStyle;
        ButtonStyle{
            background: Rectangle{
                implicitWidth: 60;
                implicitHeight: 25;
                border.width: control.pressed ? 2 : 1;
                border.color: (control.pressed || control.hovered)
                              ? "#00A060" : "#e0e0e0";
                radius:6;
                gradient: Gradient{
                    GradientStop{
                        position:0;
                        color: control.pressed ? "#cccccc" : "#e0e0e0";
                    }
                    GradientStop{
                        position:1;
                        color: control.pressed ? "#aaa" : "#ccc";
                    }
                }
            }
        }
    }

    Button{
        id:openfile;
        text:"打开";
        anchors.left: parent.left;
        anchors.leftMargin:6;
        anchors.top: parent.top;
        anchors.topMargin: 6;
        style: btnStyle;
        onClicked:fileDialog.open();
        z:1;
    }

    Button{
        id:quit;
        text:"退出";
        anchors.left: openfile.right;
        anchors.leftMargin:4;
        anchors.bottom: openfile.bottom;
        style: btnStyle;
        onClicked:Qt.quit();
        z:1;
    }

    Rectangle{
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: openfile.bottom;
        anchors.bottomMargin: -6;
        anchors.right: quit.right;
        anchors.rightMargin: -6;
        color:"#404040";
        opacity: 0.7;
    }

    Grid{
        id:op;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin:4;
        rows:2;
        columns: 3;
        rowSpacing: 4;
        columnSpacing: 4;
        z:1;

        Button{
            text:"柔化";
            style: btnStyle;
            onClicked: {
                busy.running = true;
                processor.process(fileDialog.fileUrl, ImageProcessor.Soften);
            }
        }

        Button{
            text:"灰度";
            style: btnStyle;
            onClicked: {
                busy.running = true;
                processor.process(fileDialog.fileUrl, ImageProcessor.Gray);
            }
        }

        Button{
            text:"浮雕";
            style: btnStyle;
            onClicked: {
                busy.running = true;
                processor.process(fileDialog.fileUrl, ImageProcessor.Emboss);
            }
        }

        Button{
            text:"黑白";
            style: btnStyle;
            onClicked: {
                busy.running = true;
                processor.process(fileDialog.fileUrl, ImageProcessor.Binarize);
            }
        }

        Button{
            text:"底片";
            style: btnStyle;
            onClicked: {
                busy.running = true;
                processor.process(fileDialog.fileUrl, ImageProcessor.Negative);
            }
        }

        Button{
            text:"锐化";
            style: btnStyle;
            onClicked: {
                busy.running = true;
                processor.process(fileDialog.fileUrl, ImageProcessor.Sharpen);
            }
        }
    }

    Rectangle{
        anchors.left: parent.left;
        anchors.top: op.top;
        anchors.topMargin: -4;
        anchors.bottom: parent.bottom;
        anchors.right: op.right;
        anchors.rightMargin: -4;
        color: "#404040";
        opacity: 0.7;
    }
}

