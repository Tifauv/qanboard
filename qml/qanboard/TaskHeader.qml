import QtQuick 1.1

Rectangle {
	id: taskHeader
	height: 20
	color: "#00000000"

	property int taskId: 1
	property string assignee: "Assignee"

	Row {
		id: layout
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
