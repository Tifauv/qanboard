import QtQuick 2.9

TaskEditForm {
	id: form
	
	property string taskClient: clientTxt.text
	property string taskActivity: activityTxt.text
	property string taskDescription: descriptionTxt.text
	property string taskDueDate: dueDateTxt.text
	property string taskTarget: targetTxt.text
	
	property var model: undefined
	
	// A task can be created if its description is not empty
	readonly property bool isValid: descriptionTxt.text.length > 0
	
	signal accepted()
	
	clientTxt.onAccepted     : if (isValid) accepted()
	activityTxt.onAccepted   : if (isValid) accepted()
	descriptionTxt.onAccepted: if (isValid) accepted()
	dueDateTxt.onAccepted    : if (isValid) accepted()
	targetTxt.onAccepted     : if (isValid) accepted()
	
	function reset() {
		clientTxt.text = "";
		activityTxt.text = "";
		descriptionTxt.text = "";
		dueDateTxt.text = "";
		targetTxt.text = "";
		clientTxt.focus = true;
	}

	onModelChanged: {
		if (model !== undefined) {
			console.log("(i) [TaskEdit] Loading data from model")
			clientTxt.text      = model.client;
			activityTxt.text    = model.activity;
			descriptionTxt.text = model.description;
			dueDateTxt.text     = model.dueDate;
			targetTxt.text      = model.target;
		}
		else {
			console.log("(i) [TaskEdit] Initializing empty data")
			reset()
		}
	}
}
