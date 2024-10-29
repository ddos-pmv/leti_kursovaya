import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15

ApplicationWindow {
    id: mainWindow

    readonly property int interfaceWidth: 1000
    readonly property int interfaceHeight: 500

    visible: true
    width: 1400
    height: 750
    title: "F1 Observer"
    color: "transparent"

    Image {
        anchors.fill: parent
        source: "qrc:/images/bg.png"
        fillMode: Image.PreserveAspectCrop
        z: 0

        FastBlur {
            anchors.fill: parent
            source: parent
            radius: 0.5
        }

    }

    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.2
        z: 1
    }

    Rectangle {
        implicitWidth: mainWindow.interfaceWidth
        implicitHeight: mainWindow.interfaceHeight
        anchors.centerIn: parent
        z: 2
        color: "transparent"

        RowLayout {
            anchors.fill: parent
            spacing: 5

            Rectangle {
                id: sideRec

                width: 250
                Layout.fillHeight: true
                Layout.preferredWidth: 250
                color: "transparent"

                ListView {
                    anchors.fill: parent
                    model: ["Drivers", "Races", "Tracks", "", "", "", "", "", "", "", "", ""]
                    spacing: 5

                    delegate: Rectangle {
                        height: 30
                        width: ListView.view.width
                        opacity: modelData != "" ? 0.7 : 0.35
                        color: "#646464"

                        MouseArea {
                            hoverEnabled: true
                            anchors.fill: parent
                            onEntered: {
                                if(modelData!=""){
                                    parent.color = "#ff0066";
                                    parent.opacity = 1;
                                }
                            }
                            onExited: {
                                modelText.color = "white";
                                parent.color = "#646464";
                                parent.opacity = modelData!="" ? 0.7 : 0.35;
                            }
                        }

                        Text {
                            id: modelText

                            anchors.centerIn: parent
                            text: modelData
                            color: "white"
                        }

                    }

                }

            }

            Rectangle {
                id: mainRec

                color: "transparent"
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

        }

    }

}