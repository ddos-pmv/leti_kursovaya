import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15

ApplicationWindow {
    id: root

    readonly property int interfaceWidth: 1000
    readonly property int interfaceHeight: 500
    readonly property int rowHeight: 30
    readonly property int defRowMargin: 5

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
            radius: 4
        }

    }

    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.2
        z: 1
    }

    Rectangle {
        implicitWidth: root.interfaceWidth
        implicitHeight: root.interfaceHeight
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
                    id: sideMenu

                    anchors.fill: parent
                    model: ["Drivers", "Races", "Tracks"]
                    spacing: root.defRowMargin

                    delegate: Rectangle {
                        id: delegator

                        height: root.rowHeight
                        width: ListView.view.width
                        color: "#646464"
                        opacity: 0.8
                        focus: true

                        MouseArea {
                            hoverEnabled: true
                            anchors.fill: parent
                            onEntered: {
                                if (modelData != "") {
                                    parent.color = "#ff0066";
                                    parent.opacity = 1;
                                }
                            }
                            onExited: {
                                parent.color = "#646464";
                                parent.opacity = 0.8;
                            }
                            onClicked: {
                                sideMenu.currentIndex = index
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: modelData
                            color: "white"
                        }

                    }

                }

            }

            StackLayout{
                id: stackLayout
                Layout.fillHeight: true
                Layout.fillWidth: true
                currentIndex: sideMenu.currentIndex


                Text{
                    text: "Drivers"
                }

                Text {
                    text: "Hello"
                }

                Text {
                    text: "There"
                }
            }

        }

    }

}
