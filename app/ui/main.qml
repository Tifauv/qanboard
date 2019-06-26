import QtQuick 2.9
import QtQuick.Layouts 1.12
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

	pageStack.defaultColumnWidth: Kirigami.Units.gridUnit * 36
	pageStack.initialPage: workspacePage
	
	Component {
		id: workspacePage

		WorkspacePage {
			onShowCreateDialog: {
				createTaskDlg.reset();
				createTaskDlg.open()
			}

			onShowHistory: pageStack.push(historyPage);
		}
	}

	Component {
		id: historyPage

		HistoryPage {
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
