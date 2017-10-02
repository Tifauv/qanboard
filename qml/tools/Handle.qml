import QtQuick 2.6

Rectangle {
	id: button
	height: 32
	width: 8

	color: "#cccccc"

	property Item dragTarget
	property bool active: mouseArea.drag.active

	signal pressed()
	signal released()

	MouseArea {
		id: mouseArea
		anchors.fill: parent
		hoverEnabled: true
		drag.target: dragTarget
		drag.smoothed: false

		onPressed: button.pressed(mouse)
		onReleased: {
			if (drag.active)
				button.released(mouse);
		}
	}

	states: [
		State {
			name: "hovered"
			when: mouseArea.containsMouse && !mouseArea.pressed
			PropertyChanges {
				target: button
				color: "#999999"
			}
		},
		State {
			name: "pressed"
			when: mouseArea.pressed
			PropertyChanges {
				target: button
				color: "#666666"
			}
		}
	]
}
