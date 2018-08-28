import QtQuick 2.6

Rectangle {
	id: button
	height: 48
	width: height
	color: "#ffab00"
	radius: height/2

	signal clicked()

	Text {
		color: "white"
		text: "+"
		font.pointSize: button.height * 0.75
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
	}

	MouseArea {
		anchors.fill: parent

		onClicked: button.clicked()
	}
}
