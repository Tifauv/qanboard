import QtQuick 2.6

Rectangle {
	id: button
	height: 32
	width: 8

	color: "#cccccc"

	signal pressed()
	signal released()

	MouseArea {
		id: mouseArea
		anchors.fill: parent
		hoverEnabled: true

		onPressed: button.pressed(mouse)
		onReleased: button.released(mouse)
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
