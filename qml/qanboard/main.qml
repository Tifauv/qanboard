import QtQuick 1.1
import "tools"

Rectangle {
	width: 800
	height: 320

	Workspace {
		anchors.fill: parent
		z: 0
	}

	Toolbar {
		id: tools
		anchors.bottom: parent.bottom
		anchors.left: parent.left
		anchors.right: parent.right
		height: 48
		z: 1

		onAddTask: tools.state = "reduced"
	}
}
