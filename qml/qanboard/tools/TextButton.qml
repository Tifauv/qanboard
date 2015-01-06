import QtQuick 1.1

Rectangle {
	id: button
	height: 32
	width: btnLabel.width + 12 // 6 * 2 = margin

	property string label: "Label"

	signal clicked()

	Text {
		id: btnLabel
		anchors.verticalCenter: parent.verticalCenter
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.topMargin: 8
		anchors.bottomMargin: 8
		text: label
		color: "#ffab00"
		font.weight: Font.Bold
	}

	MouseArea {
		id: mouseArea
		anchors.fill: parent
		hoverEnabled: true

		onClicked: button.clicked()
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
				target: btnLabel
				color: "white"
			}
		}
	]
}
