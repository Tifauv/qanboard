import QtQuick 1.1

Rectangle {
	id: workspace
	width: 800
	height: 320

	Model {
		id: mainModel
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
				model: mainModel

				WorkQueue {
					id: backlog
					width: workspace.width / queueRepeater.model.count
					height: workspace.height

					title: model.name
					taskList: model.tasks

					onTaskDragged: {
						rootMouseArea.initDrag(backlog, model, index);
					}
				}
			}
		}

		DraggedTask {
			id: draggedTask
		}

		function initDrag(p_queue, p_model, p_index) {
			draggedTask.model = p_model.get(p_index);
			draggedTask.originalPosition = p_index;
			draggedTask.originalQueue = p_queue;
			rootMouseArea.drag.target = draggedTask;
			draggedTask.x = rootMouseArea.mouseX - draggedTask.width/2;
			draggedTask.y = rootMouseArea.mouseY - draggedTask.height/2;
			draggedTask.visible = true;
			rootMouseArea.drag.filterChildren =  true;
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
				draggedTask.visible = false;
			}
		}
	}
}
