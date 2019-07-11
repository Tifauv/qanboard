import QtQuick 2.9
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.4 as Kirigami
import "board"
import "task"

Kirigami.Page {
	id: page
	title: workflow.name.length > 0 ? workflow.name : qsTr("Board")
	
	signal showActivity()
	signal showBoardEdit()
	
	Layout.preferredWidth: Kirigami.Units.gridUnit * 44
	
	leftPadding: 0
	topPadding: 0
	rightPadding: 0
	bottomPadding: 0
	
	mainAction: Kirigami.Action {
		text: qsTr("Create task")
		iconName: "task-new"
		shortcut: StandardKey.New
		onTriggered: {
			taskEditSheet.model = undefined;
			taskEditSheet.open()
		}
	}

	contextualActions: [
		Kirigami.Action {
			text: qsTr("View activity")
			iconName: "view-history"
			onTriggered: showActivity()
		},
		Kirigami.Action {
			text: qsTr("Edit board")
			iconName: "document-edit"
			onTriggered: showBoardEdit()
		}
	]
	
	Board {
		anchors {
			top: parent.top
			left: parent.left
			right: parent.right
			bottom: deleteMsg.top
		}
		
		onTaskEdit: {
			taskEditSheet.model = workflow.findTask(taskId);
			taskEditSheet.open()
		}
		
		onTaskRemove: {
			deleteMsg.taskId = taskId;
			deleteMsg.visible = true
		}
	}
	
	Kirigami.InlineMessage {
		id: deleteMsg
		
		anchors {
			bottom: parent.bottom
			left: parent.left
			right: parent.right
		}
		
		property int taskId
		
		type: Kirigami.MessageType.Warning
		text: qsTr("Do you really want to delete task #%1?").arg(taskId)
		showCloseButton: true
		
		actions: [
			Kirigami.Action {
				text: qsTr("Delete")
				iconName: "edit-delete"
				onTriggered: {
					workflow.removeTask(deleteMsg.taskId);
					deleteMsg.visible = false
				}
			}
		]
	}
	
	TaskEditSheet {
		id: taskEditSheet
		model: undefined
	}
}
