import QtQuick 2.6
import Qanboard 1.0
import "task"
import "queue"
import "tools"

Rectangle {
	id: workspace
	width: 800
	height: 460

	Row {
		id: layout
		anchors.top: parent.top
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: toolbar.top

		Repeater {
			id: queueRepeater
			model: workflow

			TaskQueueView {
				id: queue
				width: workspace.width / queueRepeater.model.count
				height: workspace.height

				title: model.name
				tasks: model.tasks

				draggedTaskParent: workspace

				onItemDragStarted: workspace.state = "taskDragging"
				onItemDragEnded:   workspace.state = ""
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
