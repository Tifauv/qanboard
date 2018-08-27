import QtQuick 2.4
import qanboard.app 1.0
import "task"
import "queue"
import "tools"

Rectangle {
	id: workspace
	width: 800
	height: 320

	Row {
		id: layout
		anchors.top: parent.top
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: toolbar.top

		Repeater {
			id: queueRepeater
			model: workflow

            TaskQueueView {
				id: queue
				width: workspace.width / queueRepeater.model.count
				height: workspace.height

				title: model.name
				tasks: model.tasks

				draggedTaskParent: workspace

				onItemDragStarted: workspace.state = "taskDragging"
				onItemDragEnded:   workspace.state = ""
			}
		}
	}

	Toolbar {
		id: toolbar
		anchors.bottom: parent.bottom
		anchors.left: parent.left
		anchors.right: parent.right

		onRemoveTask: {
			console.log("Asked to delete task");

			//Cleanup
			workspace.state = ""
		}
	}

	ShadowWall {
		id: shadow
		anchors.fill: parent
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
			console.log("(i) [NewTask] onAddTask()");
			workflow.createTask(description);
			workspace.state = ""
		}

        onCancel: {
            console.log("(i) [NewTask] onCancel()");
            workspace.state = ""
        }
	}

	states: [
		State {
			name: "taskDragging"
			PropertyChanges {
				target: newTask
				anchors.bottomMargin: - newTask.height - 10 // 10 should be at least the previous bottomMargin
			}
			
			PropertyChanges {
				target: toolbar
				state: "taskActions"
			}
		},

		State {
			name: "addingTask"
			PropertyChanges {
				target: shadow
				state: "blocking"
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

			NumberAnimation {
				targets: newTask
				properties: "anchors.bottomMargin"
				duration: 150
				easing.type: Easing.OutQuad
			}
		},
		Transition {
			from: "taskDragging"
			to: ""

			NumberAnimation {
				targets: newTask
				properties: "anchors.bottomMargin"
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
