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

	function isFrom(p_queue) {
		return p_queue === originalQueue;
	}


	function move(p_position) {
		originalQueue.moveItem(originalPosition, p_position);
	}


	function moveTo(p_queue, p_position) {
		p_queue.add(model, p_position);
		originalQueue.remove(originalPosition);
	}
}
