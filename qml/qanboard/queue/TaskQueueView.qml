import QtQuick 1.1
import "../task"

Rectangle {
	id: queue
	width: 200
	height: 320

	property string title: "Title"
	property variant tasks

	signal taskDragged(variant model, int index)

	VisualDataModel {
		id: visualModel

		model: tasks

		delegate: TaskView {
			id: task
			width: taskList.width

			taskId: model.taskId
			assignee: model.assignee
			description: model.description
		}
	}

	Title {
		id: titleBox
		height: 40
		label: title
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.top: parent.top
		z: 1
	}

	Rectangle {
		id: taskWrapper
		height: 280
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.top: titleBox.bottom
		anchors.bottom: parent.bottom
		border.color: Qt.rgba(0, 0, 0, 0.12)
		z:0

		ListView {
			id: taskList
			height: 280
			anchors.fill: parent
			anchors.leftMargin: 8
			anchors.topMargin: 8
			anchors.rightMargin: 8
			anchors.bottomMargin: 8
			spacing: 8

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

					// emit the taskDragged signal
					taskDragged(visualModel.model, index);
				}
			}
		}
	}


	Component.onCompleted: {
		console.log("TaskQueueView '" + title + "' created with " + tasks.count + " tasks.");
	}

	/**
	 * Initialize the drag'n drop.
	 */
	function beginDragNDrop() {
		taskList.interactive = false;
	}


	/**
	 * Finish the drag'n drop.
	 */
	function endDragNDrop() {
		taskList.interactive = true;
	}


	/**
	 * Find the item index at a given position.
	 */
	function findItemPosition(p_mouse) {
		var mappedPos = mapToItem(taskList, p_mouse.x, p_mouse.y);
		return taskList.indexAt(width / 2, mappedPos.y + taskList.contentY);
	}


	/**
	 * Moves the item at a given position to a new position.
	 */
	function moveItem(p_origin, p_destination) {
		tasks.move(p_origin, p_destination, 1);
	}


	/**
	 * Adds an item at a given position.
	 */
	function add(p_model, p_position) {
		if (p_position === -1) {
			tasks.append(p_model);
		}
		else {
			tasks.insert(p_position, p_model);
		}
	}


	/**
	 * Removes the item at a given position.
	 */
	function remove(p_position) {
		tasks.remove(p_position);
	}
}
