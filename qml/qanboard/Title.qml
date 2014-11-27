import QtQuick 1.1

Rectangle {
	width: 100
	height: 40

	property string label: "Title"
	property color  labelColor: "#ffffff"
	property color  buttonColor: "#268bd2"

	gradient: Gradient {
		GradientStop {
			position: 0
			color: Qt.lighter(buttonColor, 1.8)
		}

		GradientStop {
			position: 1
			color: Qt.darker(buttonColor, 1.8)
		}
	}

	Text {
		id: title
		text: qsTr(label)
		anchors.rightMargin: 5
		anchors.leftMargin: 5
		anchors.bottomMargin: 5
		anchors.topMargin: 5
		anchors.fill: parent
		font.bold: true
		font.pointSize: 11
		verticalAlignment: Text.AlignVCenter
		wrapMode: Text.WrapAnywhere
		color: labelColor
	}
}
