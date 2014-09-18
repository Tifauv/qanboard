import QtQuick 1.1

Rectangle {
	id: queue
	width: 200
	height: 320

	property string title: "Title"
	property variant taskList

	Column {
		id: layout
		anchors.fill: parent

		QueueTitle {
			id: titleBox
			height: 40
			label: title
			anchors.right: parent.right
			anchors.left: parent.left
			z: 1
		}

		TaskList {
			id: taskBox
			height: 280
			anchors.right: parent.right
			anchors.left: parent.left
			tasks: taskList
			z: 0
		}
	}
}
