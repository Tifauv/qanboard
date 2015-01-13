import QtQuick 1.1
import qanboard.app 1.0
import "task"
import "queue"
import "tools"

Rectangle {
	id: workspace
	width: 800
	height: 320

	MouseArea {
		id: rootMouseArea
		anchors.fill: parent
		hoverEnabled: true

		Row {
			id: layout
			anchors.fill: parent

			Repeater {
				id: queueRepeater
				model: workflow

				TaskQueueView {
					id: queue
					width: workspace.width / queueRepeater.model.count
					height: workspace.height

					title: model.name
					tasks: model.tasks

					onTaskDragged: {
						draggedTask.beginDrag(queue, taskList.at(index), index);
						workspace.state = "taskDragging";
					}
				}
			}
		}

		DraggedTask {
			id: draggedTask
			visible: false
		}

		onReleased: {
			if (workspace.state === "taskDragging") {
				// Find the destination queue
				var queue = layout.childAt(mouse.x, mouse.y);
				var newPosition = queue.findItemPosition(mapToItem(queue, mouse.x, mouse.y));
				// Move the task
				draggedTask.move(queue, newPosition);
				// Cleanup
				workspace.state = "";
				draggedTask.endDrag();
			}
		}
	}

	Rectangle {
		id: shadow
		anchors.fill: parent
		color: "#333333"
		opacity: 0

	}

	NewTask {
		id: newTask
		fullWidth: 240
		fullHeight: 150
		state: "button"
		anchors.left: parent.left
		anchors.leftMargin: 8
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 8

		onClicked: workspace.state = "addingTask"

		onAddTask: {
			workflow.createTaskInQueue(description, "Backlog");
			workspace.state = ""
		}

		onCancel: workspace.state = ""
	}

	states: [
		State {
			name: "taskDragging"
			PropertyChanges {
				target: rootMouseArea
				drag.target: draggedTask
				drag.filterChildren: true
			}
			PropertyChanges {
				target: draggedTask
				x: rootMouseArea.mouseX - draggedTask.width/2
				y: rootMouseArea.mouseY - draggedTask.height/2
				visible: true
			}
			AnchorChanges {
				target: newTask
				anchors.bottom: undefined
				anchors.top: workspace.bottom
			}
		},

		State {
			name: "addingTask"
			PropertyChanges {
				target: shadow
				opacity: 0.5
			}
			PropertyChanges {
				target: newTask
				state: ""
				anchors.leftMargin: (workspace.width - newTask.fullWidth) / 2
				anchors.bottomMargin: (workspace.height - newTask.fullHeight) / 2
			}
		}
	]

	transitions: [
		Transition {
			from: ""
			to: "taskDragging"

			AnchorAnimation {
				targets: newTask
				duration: 150
				easing.type: Easing.OutQuad
			}
			PropertyAnimation {
				target: draggedTask
				properties: "x,y"
				duration: 0
			}
		},
		Transition {
			from: "taskDragging"
			to: ""

			AnchorAnimation {
				targets: newTask
				duration: 150
				easing.type: Easing.OutQuad
			}
		},
		Transition {
			from: ""
			to: "addingTask"

			NumberAnimation {
				target: shadow
				properties: "opacity"
				duration:  100
			}
			NumberAnimation {
				target: newTask
				properties: "anchors.leftMargin,anchors.bottomMargin"
				duration: 150
				easing.type: Easing.OutQuad
			}
		},
		Transition {
			from: "addingTask"
			to: ""

			NumberAnimation {
				target: shadow
				properties: "opacity"
				duration:  100
			}
			NumberAnimation {
				targets: newTask
				properties: "anchors.leftMargin,anchors.bottomMargin"
				duration: 150
				easing.type: Easing.OutQuad
			}
		}
	]
}
