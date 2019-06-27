import QtQuick 2.9
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.2 as Controls
import org.kde.kirigami 2.4 as Kirigami
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

	contextDrawer: Kirigami.ContextDrawer {
		id: contextDrawer
	}

	pageStack.initialPage: workspacePage
	
	Component {
		id: workspacePage

		WorkspacePage {
			onShowCreateDialog: createTaskSheet.open()
			onShowHistory: pageStack.push(historyPage);
		}
	}

	Component {
		id: historyPage

		HistoryPage {
			onHideHistory: pageStack.pop()
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
		
		Keys.onReturnPressed: if (createTaskForm.isValid) createTaskSheet.createTask()
		
		CreateTask {
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
}
