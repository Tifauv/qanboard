import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2 as Controls
import org.kde.kirigami 2.4 as Kirigami
import "board"

Kirigami.ScrollablePage {
	id: page
	title: qsTr("Board edition")
	
	Layout.preferredWidth: Kirigami.Units.gridUnit * 20
	
	signal closePage()
	
	mainAction: Kirigami.Action {
		text: qsTr("Close")
		iconName: "tab-close"
		onTriggered: closePage()
	}
	
	Kirigami.FormLayout {
		id: mainlayout
		
		Controls.TextField {
			id: boardNameTxt
			Kirigami.FormData.label: qsTr("Name:")
			placeholderText: qsTr("Board name")
			text: workflow.name
			
			selectByMouse: true
			
			onActiveFocusChanged: if (!activeFocus) workflow.name = text
			onAccepted: workflow.name = text
		}
		Controls.Label {
			id: lastSavedLbl
			Kirigami.FormData.label: qsTr("Last saved:")
			text: Qt.formatDateTime(workflow.lastSaved, qsTr("dddd dd MMMM yyyy hh'h'mm"))
		}
		Controls.Label {
			id: nextTaskIdLbl
			Kirigami.FormData.label: qsTr("Next task id:")
			text:  workflow.taskId
		}
		Kirigami.Separator {
			Kirigami.FormData.label: qsTr("Queues")
			Kirigami.FormData.isSection: true
		}
		Repeater {
			id: queues
			
			model: workflow
			
			delegate: RowLayout {
				Layout.fillWidth: true

				Rectangle {
					height: queueName.height
					width: height
					radius: height/2
					
					color: model.color
				}

				Controls.Label {
					id: queueName
					text: model.name
					font.bold: model.name === workflow.defaultQueue
					
					Layout.fillWidth: true
				}
			}
		}
	}
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
