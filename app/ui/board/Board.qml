import QtQuick 2.9
import org.kde.kirigami 2.4 as Kirigami
import Qanboard 1.0
import "../task"
import "../tools"

Item {
	id: board
	width: 800
	height: 460
	
	/* Signals a task has requested to be edited. */
	signal taskEdit(int taskId)

	MoodBar {
		id: statusBar

		anchors {
			top: parent.top
			left: parent.left
			bottom: toolbar.top
		}

		width: Kirigami.Units.gridUnit
		
		model: workflow
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

				draggedTaskParent: board

				onItemDragStarted: board.state = "taskDragging"
				onItemDragEnded:   board.state = ""
				onTaskEdit:        board.taskEdit(taskId)
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
			board.state = ""
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
