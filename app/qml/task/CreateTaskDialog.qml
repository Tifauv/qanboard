import QtQuick 2.9

CreateTaskDialogForm {
	id: dialog
	
	property string taskTitle: titleTxt.text
	property string taskDescription: descriptionTxt.text
	property string taskClient: clientTxt.text
	property string taskActivity: activityTxt.text
	property string taskTarget: targetTxt.text
	
	function reset() {
		titleTxt.text = "";
		descriptionTxt.text = "";
		clientTxt.text = "";
		activityTxt.text = "";
		targetTxt.text = "";
		titleTxt.focus = true;
	}
}
