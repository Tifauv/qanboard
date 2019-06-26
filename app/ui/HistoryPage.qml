import QtQuick 2.9
import QtQuick.Controls 2.2 as Controls
import org.kde.kirigami 2.4 as Kirigami

Kirigami.ScrollablePage {
	id: page
	title: qsTr("Activity")

	signal hideHistory()

	mainAction: Kirigami.Action {
		text: qsTr("Close")
		iconName: "close"
		onTriggered: hideHistory()
	}

	ListView {
		id: list

		anchors.fill: parent
		spacing: 6

		model: workflow.history

		delegate: TaskMove {
			datetime: model.timestamp
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

		Component.onCompleted: positionViewAtIndex(count - 1, ListView.End)
	}
}
