import QtQuick 1.1

Rectangle {
	width: 100
	height: 62

	property alias tasks: taskRepeat.model

	Flickable {
		id: scroll
		anchors.fill: parent
		contentWidth: parent.width
		contentHeight: taskList.childrenRect.height

		Column {
			id: taskList
			anchors.fill: parent
			anchors.leftMargin: 10
			anchors.topMargin: 10
			anchors.rightMargin: 10
			anchors.bottomMargin: 10
			spacing: 10

			Repeater {
				id: taskRepeat

				Task {
					width: taskList.width - anchors.leftMargin - anchors.rightMargin

					taskId: model.taskId
					assignee: model.assignee
					description: model.description
				}

				onItemAdded: {
					print("++ " + taskRepeat.count + ": " + scroll.visibleArea.heightRatio);
				}

				onItemRemoved: {
					print("-- " + taskRepeat.count + ": " + scroll.visibleArea.heightRatio);
				}
			}
		}
	}

	Rectangle {
		id: scrollbar
		anchors.right: scroll.right
		y: scroll.visibleArea.yPosition * scroll.height
		width: 4
		radius: 2
		smooth: true
		height: scroll.visibleArea.heightRatio * scroll.height
		color: "#657b83"
	}

	states: [
		State {
			name: "noScrollbar"
			when: scroll.visibleArea.heightRatio == 1
			PropertyChanges {
				target: scrollbar
				visible: false
			}
		}

	]
}
