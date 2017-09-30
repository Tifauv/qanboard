import QtQuick 2.0

Item {
    id: draggable

    default property Item contentItem

    property Item draggedItemParent

    width: contentItem.width
    height: topPlaceolder.height + wrapperParent.height

    // Reparent the content item to its wrapper
    onContentItemChanged: contentItem.parent = wrapper

    // The top placeholder, only useful to
    // move an item at the top of the list.
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

    // The contentItem wrapper
    Item {
        id: wrapperParent
        anchors {
            top: topPlaceholder.bottom
            left: parent.left
            right: parent.right
        }

        Rectangle {
            id: wrapper
            anchors.fill: parent
            Drag.active: contentItem.drag.active
            Drag.hotSpot {
                x: contentItem.width / 2
                y: contentItem.height / 2
            }
        }
    }

    // The main placeholder
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
}
