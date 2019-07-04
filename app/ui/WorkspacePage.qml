import QtQuick 2.9
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.4 as Kirigami
import "task"

Kirigami.Page {
	id: page
	title: workflow.name.length > 0 ? workflow.name : qsTr("Workspace")
	
	signal showActivity()
	
	Layout.preferredWidth: Kirigami.Units.gridUnit * 44
	
	leftPadding: 0
	topPadding: 0
	rightPadding: 0
	bottomPadding: 0
	
	mainAction: Kirigami.Action {
		text: qsTr("Create task")
		iconName: "task-new"
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
		}
	]
	
	Workspace {
		id: workspace
		
		anchors.fill: parent
		
		onTaskEdit: {
			taskEditSheet.model = workflow.findTask(taskId);
			taskEditSheet.open()
		}
	}
	
	TaskEditSheet {
		id: taskEditSheet
		model: undefined
	}
}
