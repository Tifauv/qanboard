import QtQuick 2.9
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.2 as Controls
import org.kde.kirigami 2.4 as Kirigami
import "activity"

Kirigami.ScrollablePage {
	id: page
	title: qsTr("Activity")
	
	Layout.preferredWidth: Kirigami.Units.gridUnit * 20
	
	signal closePage()
	
	mainAction: Kirigami.Action {
		text: qsTr("Close")
		iconName: "tab-close"
		onTriggered: closePage()
	}
	
	Kirigami.Theme.colorSet: Kirigami.Theme.Window
	
	ListView {
		id: list
		
		anchors.fill: parent
		spacing: Kirigami.Units.largeSpacing
		
		model: workflow.history
		
		delegate: TaskMove {
			time: model.time
			taskId: model.taskId
			taskTitle: qsTr("%1 %2").arg(model.taskClient).arg(model.taskActivity)
			taskDescription: model.taskDescription
			originQueueName: model.origin
			destinationQueueName: model.destination
			
			anchors {
				left: parent.left
				right: parent.right
			}
		}
		
		section.property: "date"
		section.criteria: ViewSection.FullString
		section.delegate: dateSectionHeader
		
		Component.onCompleted: positionViewAtIndex(count-1, ListView.End)
	}
	
	Component {
		id: dateSectionHeader
	
		DateHeader {
			width: parent.width
			text: section
		}
	}
}











/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
