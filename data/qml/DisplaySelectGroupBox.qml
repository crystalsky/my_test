import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Particles 2.0
import QtQuick.Window 2.1
import QtQuick.Controls.Styles 1.2

Rectangle
{
    property var screenType: 0
    signal screenDisplayTypeChanged(int nType)
    onScreenTypeChanged:
    {
        console.debug("onScreenTypeChanged " + screenType);
        screenDisplayTypeChanged(screenType);
    }

    GroupBox 
    {
        id:displayGroupBox
        Column 
        {
            ExclusiveGroup { id: group }
            RadioButton
            {
                text: qsTr("二维")
                id:radio2D
                checked: true
                exclusiveGroup: group
                style: RadioButtonStyle
                {
                    background: Rectangle
                    {
                        color: "#66EEEEEE"
                    }
                }
                onCheckedChanged:
                {
                    if(checked)
                    {
                        screenType = 2;
                    }
                }
            }
            RadioButton
            {
                text: qsTr("三维")
                id:radio3D
                exclusiveGroup: group
                style: RadioButtonStyle
                {
                    background: Rectangle
                    {
                        color: "#66EEEEEE"
                    }
                }
                onCheckedChanged:
                {
                    if(checked)
                    {
                        screenType = 3;
                    }
                }
            }
            RadioButton 
            {
                text: "二三维"
                id:radio2D3D
                style: RadioButtonStyle 
                {
                    background: Rectangle 
                    {                           
                        color: "#66EEEEEE"                                  
                    }
                }
                exclusiveGroup: group   
                onCheckedChanged: 
                {
                   if(checked)
                   {
                      screenType = 0;
                   }
                }
            }
        }
    }
}
