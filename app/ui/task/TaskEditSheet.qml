import QtQuick 2.9
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.4 as Controls
import org.kde.kirigami 2.4 as Kirigami
import Qanboard 1.0

Kirigami.OverlaySheet {
	id: sheet
	
	property var model: undefined
	
	header: Kirigami.Heading {
		id: heading
		text: model === undefined ? qsTr("New Task") : qsTr("Edit Task")
	}
	
	footer: RowLayout {
		Controls.Button {
			id: submitBtn
			
			Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

			text: model === undefined ? qsTr("Create") : qsTr("Modify")
			focus: true
			enabled: form.isValid

			onClicked: form.submit()
		}
	}
	
	TaskEdit {
		id: form
		Layout.preferredWidth:  Kirigami.Units.gridUnit * 20
		focus: true
		
		model: sheet.model
		
		onAccepted: form.submit()
		
		function submit() {
			if (sheet.model === undefined) { // Create mode
				sheet.createTask()
			}
			else { // Edit mode
				sheet.modifyTask()
			}

			sheet.close()
		}
	}

	function createTask() {
		workflow.createTask(form.taskClient, form.taskActivity, form.taskDescription, form.taskDueDate, form.taskTarget);
	}
	
	function modifyTask() {
		sheet.model.client      = form.taskClient;
		sheet.model.activity    = form.taskActivity;
		sheet.model.description = form.taskDescription;
		sheet.model.dueDate     = form.taskDueDate;
		sheet.model.target      = form.taskTarget;
	}
}
