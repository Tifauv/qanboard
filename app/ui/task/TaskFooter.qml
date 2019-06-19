import QtQuick 2.9

TaskFooterForm {

	property string dueDate: "12/05/2015"
	property string target: "Target"

	dueDateLbl.text: qsTr("Due date: %1").arg(dueDate)
	dueDateLbl.visible: dueDate.length > 0
	targetLbl.text: qsTr("Targets: %1").arg(target)
}
