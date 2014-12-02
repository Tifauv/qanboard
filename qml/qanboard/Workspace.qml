import QtQuick 1.1
import "task"
import "queue"

Rectangle {
	id: workspace
	width: 800
	height: 320

	TaskModel {
		id: tasksModel
	}

	MouseArea {
		id: rootMouseArea
		anchors.fill: workspace
		hoverEnabled: true

		Row {
			id: layout
			anchors.fill: parent

			Repeater {
				id: queueRepeater
				model: tasksModel

				WorkQueue {
					id: queue
					width: workspace.width / queueRepeater.model.count
					height: workspace.height

					title: model.name
					tasks: model.tasks

					onTaskDragged: {
						draggedTask.beginDrag(queue, model.get(index), index);
						rootMouseArea.state = "taskDragging";
					}
				}
			}
		}

		DraggedTask {
			id: draggedTask
			visible: false
		}

		onReleased: {
			if (state === "taskDragging") {
				// Find the destination queue
				var queue = layout.childAt(mouse.x, mouse.y);
				var newPosition = queue.findItemPosition(mapToItem(queue, mouse.x, mouse.y));
				if (draggedTask.isFrom(queue)) {
					draggedTask.move(newPosition);
				}
				else {
					draggedTask.moveTo(queue, newPosition);
				}
				rootMouseArea.state = "";
				draggedTask.endDrag();
			}
		}

		states: [
			State {
				name: "taskDragging"

				PropertyChanges {
					target: rootMouseArea
					drag.target: draggedTask
					drag.filterChildren: true
				}
				PropertyChanges {
					target: draggedTask
					visible: true
					x: rootMouseArea.mouseX - draggedTask.width/2;
					y: rootMouseArea.mouseY - draggedTask.height/2;
				}
			}
		]
	}
}
