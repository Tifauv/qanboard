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

	AddButton {
		id: newTaskBtn
		anchors.left: parent.left
		anchors.leftMargin: 8
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 8
		visible: true
		height: 32
		z: 3

		onClicked: workspace.state = "addingTask"
	}

	NewTask {
		id: newTask
		visible: false
		anchors.verticalCenter: newTaskBtn.verticalCenter
		anchors.horizontalCenter: newTaskBtn.horizontalCenter
		width: 32
		height: 32
		z: 2

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
				target: newTaskBtn
				anchors.bottom: undefined
				anchors.top: workspace.bottom
			}
		},

		State {
			name: "addingTask"
			PropertyChanges {
				target: newTask
				visible: true
				width: 240
				height: 150
			}
			PropertyChanges {
				target: shadow
				opacity: 0.5
			}

			AnchorChanges {
				target: newTask
				anchors.verticalCenter: workspace.verticalCenter
				anchors.horizontalCenter: workspace.horizontalCenter
			}
			AnchorChanges {
				target: newTaskBtn
				anchors.bottom: undefined
				anchors.top: workspace.bottom
			}
		}
	]

	transitions: [
		Transition {
			from: ""
			to: "taskDragging"

			ParallelAnimation {
				AnchorAnimation {
					targets: newTaskBtn
					duration: 150
					easing.type: Easing.OutQuad
				}
				PropertyAnimation {
					target: draggedTask
					properties: "x,y"
					duration: 0
				}
			}
		},
		Transition {
			from: ""
			to: "addingTask"

			PropertyAnimation {
				target: newTask
				properties: "height,width,opacity"
				duration:  150
				easing.type: Easing.OutQuad
			}
			PropertyAnimation {
				target: shadow
				properties: "opacity"
				duration:  150
			}
			ParallelAnimation {
				AnchorAnimation {
					targets: newTask
					duration: 150
					easing.type: Easing.OutQuad
				}
				AnchorAnimation {
					targets: newTaskBtn
					duration: 150
					easing.type: Easing.OutQuad
				}
			}
		},
		Transition {
			from: "addingTask,taskDragging"
			to: ""

			PropertyAnimation {
				target: shadow
				properties: "opacity"
				duration:  150
			}
			AnchorAnimation {
				targets: newTaskBtn
				duration: 150
				easing.type: Easing.OutQuad
			}
		}
	]
}
