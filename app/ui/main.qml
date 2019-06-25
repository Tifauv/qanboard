import QtQuick 2.6
import org.kde.kirigami 2.4 as Kirigami
import "task"

Kirigami.ApplicationWindow {
	id: window
	visible: true
	width: 800
	height: 460
	title: qsTr("My Kanban")
	
	globalDrawer: Kirigami.GlobalDrawer {
		title: qsTr("My Kanban")
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

	pageStack.initialPage: workspacePageComponent
	
	Component {
		id: workspacePageComponent

		WorkspacePage {
			id: workspacePage

			onShowCreateDialog: {
				createDlg.reset();
				createDlg.open()
			}
			onShowHistory: pageStack.push(historyPageComponent)
		}
	}

	Component {
		id: historyPageComponent

		HistoryPage {
			id: historyPage

			onHideHistory: pageStack.pop()
		}
	}
	
	CreateTaskDialog {
		id: createTaskDlg
		
		modal: true
		focus: true
		
		width: Math.max(window.width/3, 300)
		height: Math.max(window.height/3, 400)
		
		x: (parent.width - width) / 2
		y: (parent.height - height) / 2
		
		onAccepted: {
			console.log("(i) [CreateTaskDialog] onAccepted()");
			workflow.createTask(taskClient, taskActivity, taskDescription, taskDueDate, taskTarget);
			reset();
		}
		
		onRejected: reset()
	}
}
