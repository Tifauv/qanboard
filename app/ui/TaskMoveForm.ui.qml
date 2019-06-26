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
		verticalAlignment: Text.AlignVCenter
		anchors.bottom: originQueueRect.bottom
		font.pointSize: 10
		elide: Text.ElideRight
		styleColor: "#666666"
		font.bold: true
		anchors.left: parent.left
		anchors.leftMargin: 8
		anchors.top: originQueueRect.top
	}

	Rectangle {
		id: originQueueRect

		anchors {
			top: parent.top
			topMargin: 6
			left: dateTimeLbl.right
			leftMargin: 16
		}

		radius: height / 2
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

		anchors {
			verticalCenter: originQueueRect.verticalCenter
			left: originQueueRect.right
			leftMargin: 6
			right: destinationQueueRect.left
			rightMargin: 6
		}

		text: qsTr("➡")
		font.pointSize: 12
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
	}

	Rectangle {
		id: destinationQueueRect
		height: 33

		anchors {
			right: parent.right
			rightMargin: 8
		}

		radius: height / 2
		anchors.top: originQueueRect.top
		anchors.verticalCenter: originQueueRect.verticalCenter
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
			anchors.verticalCenter: parent.verticalCenter
			anchors.horizontalCenter: parent.horizontalCenter
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



