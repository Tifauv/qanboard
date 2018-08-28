import QtQuick 2.6

Rectangle {
	id: shadow
	width: 800
	height: 320
	color: "#333333"
	opacity: 0

	MouseArea {
		id: clickBlocker
		anchors.top: parent.top
		anchors.bottom: parent.top
		anchors.left: parent.left
		anchors.right: parent.left
		hoverEnabled: true
	}

	states: State {
		name: "blocking"

		PropertyChanges {
			target: shadow
			opacity: 0.5
		}

		AnchorChanges {
			target: clickBlocker
			anchors.bottom: shadow.bottom
			anchors.right: shadow.right
		}

  PropertyChanges {
	  target: clickBlocker
	  anchors.rightMargin: 0
	  anchors.bottomMargin: 0
  }
	}
}
