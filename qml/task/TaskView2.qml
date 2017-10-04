import QtQuick 2.6
import "../tools"

Rectangle {
	id: task
	width: 180
	height: 80
	color: "#ffffff"

	property alias taskId: header.taskId
	property alias assignee: header.assignee
	property string description: "Description"
	property bool selected: false

	onSelectedChanged: {
		console.log("selected changed : " + selected)
	}

	signal clicked()

	MouseArea {
		id: mouseArea
		anchors.fill: parent
		hoverEnabled: true

		onPressAndHold: task.clicked()

		Column {
			id: mainLayout
			anchors.fill: parent
			anchors.leftMargin: 5
			anchors.topMargin: 5
			anchors.rightMargin: 5
			anchors.bottomMargin: 5

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
	}

	states: [
		State {
			name: "ghost"

			PropertyChanges {
				target: task
				opacity: 0.54
			}
		},
		State {
			name: "selected"
			when: task.selected == true

			PropertyChanges {
				target: task
				color: "#eeeeee"
			}
		}

	]
}
