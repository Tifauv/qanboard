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

				TaskView {
					taskId: model.taskId
					assignee: model.assignee
					description: model.description
				}

				onInternalMoveRequested: {
					console.log("{d} [TaskQueueView] Internal move required of item " + from + " to position " + to);
					tasks.moveRow(from, to);
				}

				onExternalMoveRequested: {
					console.log("{d} [TaskQueueView] External move required of item " + from + " to list " + target + " at position " + to);
					var movedTask = tasks.at(from);
					if (tasks.removeRow(from)) {
						target.add(movedTask, to);
					}
				}
			}
		}
	}


	Component.onCompleted: {
		console.log("(i) [TaskQueueView] Created for queue '" + title + "' with " + tasks.count + " tasks.");
	}


	function log() {
		tasks.log()
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
}
