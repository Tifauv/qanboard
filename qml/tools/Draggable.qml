import QtQuick 2.0
import "../task"

Item {
    id: draggable
	width: wrapperParent.width
	height: topPlaceholder.height + wrapperParent.height + bottomPlaceholder.height


	/* The real item wrapped in this draggable. */
	//default property Item contentItem: task

	/* This item will become the contentItem's parent while it is dragged. */
    property Item draggedItemParent

	/* The width of the contentItem's drag handle added at its left. */
	property int dragHandleWidth: 8

	/* Size of the area at the top and bottom of the list where drag-scrolling happens. */
	property int scrollEdgeSize: 6

	/* Internal: -1 when drag-scrolling up / 1 when drag-scrolling down */
	property int _scrollingDirection: 0

	/* The content item is reparented to the wrapper. */
	/*onContentItemChanged: {
		contentItem.parent = wrapper2;
		contentItem.visible = true;
	}*/

	/* The top placeholder, only used to move an item at the top of the list. */
    Rectangle {
        id: topPlaceholder
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: 0
        color: "green"
    }

	/* The contentItem wrapper */
    Item {
        id: wrapperParent
        anchors {
            top: topPlaceholder.bottom
            left: parent.left
            right: parent.right
        }
		height: contentItem.height
		width: dragHandle.width + contentItem.width

        Rectangle {
            id: wrapper
            anchors.fill: parent
			Drag.active: dragHandle.active
            Drag.hotSpot {
                x: contentItem.width / 2
                y: contentItem.height / 2
            }

			Handle {
				id: dragHandle
				width: dragHandleWidth
				anchors {
					top: parent.top
					left: parent.left
					bottom: parent.bottom
				}

				dragTarget: parent

				onReleased: emitMoveItemRequested()
			}

			Rectangle {
				id: wrapper2
				anchors {
					top: parent.top
					left: dragHandle.right
					right: parent.right
					bottom: parent.bottom
				}

				TaskView2 {
					id: contentItem
				}
			}
        }
    }

	/* The main placeholder is _after_ the wrapped item. */
    Rectangle {
        id: bottomPlaceholder
        anchors {
            top: wrapperParent.bottom
            left: parent.left
            right: parent.right
        }
        height: 0
        color: "red"
    }

	/* Scroll the view upward when the dragged element is at the top */
	SmoothedAnimation {
		id: scrollUpAnim
		target: draggable.ListView.view
		property: "contentY"
		to: 0
		running: _scrollingDirection == -1
	}

	/* Scroll the view downward when the dragged element is at the bottom */
	SmoothedAnimation {
		id: scrollDownAnim
		target: draggable.ListView.view
		property: "contentY"
		to: draggable.ListView.view.contentHeight - draggable.ListView.view.height
		running: _scrollingDirection == 1
	}

	/* The top drop area is loaded only for the listview's top item. */
	Loader {
		id: topDropAreaLoader
		active: model.index === 0
		anchors {
			left: parent.left
			right: parent.right
			bottom: wrapperParent.verticalCenter
		}
		height: contentItem.height
		sourceComponent: Component {
			DropArea {
				property int dropIndex: 0
			}
		}
	}

	/* The bottom drop area is used for other cases. */
	DropArea {
		id: bottomDropArea
		anchors {
			top: wrapperParent.verticalCenter
			left: parent.left
			right: parent.right
		}
		property bool isLast: model.view === draggable.ListView.view.count - 1
		height: isLast ? draggable.ListView.view.contentHeight - y : contentItem.height
		property int dropIndex: model.index + 1
	}

	states: [
		State {
			when: dragHandle.active
			name: "dragging"

			ParentChange {
				target: wrapper
				parent: draggedItemParent
			}
			PropertyChanges {
				target: wrapper
				opacity: 0.9
				anchors.fill: undefined
				width: dragHandle.width + contentItem.width
				height: contentItem.height
			}
			PropertyChanges {
				target: wrapperParent
				height: 0
			}
			PropertyChanges {
				target: draggable
				_scrollingDirection: {
					var yCoord = draggable.ListView.view.mapFromItem(dragHandle, 0, dragHandle.mouseY).y;
					if (yCoord < scrollEdgeSize) {
						-1;
					} else if (yCoord > draggable.ListView.view.height - scrollEdgeSize) {
						1;
					} else {
						0;
					}
				}
			}
		},

		State {
			when: bottomDropArea.containsDrag
			name: "droppingBelow"

			PropertyChanges {
				target: bottomPlaceholder
				height: contentItem.height
			}
			PropertyChanges {
				target: bottomDropArea
				height: contentItem.height * 2
			}
		},

		State {
			when: topDropAreaLoader.containsDrag
			name: "droppingAbove"

			PropertyChanges {
				target: topPlaceholder
				height: contentItem.height
			}
			PropertyChanges {
				target: topDropAreaLoader
				height: contentItem.height * 2
			}
		}
	]


	function emitMoveItemRequested() {
		var dropArea = 	wrapper.Drag.target;
		if (!dropArea) {
			return;
		}
		var dropIndex = dropArea.dropIndex;

		// If the target item is below us, then decrement dropIndex because the target item is going to move up when
		// our item leaves its place
		if (model.index < dropIndex) {
			dropIndex--;
		}
		if (model.index === dropIndex) {
			return;
		}
		draggable.moveItemRequested(model.index, dropIndex);

		// Scroll the ListView to ensure the droped item is visible. This is required when dropping an item after the
		// last item of the view. Delay the scroll using a timer because we have to wait until the view has moved the
		// item before we can scroll to it.
		//makeDroppedItemVisibleTimer.start();
	}

/*
	Timer {
		id: makeDroppedItemVisibleTimer
		interval: 0
		onTriggered: {
			draggable.ListView.view.positionViewAtIndex(model.index, ListView.Contain);
		}
	}
*/
}
