import QtQuick 1.1
import "../tools"

Rectangle {
	id: taskHeader
	height: 20
	color: "#00000000"

	property int taskId: 1
	property string assignee: "Assignee"

	Row {
		id: layout
		Label {
			id: taskIdLbl
			text: qsTr("#%1").arg(taskId)
			anchors.verticalCenter: parent.verticalCenter
			state: "secondary"
			font.bold: true
		}

		Label {
			id: assigneeLbl
			text: qsTr(" - Assigned to %1").arg(assignee)
			anchors.verticalCenter: parent.verticalCenter
			state: "secondary"
		}
	}

	states: [
		State {
			name: "notAssigned"
			when: assignee == ""
			PropertyChanges {
				target: assigneeLbl
				text: qsTr(" - Nobody assigned")
				state: "disabled"
				font.italic: true
			}
		}
	]
}
