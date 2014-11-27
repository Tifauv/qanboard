import QtQuick 1.1

Task {
	opacity: 0.8
	border.color: "#666666"
	border.width: 1
	visible: false

	property variant model
	property variant originalQueue
	property int originalPosition

	onModelChanged: {
		taskId = model.taskId;
		assignee = model.assignee;
		description = model.description;
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
