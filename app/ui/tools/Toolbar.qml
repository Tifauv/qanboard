import QtQuick 2.6
import FontAwesome 1.0

Rectangle {
	id: toolbar
	color: "#ffe082"
	border.color: "#caae53"
	width: 800
	height: 0

	signal removeTask(var queue, int taskIndex)

	DropButton {
		id: delTask
		anchors {
			top: toolbar.top
			bottom: toolbar.bottom
			horizontalCenter: toolbar.horizontalCenter
		}

		visible: toolbar.height > 0

		icon: FontAwesome.trash
		label: qsTr("Delete task")
		dropKey: "task"

		onActivated: toolbar.removeTask(queue, taskIndex)
	}

	states: [
		State {
			name: "taskActions"

			PropertyChanges {
				target: toolbar
				height: 32
			}
		}
	]

	transitions: [
		Transition {
			NumberAnimation {
				target: toolbar
				properties: "height"
				duration: 150
				easing.type: Easing.OutQuad
			}
		}
	]
}
