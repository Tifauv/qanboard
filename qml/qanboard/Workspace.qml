import QtQuick 1.1

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
						draggedTask.x = rootMouseArea.mouseX - draggedTask.width/2;
						draggedTask.y = rootMouseArea.mouseY - draggedTask.height/2;
						draggedTask.beginDrag(queue, model.get(index), index);
						rootMouseArea.drag.target = draggedTask;
						rootMouseArea.drag.filterChildren = true;
					}
				}
			}
		}

		DraggedTask {
			id: draggedTask
		}

		onPositionChanged: {
			if (rootMouseArea.drag.active) {
				draggedTask.x = mouse.x - draggedTask.width/2;
				draggedTask.y = mouse.y - draggedTask.height/2;
			}
		}

		onReleased: {
			if (rootMouseArea.drag.active) {
				// Find the destination queue
				var queue = layout.childAt(mouse.x, mouse.y);
				var newPosition = queue.findItemPosition(mapToItem(queue, mouse.x, mouse.y));
				if (draggedTask.isFrom(queue)) {
					draggedTask.move(newPosition);
				}
				else {
					draggedTask.moveTo(queue, newPosition);
				}
				rootMouseArea.drag.target = null;
				rootMouseArea.drag.filterChildren = false;
				draggedTask.endDrag();
			}
		}
	}
}
