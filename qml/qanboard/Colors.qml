import QtQuick 1.1

Rectangle {
	height: 80
	width: 80
	color: "#ffffff"

	property color normalText: Qt.rgba(0, 0, 0, 0.87)
	property color secondaryText: Qt.rgba(0, 0, 0, 0.54)
	property color disabledText: Qt.rgba(0, 0, 0, 0.26)
	property color divider: Qt.rgba(0, 0, 0, 0.12)

	Column {
		anchors.fill: parent

		Text {
			height: 20
			anchors.left: parent.left
			anchors.right: parent.right
			color: Qt.rgba(0, 0, 0, 0.12)
			text: "divider"
		}

		Text {
			height: 20
			anchors.left: parent.left
			anchors.right: parent.right
			color: Qt.rgba(0, 0, 0, 0.26)
			text: "disabled"
		}

		Text {
			height: 20
			anchors.left: parent.left
			anchors.right: parent.right
			color: Qt.rgba(0, 0, 0, 0.54)
			text: "secondary"
		}

		Text {
			height: 20
			anchors.left: parent.left
			anchors.right: parent.right
			color: Qt.rgba(0, 0, 0, 0.87)
			text: "normal"
		}
	}
}
