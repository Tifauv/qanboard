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

	VisualDataModel {
		id: visualModel

		model: tasks

		delegate: Draggable {
			id: draggable
			width: taskList.width - taskList.leftMargin - taskList.rightMargin
			draggedItemParent: queue.parent
			dropTargetItem: queue

            TaskView {
				id: task

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
                queue.log();
                target.log();

                var movedTask = tasks.at(from);
                console.log("{d} [TaskQueueView] #1 Moved task is " + movedTask.taskId);
                if (tasks.removeRow(from)) {
                    console.log("{d} [TaskQueueView] #2 Moved task is " + movedTask.taskId);
                    target.add(movedTask, to);
                    console.log("{d} [TaskQueueView] #3 Moved task is " + movedTask.taskId);
                }

                queue.log();
                target.log();
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


    function log() {
        console.log("{d} [TaskQueueView] #tasks for " + title + ": " + tasks.count);
        for (var i=0; i<tasks.count; ++i) {
            var tstTask = tasks.at(i);
            if (tstTask) {
                console.log("  [" + i + "] " + tstTask.taskId);
            }
            else {
                console.log("  [" + i + "] <null>");
            }
        }
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
