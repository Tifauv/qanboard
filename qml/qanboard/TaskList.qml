import QtQuick 1.1

Rectangle {
	id: main
	width: 100
	height: 62

	property string name: "default"
	property alias tasks: visualModel.model

	signal dragged(variant model, int index)

	VisualDataModel {
		id: visualModel
		delegate:  Task {
			id: task
			width: taskList.width

			taskId: model.taskId
			assignee: model.assignee
			description: model.description
		}
	}

	ListView {
		id: taskList
		anchors.fill: parent
		anchors.leftMargin: 10
		anchors.topMargin: 10
		anchors.rightMargin: 10
		anchors.bottomMargin: 10
		spacing: 10

		model: visualModel

		MouseArea {
			id: taskMouseArea
			anchors.fill: taskList

			onPressAndHold: {
				// If we are sliding inside the view, dismiss
				if (taskList.moving)
					return;

				var index = taskList.indexAt(mouse.x + taskList.contentX, mouse.y + taskList.contentY);
				if (index === -1) // No index, nothing to do
					return;

				taskList.interactive = false;
				dragged(visualModel.model, index);
			}
		}
	}

	function getItemIndex(p_y) {
		return taskList.indexAt(width / 2, p_y + taskList.contentY);
	}
}
