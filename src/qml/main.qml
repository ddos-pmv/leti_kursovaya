import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

ApplicationWindow {
    id: root

    readonly property int interfaceWidth: 1000
    readonly property int interfaceHeight: 500
    readonly property int rowHeight: 30
    readonly property int defRowMargin: 5
    readonly property string unHoveredColor: "#646464"
    readonly property real unHoveredOpacity: 0.8
    readonly property real hoveredOpacity: 1
    readonly property string hoveredColor: "#ff0066"

    visible: true
    width: 1400
    height: 750
    title: "F1 Observer"
    color: "transparent"

    Image {
        id: bgImage

        anchors.fill: parent
        source: "../public/bg.png"
        fillMode: Image.PreserveAspectCrop
        z: 0
    }

    FastBlur {
        anchors.fill: bgImage
        source: bgImage
        radius: 20
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

                    property int prevIndex: -1

                    anchors.fill: parent
                    model: ["Drivers", "Races", "Tracks"]
                    spacing: root.defRowMargin

                    delegate: Rectangle {
                        id: delegator

                        height: root.rowHeight
                        width: ListView.view.width
                        color: sideMenu.currentIndex === index ? "white" : root.unHoveredColor
                        opacity: sideMenu.currentIndex === index ? 1 : root.unHoveredOpacity
                        focus: true

                        MouseArea {
                            hoverEnabled: true
                            anchors.fill: parent
                            onEntered: {
                                if (sideMenu.currentIndex !== index) {
                                    parent.color = root.hoveredColor;
                                    parent.opacity = root.hoveredOpacity;
                                }
                            }
                            onExited: {

                                    parent.color = root.unHoveredColor;
                                    parent.opacity = root.unHoveredOpacity;

                            }
                            onClicked: {
                                sideMenu.currentIndex = index;
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: modelData
                            color: sideMenu.currentIndex === index ? "black" : "white"
                        }

                    }

                }

            }

            StackLayout {
                id: stackLayout

                Layout.fillHeight: true
                Layout.fillWidth: true
                currentIndex: sideMenu.currentIndex

                ListView {
                    id: listView

                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: driverModel
                    spacing: root.defRowMargin

                    delegate: DriverTableDelegate{}

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
