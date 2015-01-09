import QtQuick 1.1
import "../tools"

Rectangle {
	id: task
	width: 180
	height: 80
	color: "#e3f2fd"

	property alias taskId: header.taskId
	property alias assignee: header.assignee
	property string description: "Description"

	Column {
		id: mainLayout
		anchors.rightMargin: 5
		anchors.leftMargin: 5
		anchors.bottomMargin: 5
		anchors.topMargin: 5
		anchors.fill: parent

		TaskHeader {
			id: header
			height: 20
			anchors.right: parent.right
			anchors.left: parent.left
		}

		Label {
			id: descriptionLbl
			text: qsTr(description)
			wrapMode: Text.WordWrap
			font.pointSize: 9
			anchors.right: parent.right
			anchors.left: parent.left
		}
	}
 states: [
	 State {
		 name: "ghost"

		 PropertyChanges {
			 target: task
			 opacity: 0.54
		 }
	 }
 ]
}
