import QtQuick 1.1

Rectangle {
	id: title
	width: 100
	height: 40

	property string name: "Title"
	property int    count: 0
	property color  labelColor: "#ffffff"

	color: "#2196f3"

	Text {
		id: nameLbl
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		anchors.left: parent.left
		anchors.topMargin: 5
		anchors.bottomMargin: 5
		anchors.leftMargin: 5
		text: qsTr(name)
		font.bold: true
		font.pointSize: 11
		verticalAlignment: Text.AlignVCenter
		wrapMode: Text.WrapAnywhere
		color: labelColor
	}

	Text {
		id: countLbl
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		anchors.left: nameLbl.right
		anchors.right: parent.right
		anchors.topMargin: 5
		anchors.bottomMargin: 5
		anchors.leftMargin: 5
		anchors.rightMargin: 5
		text: count
		font.pointSize: 8
		verticalAlignment: Text.AlignVCenter
		color: labelColor
		opacity: 0.87
	}
}
