import QtQuick 2.9
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.2 as Controls
import org.kde.kirigami 2.4 as Kirigami

Kirigami.ScrollablePage {
	id: page
	title: qsTr("Activity")
	
	Layout.preferredWidth: Kirigami.Units.gridUnit * 20
	
	signal closePage()
	
	mainAction: Kirigami.Action {
		text: qsTr("Close")
		iconName: "close"
		onTriggered: closePage()
	}
	
	ListView {
		id: list
		
		anchors.fill: parent
		spacing: Kirigami.Units.largeSpacing
		
		model: workflow.history
		
		delegate: TaskMove {
			datetime: model.time
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
	
		ColumnLayout {
			width: parent.width
			height: childrenRect.height
			spacing: Kirigami.Units.smallSpacing
			Layout.topMargin: Kirigami.Units.largeSpacing
			Layout.bottomMargin: Kirigami.Units.largeSpacing
			
			Rectangle {
				id: separator
				height: 1
				Layout.fillWidth: true
				color: Kirigami.Theme.disabledTextColor
			}
			
			Kirigami.Heading {
				text: section
				
				horizontalAlignment: Text.AlignHCenter
				Layout.fillWidth: true
			}
			
			
		}
	}
}











/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
