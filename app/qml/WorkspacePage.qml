import QtQuick 2.9
import QtQuick.Controls 2.2
import org.kde.kirigami 2.4 as Kirigami

Kirigami.Page {
	id: page
	title: qsTr("Workspace")
	
	property variant createDlg
	
	mainAction: Kirigami.Action {
		text: qsTr("Create task")
		iconName: "task-new"
		onTriggered: createDlg.open()
	}
	
	Workspace {
		id: workspace
		
		anchors.fill: parent
	}
}
