import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: delegateRectangel

    color: root.unHoveredColor
    opacity: root.unHoveredOpacity
    implicitHeight: root.rowHeight
    implicitWidth: listView.width
    height: root.rowHeight
    anchors.leftMargin: 5

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            delegateRectangel.color = root.hoveredColor;
            delegateRectangel.opacity = 1;
        }
        onExited: {
            delegateRectangel.color = root.unHoveredColor;
            delegateRectangel.opacity = root.unHoveredOpacity;
        }
    }

    RowLayout {
        id: rowLayout

        width: delegateRectangel.width
        height: root.rowHeight
        Layout.fillWidth: true

        Rectangle {
            color: "transparent"
            Layout.fillWidth: true
            Layout.fillHeight: true

            TextWhite {
                text: name
                anchors.leftMargin: root.defRowMargin
                anchors.verticalCenter: parent.verticalCenter
            }

        }

        Rectangle {
            color: "transparent"
            Layout.fillWidth: true
            Layout.fillHeight: true

            TextWhite {
                text: age
                anchors.verticalCenter: parent.verticalCenter
            }

        }

        Rectangle {
            color: "transparent"
            Layout.fillWidth: true
            Layout.fillHeight: true

            TextWhite {
                text: team
                anchors.verticalCenter: parent.verticalCenter
            }

        }

        Rectangle {
            color: "transparent"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumWidth: 100

            TextWhite {
                text: points
                anchors.verticalCenter: parent.verticalCenter
            }

        }

    }

}
