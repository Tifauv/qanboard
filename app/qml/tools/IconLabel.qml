import QtQuick 2.6
import FontAwesome 1.0

Item {
	id: label
	height: 24
	width: iconText.anchors.leftMargin * 2 + iconText.width + labelText.anchors.leftMargin + labelText.width

	property string text: "Label"
	property string icon: FontAwesome.fontAwesome
	property color color: Qt.rgba(0, 0, 0, 0.87)

	Text {
		id: iconText
		anchors {
			verticalCenter: parent.verticalCenter
			topMargin: 8
			bottomMargin: 8
			left: parent.left
			leftMargin: 6
		}
		font.family: FontAwesome.fontFamily
		text: label.icon
		color: label.color
	}

	Text {
		id: labelText
		anchors {
			verticalCenter: parent.verticalCenter
			topMargin: 8
			bottomMargin: 8
			left: iconText.right
			leftMargin: 8
		}
		text: label.text
		color: label.color
		font.weight: Font.Bold
	}
}
