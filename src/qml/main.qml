import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Hello QML"

    Button {
        text: "Click Me"
        anchors.centerIn: parent
    }
    Button {
        text: "Fuck Me"
    }
}