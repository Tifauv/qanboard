import QtQuick 2.9
import org.kde.kirigami 2.4 as Kirigami
import Qanboard 1.0
import "task"
import "queue"
import "tools"

Item {
	id: workspace
	width: 800
	height: 460
	
	/* Signals a task has requested to be edited. */
	signal taskEdit(int taskId)

	WorkspaceStatusBar {
		id: statusBar

		anchors {
			top: parent.top
			left: parent.left
			bottom: toolbar.top
		}

		width: Kirigami.Units.gridUnit
	}

	Row {
		id: layout
		anchors {
			top: parent.top
			left: statusBar.right
			right: parent.right
			bottom: toolbar.top
		}

		Repeater {
			id: queueRepeater
			model: workflow

			TaskQueueView {
				width: Math.floor(layout.width / queueRepeater.model.count) + (index > 0 && index <= layout.width % queueRepeater.model.count ? 1 : 0)
				height: layout.height

				title: model.name
				tasks: model.tasks

				draggedTaskParent: workspace

				onItemDragStarted: workspace.state = "taskDragging"
				onItemDragEnded:   workspace.state = ""
				onTaskEdit:        workspace.taskEdit(taskId)
				
				Component.onCompleted: {
					/* MOST UGLY !
					 * TODO The WorkspaceStatusBar should be reworked to allow for dynamically created segments.
					 * This means the color must come from the model as well.
					 */
					if (title === "Backlog") {
						statusBar.backlogColor = Qt.binding(function() {return tasks.color});
						statusBar.backlogCount = Qt.binding(function() {return tasks.count});
					}
					else if (title === "Selected") {
						statusBar.selectedColor = Qt.binding(function() {return tasks.color});
						statusBar.selectedCount = Qt.binding(function() {return tasks.count});
					}
					else if (title === "In progress") {
						statusBar.workingColor = Qt.binding(function() {return tasks.color});
						statusBar.workingCount = Qt.binding(function() {return tasks.count});
					}
					else if (title === "Done") {
						statusBar.finishedColor = Qt.binding(function() {return tasks.color});
						statusBar.finishedCount = Qt.binding(function() {return tasks.count});
					}
				}
			}
		}
	}

	Toolbar {
		id: toolbar
		anchors.bottom: parent.bottom
		anchors.left: parent.left
		anchors.right: parent.right

		onRemoveTask: {
			console.log("Asked to delete task");
			queue.remove(taskIndex);

			//Cleanup
			workspace.state = ""
		}
	}

	states: [
		State {
			name: "taskDragging"
			PropertyChanges {
				target: toolbar
				state: "taskActions"
			}
		}
	]
}
