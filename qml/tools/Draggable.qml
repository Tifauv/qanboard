import QtQuick 2.6
import QtGraphicalEffects 1.0
import "../task"

Item {
    id: draggable
	height: topPlaceholder.height + itemPlaceholder.height + bottomPlaceholder.height


	/* The real item wrapped in this draggable. */
	default property Item contentItem

	/* This item will become the contentItem's parent while it is dragged. */
    property Item draggedItemParent

	/* The width of the contentItem's drag handle added at its left. */
	property int handleWidth: 8

	/* Size of the area at the top and bottom of the list where drag-scrolling happens. */
	property int scrollEdgeSize: 6

	/* Internal: -1 when drag-scrolling up / 1 when drag-scrolling down */
	property int _scrollingDirection: 0

	/* The content item is reparented to the wrapper. */
	onContentItemChanged: contentItem.parent = wrapper2

	/* The top placeholder, only used to move an item at the top of the list. */
    Rectangle {
        id: topPlaceholder
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: 0

		color: "red"
    }

	/* The item placeholder inside the ListView */
    Item {
		id: itemPlaceholder
        anchors {
            top: topPlaceholder.bottom
            left: parent.left
            right: parent.right
        }
		height: contentItem.height

        Rectangle {
            id: wrapper
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }

			Drag.active: dragHandle.active
            Drag.hotSpot {
                x: contentItem.width / 2
                y: contentItem.height / 2
            }

            Rectangle {
                id: shadowWrapper
                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }

                Handle {
                    id: dragHandle
                    width: handleWidth
                    anchors {
                        top: parent.top
                        left: parent.left
                        bottom: parent.bottom
                    }

                    dragTarget: wrapper
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
                }
            }

            DropShadow {
                id: shadow
                anchors.fill: shadowWrapper
                cached: true
                verticalOffset: 1
                radius: 8.0
                samples: 16
                color: "#80000000"
                source: shadowWrapper
            }
        }
	}

	/* The main placeholder is _after_ the wrapped item. */
    Rectangle {
        id: bottomPlaceholder
        anchors {
			top: itemPlaceholder.bottom
            left: parent.left
            right: parent.right
        }
        height: 0
		color: "#ffe082"
		border.color: "#caae53"
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
			bottom: itemPlaceholder.verticalCenter
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
			top: itemPlaceholder.verticalCenter
			left: parent.left
			right: parent.right
		}
		property bool isLast: model.index === draggable.ListView.view.count - 1
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
			AnchorChanges {
				target: wrapper
				anchors {
					top: undefined
					left: undefined
					right: undefined
					bottom: undefined
				}
			}
			PropertyChanges {
				target: wrapper
				width: draggable.width
				height: contentItem.height
			}

            PropertyChanges {
				target: itemPlaceholder
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
			when: topDropAreaLoader.containsDrag
			name: "droppingAbove"

			PropertyChanges {
				target: topPlaceholder
				height: contentItem.height
				anchors {
					topMargin: 8
					bottomMargin: 8
				}
			}
			PropertyChanges {
				target: topDropAreaLoader
				height: contentItem.height * 2
			}
		},

		State {
			when: bottomDropArea.containsDrag
			name: "droppingBelow"

			PropertyChanges {
				target: bottomPlaceholder
				height: contentItem.height
				anchors {
					topMargin: 8
					bottomMargin: 8
				}
			}
			PropertyChanges {
				target: bottomDropArea
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

        // Scroll the ListView to ensure the dropped item is visible. This is required when dropping an item after the
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
