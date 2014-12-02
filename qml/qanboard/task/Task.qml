import QtQuick 1.1

Rectangle {
	id: task
	width: 180
	height: 80
	color: "#eeeeee"
	border.width: 0

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

		Text {
			id: descriptionLbl
			text: qsTr(description)
			wrapMode: Text.WordWrap
			font.pointSize: 9
			anchors.right: parent.right
			anchors.rightMargin: 0
			anchors.left: parent.left
			anchors.leftMargin: 0
		}
	}

	states: [
		State {
			name: "dropTarget"
			PropertyChanges {
				target: task
				color: "#dddddd"
				border.color: "#666666"
				border.width: 5
			}
			PropertyChanges {
				target: mainLayout
				visible: false
			}
		}
	]
}
