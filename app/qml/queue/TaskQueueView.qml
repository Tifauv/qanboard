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
	property Item draggedTaskParent

	/* Signals the item at the given index has been dragged. */
	signal itemDragStarted(int index)

	/* Signals the item at the given index has been dropped. */
	signal itemDragEnded(int index)

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

			model: tasks

			delegate: Draggable {
				id: draggable
				width: taskList.width - taskList.leftMargin - taskList.rightMargin
				draggedItemParent: queue.draggedTaskParent
				dropTargetItem: queue
				dragKey: "task"

				TaskView {
					taskId: model.taskId
					assignee: model.assignee
					description: model.description
				}

				onInternalMoveRequested: {
					console.log("{d} [TaskQueueView] Internal move required of item " + from + " to position " + to + " inside list " + source);
					source.move(from, to);
				}

				onExternalMoveRequested: {
					console.log("{d} [TaskQueueView] External move required of item " + from + " from list " + source + " to list " + target + " at position " + to);
					var movedTask = source.at(from);
					if (source.remove(from)) {
						target.add(movedTask, to);
					}
				}

				onDragStarted: {
					console.log("{d} [TaskQueueView] Item drag started");
					queue.itemDragStarted(model.index);
				}

				onDragEnded: {
					console.log("{d} [TaskQueueView] Item drag ended");
					queue.itemDragEnded(model.index);
				}
			}
		}
	}


	Component.onCompleted: {
		console.log("(i) [TaskQueueView] Created for queue '" + title + "' with " + tasks.count + " tasks.");
	}


	/**
	 * Logs the view's model content.
	 */
	function log() {
		tasks.log()
	}


	/**
	 * Adds an item with model p_model at p_position.
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
	 * Removes the item at position p_position.
	 *
	 * @return true  if an item was removed,
	 *         false otherwise
	 */
	function remove(p_position) {
		return tasks.removeRow(p_position);
	}


	/**
	 * Returns the item at the given p_position.
	 */
	function at(p_position) {
		return tasks.at(p_position);
	}

	/**
	 * Moves the item at position p_from to position p_to.
	 */
	function move(p_from, p_to) {
		tasks.moveRow(p_from, p_to);
	}
}
