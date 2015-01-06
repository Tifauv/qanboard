import QtQuick 1.1

Rectangle {
	id: toolbar
	color: "#bbdefb"
	width: 800
	height: 48
	state: "reduced"

	signal addTask()

	Row {
		id: layout
		anchors.fill: parent
		anchors.margins: 8
		height: parent.height - anchors.topMargin - anchors.bottomMargin

		AddButton {
			height: layout.height
			onClicked: toolbar.addTask()
		}
	}

	MouseArea {
		id: mouseArea
		anchors.fill: parent
		hoverEnabled: true
	}

	states: [
		State {
			name: "reduced"
			when: !mouseArea.containsMouse

			PropertyChanges {
				target: toolbar
				height: 8
			}
			PropertyChanges {
				target: layout
				visible: false
			}
		}
	]
}
