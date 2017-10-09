import QtQuick 2.4

Rectangle {
	id: button
	height: 32
    width: btnLabel.width + 12 // 6 * 2 = margin

	property string label: "Label"

	signal clicked()
	signal pressed()
	signal released()

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
				target: btnLabel
				color: "white"
			}
		}
	]
}
