import QtQuick 1.1

Rectangle {
	width: 100
	height: 62

	property alias tasks: taskList.model

	ListView {
		id: taskList
		anchors.fill: parent
		anchors.leftMargin: 10
		anchors.topMargin: 10
		anchors.rightMargin: 10
		anchors.bottomMargin: 10
		spacing: 10
		z: 0

		delegate: Task {
			id: task
			width: taskList.width
			z: 100

			taskId: model.taskId
			assignee: model.assignee
			description: model.description

			MouseArea {
				id: taskMouseArea
				anchors.fill: parent
				drag.target: task
				drag.axis: Drag.XandYAxis
			}
		}
	}
}
