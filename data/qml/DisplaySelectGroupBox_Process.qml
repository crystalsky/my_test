import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Particles 2.0
import QtQuick.Window 2.1
import QtQuick.Controls.Styles 1.2

Rectangle
{
    width: 500
    height: 400
    color: "#5a5050"
    gradient: Gradient {
        GradientStop {
            position: 0.00;
            color: "#498d52";
        }
        GradientStop {
            position: 1.00;
            color: "#ffffff";
        }
    }
    DisplaySelectGroupBox
    {
        id:displaySelectGroupBox
        x: 5
        y: 5
    }
}
