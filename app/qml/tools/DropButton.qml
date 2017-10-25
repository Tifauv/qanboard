import QtQuick 2.6
import FontAwesome 1.0

Rectangle {
	id: button
	height: 32
	width: labelWithIcon.width

	property string label: "Label"
	property string icon: FontAwesome.fontAwesome
	property color textColor: "#ffab00"

	signal activated()

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

	MouseArea {
		id: mouseArea
		anchors.fill: parent
		hoverEnabled: true

		onClicked: button.activated()
	}

	states: [
		State {
			name: "highlighted"
			when: mouseArea.containsMouse
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
