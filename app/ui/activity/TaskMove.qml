import QtQuick 2.9

TaskMoveForm {

	property string time: "11:25"
	property int taskId: 0
	property string taskTitle: "Plop"
	property string taskDescription: "Description"
	property string originQueueName: "Backlog"
	property string destinationQueueName: "Selected"

	timeLbl.text: time
	taskHeader.taskId: taskId
	taskHeader.title: taskTitle
	taskDescriptionLbl.text: taskDescription
	originQueueLbl.text: originQueueName
	destinationQueueLbl.text: destinationQueueName
	
	originQueueRect.border.color: selectColor(originQueueName)
	destinationQueueRect.border.color: selectColor(destinationQueueName)
	
	function selectColor(p_queueName) {
		if (p_queueName === "Backlog")
			return "#4d4d4d";
		if (p_queueName === "Selected")
			return "#1d99f3";
		if (p_queueName === "In progress")
			return "#da4453";
		if (p_queueName === "Done")
			return "#2ecc71";
	}
}
