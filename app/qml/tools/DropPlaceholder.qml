import QtQuick 2.0

Rectangle {
	id: placeholder
	height: 0

	property int spacing: 6
	property color bgColor: "#ffe082"
	property color borderColor: "#caae53"

	Rectangle {
		id: placeholderItem
		anchors {
			fill: parent
			bottomMargin: spacing
		}

		color: bgColor
		border.color: borderColor
	}
}
