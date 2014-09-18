import QtQuick 1.1

Rectangle {
	id: queue
	width: 200
	height: 320

	property string title: "Title"
	property variant taskList

	Title {
		id: titleBox
		height: 40
		label: title
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.top: parent.top
		z: 1000
	}

	TaskList {
		id: taskBox
		height: 280
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.top: titleBox.bottom
		anchors.bottom: parent.bottom
		tasks: taskList
		border.color: "#cccccc"
		z:0
	}
}
