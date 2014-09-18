import QtQuick 1.1

Rectangle {
	id: task
	width: 180
	height: 80
	color: "#eeeeee"

	property int taskId: 1
	property string assignee: "Assignee"
	property string description: "Description"

	Column {
		id: mainLayout
		anchors.rightMargin: 5
		anchors.leftMargin: 5
		anchors.bottomMargin: 5
		anchors.topMargin: 5
		anchors.fill: parent

		Row {
			id: topLayout
			height: 20
			anchors.right: parent.right
			anchors.left: parent.left

			Text {
				id: taskIdLbl
				text: qsTr("#%1").arg(taskId)
				anchors.verticalCenter: parent.verticalCenter
				font.bold: true
				font.pointSize: 8
			}

			Text {
				id: assigneeLbl
				text: qsTr(" - Assigned to %1").arg(assignee)
				font.pointSize: 8
				anchors.verticalCenter: parent.verticalCenter
			}
		 }

		Text {
			id: descriptionLbl
			text: qsTr(description)
			wrapMode: Text.WordWrap
			font.pointSize: 9
			anchors.right: parent.right
			anchors.rightMargin: 0
			anchors.left: parent.left
			anchors.leftMargin: 0
			font.pixelSize: 12
		}
	}

	states: [
		State {
			name: "notAssigned"
			when: assignee == ""
			PropertyChanges {
				target: assigneeLbl
				text: qsTr(" - Nobody assigned")
				color: "#999999"
				font.italic: true
			}
		}
	]
}
