import QtQuick 2.4

Rectangle {
	id: title
	width: 100
	height: 40

	property string name: "Title"
	property int    count: 0
	property color  labelColor: "#ffffff"

	color: "#1976d2"

	Text {
		id: nameLbl
		anchors {
			top: parent.top
			bottom: parent.bottom
			left: parent.left
			topMargin: 5
			bottomMargin: 5
			leftMargin: 5
		}
		text: qsTr(name)
		font {
			bold: true
			pointSize: 11
		}
		verticalAlignment: Text.AlignVCenter
		wrapMode: Text.WrapAnywhere
		color: labelColor
	}

	Text {
		id: countLbl
		anchors {
			top: parent.top
			bottom: parent.bottom
			left: nameLbl.right
			right: parent.right
			margins: 5
		}
		text: count
		font.pointSize: 8
		verticalAlignment: Text.AlignVCenter
		color: labelColor
		opacity: 0.87
	}
}
