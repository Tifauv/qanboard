import QtQuick 2.6
import FontAwesome 1.0

Rectangle {
	id: button
	height: 32
	width: labelWithIcon.width

	property string label: "Label"
	property string icon: FontAwesome.fontAwesome
	property color textColor: Qt.rgba(0, 0, 0, 0.87)
	property color bgColor: "#00ffffff"
	property string dropKey

	signal activated()

	color: bgColor

	IconLabel {
		id: labelWithIcon

		text: button.label
		icon: button.icon
		color: button.textColor

		anchors {
			verticalCenter: parent.verticalCenter
			horizontalCenter: parent.horizontalCenter
		}
	}

	DropArea {
		id: dropArea
		anchors.fill: button

		keys: [ dropKey ]

		onDropped: {
			console.log("Dropped");
			button.activated();
		}
	}

	states: [
		State {
			name: "hovered"
			when: dropArea.containsDrag

			PropertyChanges {
				target: button
				color: "#ffab00"
			}
			PropertyChanges {
				target: labelWithIcon
				color: "white"
			}
		}
	]
}
