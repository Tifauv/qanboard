import QtQuick 2.6
import QtGraphicalEffects 1.0
import "../task"

Item {
	id: root
	height: topPlaceholder.height + itemPlaceholder.height + bottomPlaceholder.height


	/* The real item wrapped in this root. */
	default property Item contentItem

	/* The target of the drop areas. */
	property Item dropTargetItem

	/* This item will become the contentItem's parent while it is dragged. */
    property Item draggedItemParent

	/* */
	signal dragStarted()

	/* Signals a drag requested from 'from' position to 'to' position inside the list. */
	signal internalMoveRequested(int from, int to)

	/* Signals a drag requested from 'from' position to 'to' position in the 'target' list. */
	signal externalMoveRequested(int from, var target, int to)

	/* The width of the contentItem's drag handle added at its left. */
	property int handleWidth: 8

	/* Size of the area at the top and bottom of the list where drag-scrolling happens. */
	property int scrollEdgeSize: 6

	/* Internal: -1 when drag-scrolling up / 1 when drag-scrolling down */
	property int _scrollingDirection: 0

	/* Internal: shortcup to avoid repeating root.ListView.view */
	property Item _listView: root.ListView.view

	/* The content item is reparented to the contentWrapper. */
	onContentItemChanged: contentItem.parent = contentWrapper;

	/* The top placeholder, only used to move an item at the top of the list. */
    Rectangle {
        id: topPlaceholder
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: 0


		Rectangle {
			id: fakeTopPlaceholderItem
			anchors {
				fill: parent
				bottomMargin: _listView.spacing
			}

			color: "#ffe082"
			border.color: "#caae53"
		}
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
			id: movableItem
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

					dragTarget: movableItem

					onDragged: root.dragStarted()

					onDropped: emitMoveItemRequested()
                }

                Rectangle {
					id: contentWrapper
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
			topMargin: _listView.spacing
        }
        height: 0

		Rectangle {
			id: fakeBottomPlaceholderItem
			anchors {
				fill: parent
				bottomMargin: _listView.spacing
			}

			color: "#ffe082"
			border.color: "#caae53"
		}
	}

	/* Scroll the view upward when the dragged element is at the top */
	SmoothedAnimation {
		id: scrollUpAnim
		target: _listView
		property: "contentY"
		to: 0
		running: _scrollingDirection == -1
	}

	/* Scroll the view downward when the dragged element is at the bottom */
	SmoothedAnimation {
		id: scrollDownAnim
		target: _listView
		property: "contentY"
		to: _listView.contentHeight - _listView.height
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
				property Item targetList: dropTargetItem
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
		property bool isLast: model.index === _listView.count - 1
		height: isLast ? _listView.contentHeight - y : contentItem.height
		property int dropIndex: model.index + 1
		property Item targetList: dropTargetItem
	}

	states: [
		State {
			when: dragHandle.active
			name: "dragging"

			ParentChange {
				target: movableItem
				parent: draggedItemParent
			}
			AnchorChanges {
				target: movableItem
				anchors {
					top: undefined
					left: undefined
					right: undefined
					bottom: undefined
				}
			}
			PropertyChanges {
				target: movableItem
				width: root.width
				height: contentItem.height
			}

            PropertyChanges {
				target: itemPlaceholder
				height: - _listView.spacing // Cancel the view's spacing
			}
			PropertyChanges {
				target: root
				_scrollingDirection: {
					var yCoord = _listView.mapFromItem(dragHandle, 0, dragHandle.mouseY).y;
					if (yCoord < scrollEdgeSize) {
						-1;
					} else if (yCoord > _listView.height - scrollEdgeSize) {
						1;
					} else {
						0;
					}
				}
			}
		},

		State {
			when: topDropAreaLoader.item.containsDrag
			name: "droppingAbove"

			PropertyChanges {
				target: topPlaceholder
				height: contentItem.height + _listView.spacing
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
				height: contentItem.height + _listView.spacing
			}
			PropertyChanges {
				target: bottomDropArea
				height: contentItem.height * 2
			}
		}
	]


	function emitMoveItemRequested() {
		var dropArea = 	movableItem.Drag.target;
		if (!dropArea) {
			return;
		}
		var dropIndex = dropArea.dropIndex;
		var dropList = dropArea.targetList;

		console.log("Source list: " + dropTargetItem)
		console.log("Target list: " + dropList)

		if (dropList === dropTargetItem) {
			console.log("Dropping on same list");

			// If the target item is below us, then decrement dropIndex because the target item is going to move up when
			// our item leaves its place
			if (model.index < dropIndex) {
				dropIndex--;
			}
			if (model.index === dropIndex) {
				return;
			}
			console.log("emitting internalMoveRequested(" + model.index + ", " + dropIndex + ")")
			root.internalMoveRequested(model.index, dropIndex);
		}
		else {
			console.log("Dropping on another list");
			console.log("emitting externalMoveRequested(" + model.index + ", " + dropList + ", " + dropIndex + ")")
			root.externalMoveRequested(model.index, dropList, dropIndex);
		}

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
			_listView.positionViewAtIndex(model.index, ListView.Contain);
		}
	}
*/
}
