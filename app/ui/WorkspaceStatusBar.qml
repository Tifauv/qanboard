import QtQuick 2.9

Item {
	id: bar

	property color backlogColor:  "#4d4d4d"
	property color selectedColor: "#1d99f3"
	property color workingColor:  "#da4453"
	property color finishedColor: "#2ecc71"

	property int backlogCount: 1
	property int selectedCount: 1
	property int workingCount: 1
	property int finishedCount: 1

	readonly property int total: backlogCount + selectedCount + workingCount + finishedCount

	readonly property double backlogPercent:   backlogCount / total
	readonly property double selectedPercent:  selectedCount / total
	readonly property double workingPercent:   workingCount / total
	readonly property double finishedPercent: finishedCount / total

	Rectangle {
		id: finishedBar

		anchors {
			top: parent.top
			left: parent.left
			right: parent.right
			bottom: workingBar.top
		}

		color: finishedColor
	}

	Rectangle {
		id: workingBar

		anchors {
			left: parent.left
			right: parent.right
			bottom: selectedBar.top
		}

		height: workingPercent * bar.height

		color: workingColor
	}

	Rectangle {
		id: selectedBar

		anchors {
			left: parent.left
			right: parent.right
			bottom: backlogBar.top
		}

		height: selectedPercent * bar.height
		color: selectedColor
	}

	Rectangle {
		id: backlogBar

		anchors {
			left: parent.left
			right: parent.right
			bottom: parent.bottom
		}

		height: backlogPercent * bar.height
		color: backlogColor
	}
}
