import QtQuick 2.6
import "../tools"

Rectangle {
	id: taskHeader
	height: 20
	color: "#00000000"

	property int taskId: 1
	property string title: "Title"

	Row {
		id: layout
		Label {
			id: taskIdLbl
			text: qsTr("#%1 - ").arg(taskId)
			anchors.verticalCenter: parent.verticalCenter
			state: "secondary"
		}

		Label {
			id: titleassigneeLbl
			text: title
			anchors.verticalCenter: parent.verticalCenter
			state: "secondary"
			font.bold: true
		}
	}
}
