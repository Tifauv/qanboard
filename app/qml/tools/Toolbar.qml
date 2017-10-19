import QtQuick 2.6
import FontAwesome 1.0

Rectangle {
	id: toolbar
	color: "#bbdefb"
	width: 800
	height: 0

	signal removeTask()

	Row {
		id: layout
		visible: false
		anchors.fill: parent
		anchors.margins: 8
		height: parent.height - anchors.topMargin - anchors.bottomMargin

		DropButton {
			id: delTask
			height: layout.height
			icon: FontAwesome.trash
			label: qsTr("Delete task")

			onClicked: toolbar.removeTask()
		}
	}

	states: [
		State {
			name: "taskActions"

			PropertyChanges {
				target: toolbar
				height: 48
			}
			PropertyChanges {
				target: layout
				visible: true
			}
			PropertyChanges {
				target: delTask
				visible: true
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
