import QtQuick 1.1

Task {
	opacity: 0.8
	border.color: "#666666"
	border.width: 1

	property variant model
	property variant originalQueue
	property int originalPosition

	onModelChanged: {
		if (model !== undefined && model !== null) {
			taskId = model.taskId;
			assignee = model.assignee;
			description = model.description;
		}
	}

	function beginDrag(p_queue, p_model, p_index) {
		model = p_model;
		originalQueue = p_queue;
		originalPosition = p_index;
		originalQueue.beginDragNDrop();
	}

	function endDrag() {
		originalQueue.endDragNDrop();
		originalPosition = -1;
		originalQueue = null;
		model = null;
	}

	function move(p_queue, p_position) {
		// Déplacement dans la même queue
		if (p_queue === originalQueue) {
			originalQueue.moveItem(originalPosition, p_position);
		}
		// Déplacement dans une autre queue
		else {
			p_queue.add(model, p_position);
			originalQueue.remove(originalPosition);
		}
	}
}
