import QtQuick 1.1

Rectangle {
	id: toolbar
	color: "#bbdefb"
	width: 800
	height: 0

	//signal delTask()

	Row {
		id: layout
		visible: false
		anchors.fill: parent
		anchors.margins: 8
		height: parent.height - anchors.topMargin - anchors.bottomMargin

		/*AddButton {
			height: layout.height
			onClicked: toolbar.delTask()
		}*/
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
