import QtQuick 2.4

TaskMoveForm {

	property string datetime: "24/06/2019 11:25"
	property int taskId: 0
	property string taskTitle: "Plop"
	property string taskDescription: "Description"
	property string originQueueName: "Backlog"
	property string destinationQueueName: "Selected"

	dateTimeLbl.text: datetime
	taskHeader.taskId: taskId
	taskHeader.title: taskTitle
	taskDescriptionLbl.text: taskDescription
	originQueueLbl.text: originQueueName
	destinationQueueLbl.text: destinationQueueName
}
