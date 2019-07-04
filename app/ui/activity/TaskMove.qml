import QtQuick 2.9

TaskMoveForm {

	property string time: "11:25"
	property int taskId: 0
	property string taskTitle: "Plop"
	property string taskDescription: "Description"
	property string originQueueName: "Backlog"
	property color  originQueueColor: "#666666"
	property string destinationQueueName: "Selected"
	property color  destinationQueueColor: "#cccccc"

	timeLbl.text: time
	taskHeader.taskId: taskId
	taskHeader.title: taskTitle
	taskDescriptionLbl.text: taskDescription
	originQueueLbl.text: originQueueName
	destinationQueueLbl.text: destinationQueueName
	
	originQueueRect.border.color: originQueueColor
	destinationQueueRect.border.color: destinationQueueColor
}
