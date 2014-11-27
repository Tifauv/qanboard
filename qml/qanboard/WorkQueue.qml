import QtQuick 1.1

Rectangle {
	id: queue
	width: 200
	height: 320

	property string title: "Title"
	property variant taskList

	signal taskDragged(variant model, int index)

	Title {
		id: titleBox
		height: 40
		label: title
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.top: parent.top
		z: 1
	}

	TaskList {
		id: taskBox
		height: 280
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.top: titleBox.bottom
		anchors.bottom: parent.bottom
		tasks: taskList
		border.color: "#cccccc"
		z:0
		name: title

		onDragged: taskDragged(model, index)
	}

	function findItemPosition(p_mouse) {
		var mappedPos = mapToItem(taskBox, p_mouse.x, p_mouse.y);
		return taskBox.getItemIndex(mappedPos.y);
	}

	function moveItem(p_origin, p_destination) {
		taskList.move(p_origin, p_destination, 1);
	}

	function add(p_model, p_position) {
		if (p_position === -1) {
			taskList.append(p_model);
		}
		else {
			taskList.insert(p_position, p_model);
		}
	}

	function remove(p_position) {
		taskList.remove(p_position);
	}
}
