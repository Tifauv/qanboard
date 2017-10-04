import QtQuick 2.6
import qanboard.app 1.0
import "../tools"
import "../task"

Rectangle {
	id: queue
	width: 200
	height: 320

	property string title: "Title"
	property variant tasks

	signal taskSelected(variant taskList, int index)

	VisualDataModel {
		id: visualModel

		model: tasks

		delegate: Draggable {
			id: draggable
			width: taskList.width - taskList.leftMargin - taskList.rightMargin
			draggedItemParent: queue.parent

			TaskView2 {
				id: task

				taskId: model.taskId
				assignee: model.assignee
				description: model.description
				selected: model.selected

				onClicked: {
					console.log("(i) [TaskQueueView] Task with index " + index + " selected");

					// Set the pointed item as current
					taskList.currentIndex = index;

					// Signal the drag has started
					taskSelected(tasks, index);
				}
			}
		}
	}

	Title {
		id: titleBox
		height: 40
		name: title
		count: tasks.count
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.top: parent.top
		z: 1
	}

	Rectangle {
		height: 280
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.top: titleBox.bottom
		anchors.bottom: parent.bottom
		color: "#fafafa"
		z:0

		ListView {
			id: taskList
			anchors {
				fill: parent
				topMargin: 8
				leftMargin: 4
				rightMargin: 4
				bottomMargin: 8
			}
			spacing: 8

			model: visualModel
		}
	}


	Component.onCompleted: {
		console.log("(i) [TaskQueueView] Created for queue '" + title + "' with " + tasks.count + " tasks.");
	}

	/**
	 * Initialize the drag'n drop.
	 */
	function beginDragNDrop() {
		taskList.interactive = false;
		taskList.currentItem.state = "ghost";
	}


	/**
	 * Finish the drag'n drop.
	 */
	function endDragNDrop() {
		taskList.currentItem.state = "";
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
		tasks.moveRow(p_origin, p_destination);
	}


	/**
	 * Adds an item at a given position.
	 */
	function add(p_model, p_position) {
		if (p_position === -1) {
			tasks.appendRow(p_model);
		}
		else {
			tasks.insertRow(p_position, p_model);
		}
	}


	/**
	 * Removes the item at a given position.
	 */
	function remove(p_position) {
		tasks.removeRow(p_position);
	}
}
