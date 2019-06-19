import QtQuick 2.6
import FontAwesome 1.0

Rectangle {
	id: button
	height: 32
	width: btnIcon.width + btnLabel.anchors.leftMargin + btnLabel.width + 12 // 6 = right margin

	property string label: "Label"
	property string icon: FontAwesome.fontAwesome
	property color textColor: "#ffab00"

	signal clicked()
	signal pressed()
	signal released()

	Text {
		id: btnIcon
		anchors {
			verticalCenter: parent.verticalCenter
			topMargin: 8
			bottomMargin: 8
			left: button.left
			leftMargin: 6
		}
		font.family: FontAwesome.fontFamily
		text: button.icon
		color: textColor
	}

	Text {
		id: btnLabel
		anchors {
			verticalCenter: parent.verticalCenter
			topMargin: 8
			bottomMargin: 8
			left: btnIcon.right
			leftMargin: 8
		}
		text: label
		color: textColor
		font.weight: Font.Bold
	}

	MouseArea {
		id: mouseArea
		anchors.fill: parent
		hoverEnabled: true

		onClicked: button.clicked()
		onPressed: button.pressed()
		onReleased: button.released()
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
				target: btnIcon
				color: "white"
			}
			PropertyChanges {
				target: btnLabel
				color: "white"
			}
		}
	]
}
