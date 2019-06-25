import QtQuick 2.4
import QtQuick.Controls 2.3
import "task"
import "tools"

Item {
	id: element
	width: 300
	height: 120
	property alias taskDescriptionLbl: taskDescriptionLbl
	property alias taskHeader: taskHeader
	property alias destinationQueueLbl: destinationQueueLbl
	property alias originQueueLbl: originQueueLbl
	property alias dateTimeLbl: dateTimeLbl

	Label {
		id: dateTimeLbl
		text: qsTr("24/05/2019 11h25")
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
		anchors.rightMargin: destinationQueueRect.radius
		anchors.leftMargin: originQueueRect.radius
		anchors.bottom: originQueueRect.top
		anchors.bottomMargin: 4
		anchors.right: destinationQueueRect.right
		anchors.left: originQueueRect.left
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

		Label {
			id: taskDescriptionLbl
			text: qsTr("Label")
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
		y: 8
		height: childrenRect.height + 2 * 4
		color: Qt.lighter("#4d4d4d", 1.6)
		radius: height / 2
		anchors.leftMargin: 8
		border.width: 2
		border.color: "#4d4d4d"
		anchors.right: arrowLbl.left
		anchors.rightMargin: 0
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 8
		anchors.left: parent.left

		Label {
			id: originQueueLbl
			x: 80
			y: 11
			text: qsTr("Backlog")
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.verticalCenter: parent.verticalCenter
		}
	}

	Label {
		id: arrowLbl
		x: 154
		y: 74
		text: qsTr("➡")
		font.pointSize: 12
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: originQueueRect.verticalCenter
	}

	Rectangle {
		id: destinationQueueRect
		x: -9
		y: 59
		height: childrenRect.height + 2 * 4
		color: Qt.lighter("#1d99f3", 1.6)
		radius: height / 2
		border.width: 2
		border.color: "#1d99f3"
		anchors.right: parent.right
		anchors.rightMargin: 8
		anchors.leftMargin: 0
		anchors.bottomMargin: 8
		anchors.bottom: parent.bottom
		anchors.left: arrowLbl.right
		Label {
			id: destinationQueueLbl
			x: 80
			y: 11
			text: qsTr("Selected")
			anchors.verticalCenter: parent.verticalCenter
			anchors.verticalCenterOffset: 0
			anchors.horizontalCenterOffset: 0
			anchors.horizontalCenter: parent.horizontalCenter
		}
	}
}




/*##^## Designer {
	D{i:5;anchors_height:33;anchors_width:190;anchors_x:202;anchors_y:8}D{i:8;anchors_height:33;anchors_width:190;anchors_x:202;anchors_y:8}
}
 ##^##*/
