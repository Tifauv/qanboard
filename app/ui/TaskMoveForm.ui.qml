import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2 as Controls
import "task"
import "tools"

Item {
    id: element
    width: 300
    height: 140
    property alias originQueueRect: originQueueRect
    property alias destinationQueueRect: destinationQueueRect

    property alias taskDescriptionLbl: taskDescriptionLbl
    property alias taskHeader: taskHeader
    property alias destinationQueueLbl: destinationQueueLbl
    property alias originQueueLbl: originQueueLbl
    property alias dateTimeLbl: dateTimeLbl

    RowLayout {
        id: headerLayout

        spacing: 6

        anchors {
            top: parent.top
            topMargin: 6
            left: parent.left
            leftMargin: 8
            right: parent.right
            rightMargin: 8
        }

        Controls.Label {
            id: dateTimeLbl

            text: qsTr("24/05/2019 11h25")
            Layout.fillHeight: true
            font.pointSize: 10
            font.bold: true
            styleColor: "#666666"
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter

            Layout.fillWidth: true
        }

        Rectangle {
            id: originQueueRect

            radius: height / 2
            Layout.fillHeight: true
            implicitHeight: originQueueLbl.implicitHeight + 2 * 4
            implicitWidth: originQueueLbl.implicitWidth + 2 * radius

            border.width: 2
            border.color: "#4d4d4d"
            color: Qt.lighter(border.color, 1.8)

            Controls.Label {
                id: originQueueLbl
                text: qsTr("Backlog")
                font.pointSize: 8
                elide: Text.ElideRight
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Controls.Label {
            id: arrowLbl

            text: qsTr("➡")
            Layout.fillHeight: true
            font.pointSize: 12
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Rectangle {
            id: destinationQueueRect

            radius: height / 2
            Layout.fillHeight: true
            implicitHeight: destinationQueueLbl.implicitHeight + 2 * 4
            implicitWidth: destinationQueueLbl.implicitWidth + 2 * radius

            border.width: 2
            border.color: "#1d99f3"
            color: Qt.lighter(border.color, 1.8)

            Controls.Label {
                id: destinationQueueLbl
                text: qsTr("Selected")
                font.pointSize: 8
                elide: Text.ElideRight
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Rectangle {
        id: taskRect
        color: "#ffffff"
        border.color: "#cccccc"
        border.width: 1
        anchors.rightMargin: 8
        anchors.leftMargin: 16
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: headerLayout.bottom
        anchors.topMargin: 4

        TaskHeader {
            id: taskHeader
            anchors.right: parent.right
            anchors.rightMargin: 2
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.top: parent.top
            anchors.topMargin: 2
        }

        Controls.Label {
            id: taskDescriptionLbl
            text: qsTr("Description")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            elide: Text.ElideRight
            anchors.right: parent.right
            anchors.rightMargin: 2
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.top: taskHeader.bottom
            anchors.topMargin: 2
        }
    }
}




/*##^## Designer {
    D{i:0;width:300}
}
 ##^##*/
