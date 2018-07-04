import QtQuick 2.7

Rectangle {
	id: button
	height: 32
	width: 8

	color: "#63a4ff"

	property Item dragTarget
	property bool active: mouseArea.drag.active
	property alias mouseX: mouseArea.mouseX
	property alias mouseY: mouseArea.mouseY

	signal pressed()
	signal released()

	MouseArea {
		id: mouseArea
		anchors.fill: parent
		hoverEnabled: true
		drag.target: dragTarget
		drag.smoothed: false

		onPressed: button.pressed()
		onReleased: button.released()
	}

	states: [
		State {
			name: "hovered"
			when: mouseArea.containsMouse && !mouseArea.pressed
			PropertyChanges {
				target: button
				color: "#1976d2"
			}
		},
		State {
			name: "pressed"
			when: mouseArea.pressed
			PropertyChanges {
				target: button
				color: "#004ba0"
			}
		}
	]
}
