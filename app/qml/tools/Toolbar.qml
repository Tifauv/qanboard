import QtQuick 2.6
import FontAwesome 1.0

Rectangle {
	id: toolbar
	color: "#ffe082"
	width: 800
	height: 0

	signal removeTask()

	DropButton {
		id: delTask
		anchors {
			verticalCenter: toolbar.verticalCenter
			horizontalCenter: toolbar.horizontalCenter
		}
		height: toolbar.height

		visible: toolbar.height > 0

		icon: FontAwesome.trash
		label: qsTr("Delete task")
		dropKey: "task"

		onActivated: toolbar.removeTask()
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
