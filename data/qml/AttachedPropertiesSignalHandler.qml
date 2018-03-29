import QtQuick 2.2
Item{
    width: 100;
    height: 100;

    focus:true;
    Keys.enabled: true;
    Keys.onEscapePressed: console.log("onEscapePressed!");
}
