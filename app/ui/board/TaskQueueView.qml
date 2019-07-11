import QtQuick 2.9
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.4 as Kirigami
import Qanboard 1.0
import "../tools"
import "../task"

Rectangle {
	id: queue
	width: 200
	height: 320

	property string title: "Title"
	property string taskDragKey: "task"
	property variant tasks
	property Item draggedTaskParent

	/* Signals the item at the given index has been dragged. */
	signal itemDragStarted(int index)

	/* Signals the item at the given index has been dropped. */
	signal itemDragEnded(int index)
	
	/* Signals a task has requested to be edited. */
	signal taskEdit(int taskId)
	
	/* Signals a task should be removed. */
	signal taskRemove(int taskId)

	Kirigami.Theme.colorSet: Kirigami.Theme.Window
	color: Kirigami.Theme.backgroundColor

	ColumnLayout {
		id: layout
		
		anchors.fill: parent
		spacing: 0

		Title {
			id: titleBox
			height: 40
			name: title
			count: tasks.count

			Layout.fillWidth: true
			
			z: 1
		}
		
		ListView {
			id: taskList
			
			Layout.fillWidth: true
			Layout.fillHeight: true
			Layout.margins: Kirigami.Units.smallSpacing
			spacing: Kirigami.Units.largeSpacing
			
			model: tasks

			delegate: Draggable {
				id: draggable
				width: taskList.width - taskList.leftMargin - taskList.rightMargin
				draggedItemParent: queue.draggedTaskParent
				dropTargetItem: queue
				dragKey: taskDragKey

				contentItem: TaskView {
					taskId: model.taskId
					client: model.client
					activity: model.activity
					description: model.description
					dueDate: model.dueDate
					target: model.target
					
					onEdit: {
						console.log("(i) [TaskQueueView] Requested edition of task #" + taskId);
						queue.taskEdit(taskId)
					}
					
					onRemove: {
						console.log("(i) [TaskQueueView] Requested removal of task #" + taskId);
						queue.taskRemove(taskId)
					}
				}

				onInternalMoveRequested: {
					console.log("{d} [TaskQueueView] Internal move required of item " + from + " to position " + to + " inside list " + source);
					source.move(from, to);
				}

				onExternalMoveRequested: {
					console.log("{d} [TaskQueueView] External move required of item " + from + " from list " + source + " to list " + target + " at position " + to);
					workflow.moveBetweenQueues(source.title, from, target.title, to);
				}

				onDragStarted: {
					console.log("{d} [TaskQueueView] Item drag started");
					queue.itemDragStarted(model.index);
				}

				onDragEnded: {
					console.log("{d} [TaskQueueView] Item drag ended");
					queue.itemDragEnded(model.index);
				}
			}

			DropPlaceholder {
				id: emptyPlaceholder
				anchors {
					top: taskList.top
					left: taskList.left
					right: taskList.right
				}
			}
			
			Loader {
				id: emptyDropAreaLoader
				active: taskList.model.count === 0
				anchors.fill: taskList
	
				sourceComponent: Component {
					DropArea {
						keys: [ taskDragKey ]
	
						onDropped: {
							var sourceList  = drop.source.dropTargetItem;
							var sourceIndex = drop.source.modelIndex;
	
							workflow.moveBetweenQueues(sourceList.title, sourceIndex, title, 0);
							drop.accept(Qt.MoveAction);
						}
					}
				}
			}
		}
	}

	states: State {
		when: emptyDropAreaLoader.item.containsDrag
		name: "DroppingEmpty"

		PropertyChanges {
			target: emptyPlaceholder
			height: 111 + taskList.spacing // 111 is a Draggable's height
		}
	}

	Component.onCompleted: {
		console.log("(i) [TaskQueueView] Created for queue '" + title + "' with " + tasks.count + " tasks.");
	}


	/**
	 * Logs the view's model content.
	 */
	function log() {
		tasks.log()
	}


	/**
	 * Adds an item with model p_model at p_position.
	 */
	function add(p_model, p_position) {
		if (p_position === -1) {
			tasks.append(p_model);
		}
		else {
			tasks.insert(p_position, p_model);
		}
	}


	/**
	 * Removes the item at position p_position.
	 *
	 * @return true  if an item was removed,
	 *         false otherwise
	 */
	function removeAt(p_position) {
		return tasks.removeAt(p_position);
	}


	/**
	 * Returns the item at the given p_position.
	 */
	function at(p_position) {
		return tasks.at(p_position);
	}

	/**
	 * Moves the item at position p_from to position p_to.
	 */
	function move(p_from, p_to) {
		tasks.move(p_from, p_to);
	}
}
