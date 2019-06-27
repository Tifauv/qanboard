import QtQuick 2.9
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.4 as Kirigami

Kirigami.Page {
	id: page
	title: qsTr("Workspace")
	
	signal showCreateDialog()
	signal showHistory()
	
	Layout.preferredWidth: Kirigami.Units.gridUnit * 44
	
	leftPadding: 0
	topPadding: 0
	rightPadding: 0
	bottomPadding: 0
	
	mainAction: Kirigami.Action {
		text: qsTr("Create task")
		iconName: "task-new"
		onTriggered: showCreateDialog()
	}

	contextualActions: [
		Kirigami.Action {
			text: qsTr("View activity")
			iconName: "view-history"
			onTriggered: showHistory()
		}
	]
	
	Workspace {
		id: workspace
		
		anchors.fill: parent
	}
}
