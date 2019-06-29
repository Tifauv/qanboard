import QtQuick 2.9
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.2 as Controls
import org.kde.kirigami 2.4 as Kirigami
import Qanboard 1.0
import "task"

Kirigami.ApplicationWindow {
	id: window
	visible: true
	width: 800
	height: 460
	title: qsTr("Qanboard")
	
	globalDrawer: Kirigami.GlobalDrawer {
		title: qsTr("Qanboard")
		titleIcon: "planwork"
		bannerImageSource: "qrc:/images/banner.png"
		
		actions: [
			Kirigami.Action {
				text: qsTr("Quit")
				iconName: "application-exit"
				onTriggered: Qt.quit()
			}
		]
	}

	pageStack.initialPage: workspacePage
	
	Component {
		id: workspacePage

		WorkspacePage {
			onShowCreateDialog: createTaskSheet.open()
			onShowActivity: pageStack.push(activityPage);
		}
	}

	Component {
		id: activityPage

		ActivityPage {
			onClosePage: pageStack.pop()
		}
	}
	
	Kirigami.OverlaySheet {
		id: createTaskSheet
		
		header: Kirigami.Heading {
			text: qsTr("New Task")
		}
		
		footer: RowLayout {
			Controls.Button {
				id: createBtn
				
				Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

				text: qsTr("Create")
				focus: true
				enabled: createTaskForm.isValid

				onClicked: createTaskSheet.createTask()
			}
		}
		
		TaskEdit {
			id: createTaskForm
			Layout.preferredWidth:  Kirigami.Units.gridUnit * 20
			focus: true
			
			onAccepted: createTaskSheet.createTask()
		}
		
		onSheetOpenChanged: {
			createTaskForm.reset();
		}

		function createTask() {
			workflow.createTask(createTaskForm.taskClient, createTaskForm.taskActivity, createTaskForm.taskDescription, createTaskForm.taskDueDate, createTaskForm.taskTarget);
			createTaskSheet.close()
		}
	}
	
	Kirigami.OverlaySheet {
		id: editTaskSheet
		
		header: Kirigami.Heading {
			text: qsTr("Edit Task #%1").arg(editTaskSheet.taskId)
		}
		
		property var model: Task {
			
		}
		
		footer: RowLayout {
			Controls.Button {
				id: modifyBtn
				
				Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

				text: qsTr("Modify")
				focus: true
				enabled: editTaskForm.isValid

				onClicked: editTaskSheet.modifyTask()
			}
		}
		
		TaskEdit {
			id: editTaskForm
			Layout.preferredWidth:  Kirigami.Units.gridUnit * 20
			focus: true
			
			taskClient: editTaskSheet.model.client
			taskActivity: editTaskSheet.model.activity
			taskDescription: editTaskSheet.model.description
			taskDueDate: editTaskSheet.model.dueDate
			taskTarget: editTaskSheet.model.target
			
			onAccepted: editTaskSheet.modifyTask()
		}
		
		onSheetOpenChanged: {
			editTaskForm.reset();
		}

		function modifyTask() {
			//workflow.createTask(createTaskForm.taskClient, createTaskForm.taskActivity, createTaskForm.taskDescription, createTaskForm.taskDueDate, createTaskForm.taskTarget);
			
			editTaskSheet.close()
		}
	}
}
