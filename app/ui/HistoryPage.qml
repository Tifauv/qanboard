import QtQuick 2.9
import QtQuick.Controls 2.2 as Controls
import org.kde.kirigami 2.4 as Kirigami

Kirigami.ScrollablePage {
	id: page
	title: qsTr("Activity history")

	signal hideHistory()

	mainAction: Kirigami.Action {
		text: qsTr("Close")
		iconName: "close"
		onTriggered: hideHistory()
	}

	ListView {
		id: list

		anchors.fill: parent

		model: workflow.history

		delegate: TaskMove {
			datetime: model.timestamp
			taskId: model.task.taskId
			taskTitle: qsTr("%1 %2").arg(model.task.client).arg(model.task.activity)
			taskDescription: model.task.description
			originQueueName: model.originQueue.name
			destinationQueueName: model.destinationQueue.name
		}
	}
}
