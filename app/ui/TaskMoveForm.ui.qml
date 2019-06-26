import QtQuick 2.9
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

    Controls.Label {
        id: dateTimeLbl
        text: qsTr("24/05/2019 11h25")
        elide: Text.ElideRight
        styleColor: "#666666"
        font.bold: true
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 8
    }

    Rectangle {
        id: taskRect
        color: "#ffffff"
        border.color: "#cccccc"
        border.width: 1
        anchors.rightMargin: 16
        anchors.leftMargin: 16
        anchors.bottom: originQueueRect.top
        anchors.bottomMargin: 4
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: dateTimeLbl.bottom
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
            text: qsTr("Label")
            elide: Text.ElideRight
            anchors.right: parent.right
            anchors.rightMargin: 2
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            anchors.top: taskHeader.bottom
            anchors.topMargin: 2
        }
    }

    Rectangle {
        id: originQueueRect
        implicitHeight: originQueueLbl.implicitHeight + 2 * 4
        color: Qt.lighter(border.color, 1.8)
        radius: height / 2
        anchors.leftMargin: 16
        border.width: 2
        border.color: "#4d4d4d"
        anchors.right: arrowLbl.left
        anchors.rightMargin: 6
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.left: parent.left

        Controls.Label {
            id: originQueueLbl
            text: qsTr("Backlog")
            elide: Text.ElideRight
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Controls.Label {
        id: arrowLbl
        text: qsTr("➡")
        font.pointSize: 12
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: originQueueRect.verticalCenter
    }

    Rectangle {
        id: destinationQueueRect
        implicitHeight: destinationQueueLbl.implicitHeight + 2 * 4
        color: Qt.lighter(border.color, 1.8)
        radius: height / 2
        border.width: 2
        border.color: "#1d99f3"
        anchors.right: parent.right
        anchors.rightMargin: 16
        anchors.leftMargin: 6
        anchors.bottomMargin: 8
        anchors.bottom: parent.bottom
        anchors.left: arrowLbl.right

        Controls.Label {
            id: destinationQueueLbl
            text: qsTr("Selected")
            elide: Text.ElideRight
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}




/*##^## Designer {
    D{i:5;anchors_height:33;anchors_width:190;anchors_x:202;anchors_y:8}D{i:8;anchors_height:33;anchors_width:190;anchors_x:202;anchors_y:8}
}
 ##^##*/
