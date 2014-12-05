import QtQuick 1.1

Rectangle {
	id: button
	height: 32
	width: childrenRect.width

	property string label: "Label"

	signal clicked()

	Text {
		id: btnLabel
		anchors.verticalCenter: parent.verticalCenter
		anchors.right: parent.right
		anchors.topMargin: 8
		anchors.bottomMargin: 8
		anchors.leftMargin: 6
		anchors.rightMargin: 6
		text: label
		horizontalAlignment: Text.AlignRight
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
