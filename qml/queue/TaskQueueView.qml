import QtQuick 2.4
import qanboard.app 1.0
import "../task"

Rectangle {
	id: queue
	width: 200
	height: 320

	property string title: "Title"
	property variant tasks

	signal taskDragged(variant taskList, int index)
	signal taskSelected(variant taskList, int index)

	VisualDataModel {
		id: visualModel

		model: tasks

		delegate: TaskView {
			id: task
			width: taskList.width

			taskId: model.taskId
			assignee: model.assignee
			description: model.description
			selected: model.selected
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
				hoverEnabled: true

				onPressed: {
					console.log("onPressed");

					// If we are sliding inside the view, dismiss
					if (taskList.moving)
						return;
					console.log("! moving");

					// Find the index of the pointed item
					var index = taskList.indexAt(mouse.x + taskList.contentX, mouse.y + taskList.contentY);
					if (index === -1) // No index, nothing to do
						return;
					console.log("index=" + index);
					console.log("name:" + tasks.at(index).description)

					// Invert the "selected" state
					tasks.at(index).selected = ! tasks.at(index).selected;
					console.log("selected state inverted");

					// Do not forward the event
					mouse.accepted = true;
				}

				onDoubleClicked: {
					// If we are sliding inside the view, dismiss
					if (taskList.moving)
						return;

					// Find the index of the pointed item
					var index = taskList.indexAt(mouse.x + taskList.contentX, mouse.y + taskList.contentY);
					if (index === -1) // No index, nothing to do
						return;

					// Do not forward the event
					mouse.accepted = true;

					// Set the pointed item as current
					taskList.currentIndex = index;

					// Signal the drag has started
					taskDragged(tasks, index);
				}
			}
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
