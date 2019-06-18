import QtQuick 2.9

CreateTaskDialogForm {
	id: dialog
	
	property string taskClient: clientTxt.text
	property string taskActivity: activityTxt.text
	property string taskDescription: descriptionTxt.text
	property string taskDueDate: dueDateTxt.text
	property string taskTarget: targetTxt.text
	
	function reset() {
		clientTxt.text = "";
		activityTxt.text = "";
		descriptionTxt.text = "";
		dueDateTxt.text = "";
		targetTxt.text = "";
		clientTxt.focus = true;
	}
}
