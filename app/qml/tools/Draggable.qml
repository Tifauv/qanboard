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

	/* This is the type of object that this Draggable will drag */
	property string dragKey

	/* Signals that a drag has started. Usefull to change the state of some upper component. */
	signal dragStarted()

	/* Signals that a drag has ended. Usefull to change the state of some upper component. */
	signal dragEnded()

	/* Signals a drag requested from 'from' position to 'to' position inside the 'source' list. */
	signal internalMoveRequested(var source, int from, int to)

	/* Signals a drag requested from 'from' position in the 'source' list to 'to' position in the 'target' list. */
	signal externalMoveRequested(var source, int from, var target, int to)

	/* The width of the contentItem's drag handle added at its left. */
	property int handleWidth: 8

	/* Size of the area at the top and bottom of the list where drag-scrolling happens. */
	property int scrollEdgeSize: 6

	property int modelIndex: model.index

	/* Internal: shortcup to avoid repeating root.ListView.view */
	property Item _listView: root.ListView.view

	/* The content item is reparented to the contentWrapper. */
	onContentItemChanged: contentItem.parent = contentWrapper;

	/* The top placeholder, only used to move an item at the top of the list. */
	DropPlaceholder {
        id: topPlaceholder
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
		spacing: _listView.spacing
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
			Drag.source: root
            Drag.hotSpot {
                x: contentItem.width / 2
                y: contentItem.height / 2
            }
			Drag.keys: [ dragKey ]
			Drag.proposedAction: Qt.MoveAction

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

					onPressed: root.dragStarted();
					onReleased: {
						movableItem.Drag.drop();
						root.dragEnded();
					}
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
	DropPlaceholder {
        id: bottomPlaceholder
        anchors {
			top: itemPlaceholder.bottom
            left: parent.left
            right: parent.right
			topMargin: _listView.spacing
        }
		spacing: _listView.spacing
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
				keys: [ dragKey ]

				property int targetIndex: 0
				property Item targetList: dropTargetItem

				onDropped : {
					var sourceList  = drop.source.dropTargetItem;
					var sourceIndex = drop.source.modelIndex;

					if (targetList === sourceList) {
						// If the target item is below us, then decrement targetIndex because the target item is going to move up when
						// our item leaves its place
						if (sourceIndex < targetIndex)
							targetIndex--;
						if (sourceIndex === targetIndex)
							return;

						root.internalMoveRequested(sourceList, sourceIndex, targetIndex);
						drop.accept(Qt.MoveAction);
					}
					else {
						root.externalMoveRequested(sourceList, sourceIndex, targetList, targetIndex);
						drop.accept(Qt.MoveAction);
					}
				}
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

		enabled: !movableItem.Drag.active
		keys: [ dragKey ]

		property bool isLast: model.index === _listView.count - 1
		property int defaultHeight: contentItem.height
		property int heightIfLast: Math.max(_listView.height - y - ((contentItem.height + 8) * (_listView.count - 1)), contentItem.height)
		height: isLast ? heightIfLast : defaultHeight

		property int targetIndex: model.index + 1
		property Item targetList: dropTargetItem

		onDropped : {
			console.log("Dropped at index " + targetIndex)
			var sourceList  = drop.source.dropTargetItem;
			var sourceIndex = drop.source.modelIndex;

			if (targetList === sourceList) {
				if (sourceIndex < targetIndex)
					targetIndex--;
				if (sourceIndex === targetIndex)
					return;

				root.internalMoveRequested(sourceList, sourceIndex, targetIndex);
				drop.accept(Qt.MoveAction);
			}
			else {
				root.externalMoveRequested(sourceList, sourceIndex, targetList, targetIndex);
				drop.accept(Qt.MoveAction);
			}
		}
	}

	onStateChanged: {
		console.log("Item " + modelIndex + " of queue '" + _listView + "' entering state '" + state +"'")
	}

	states: [
		State {
			when: movableItem.Drag.active
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
				height: isLast ? heightIfLast : defaultHeight * 2
			}
		}
	]

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
