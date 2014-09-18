import QtQuick 1.1

Rectangle {
	id: workspace
	width: 800
	height: 320

	Model {
		id: mainModel
	}

	Row {
		id: layout
		anchors.fill: parent

		Repeater {
			id: queueRepeater
			model: mainModel

			WorkQueue {
				id: backlog
				width: workspace.width / queueRepeater.model.count
				height: workspace.height

				title: model.name
				taskList: model.tasks
			}
		}
	}
}
