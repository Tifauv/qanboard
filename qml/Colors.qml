import QtQuick 2.6

Rectangle {
	height: 380
	width: 220
	color: background

	property color normalText   : Qt.rgba(0, 0, 0, 0.87)
	property color secondaryText: Qt.rgba(0, 0, 0, 0.54)
	property color disabledText : Qt.rgba(0, 0, 0, 0.26)
	property color divider      : Qt.rgba(0, 0, 0, 0.12)

	property color main         : "#1976d2"
	property color mainLighter  : "#63a4ff"
	property color mainDarker   : "#004ba0"
	property color mainText         : Qt.rgba(1, 1, 1, 0.87)
	property color mainSecondaryText: Qt.rgba(1, 1, 1, 0.54)
	property color mainDisabledText : Qt.rgba(1, 1, 1, 0.26)


	property color accent       : "#ffe082"
	property color accentLighter: "#ffffb3"
	property color accentDarker : "#caae53"

	property color background   : "#fafafa"
	property color tile         : "#ffffff"

	Rectangle {
		id: topBar
		color: mainDarker
		anchors {
			top: parent.top
			left: parent.left
			right: parent.right
		}
		height: 16
	}

	Rectangle {
		id: title
		color: main
		anchors {
			top: topBar.bottom
			left: parent.left
			right: parent.right
		}
		height: 48

		Text {
			id: titleLbl
			color: Qt.rgba(1, 1, 1, 0.87)
			anchors {
				fill: parent
				margins: 8
			}
			font.pointSize: 20
			text: "Title"
			horizontalAlignment: Text.AlignLeft
			verticalAlignment: Text.AlignBottom
		}
	}

	Column {
		id: content
		anchors {
			top: title.bottom
			left: parent.left
			right: parent.right
			bottom: bottomBar.bottom
			margins: 4
		}
		spacing: 8

		Rectangle {
			anchors {
				left: parent.left
				right: parent.right
			}
			height: 48
			color: tile
			border.color: Qt.rgba(0, 0, 0, 0.12) // divider

			Text {
				id: normalText
				anchors {
					top: parent.top
					left: parent.left
					right: parent.right
					topMargin: 4
					leftMargin: 6
					rightMargin: 6
					bottomMargin: 4
				}
				color: Qt.rgba(0, 0, 0, 0.87)
				font.pointSize: 10
				text: "Normal Text"
			}

			Text {
				id: secondaryText
				anchors {
					top: normalText.bottom
					left: parent.left
					right: parent.right
					bottom: parent.bottom
					topMargin: 4
					leftMargin: 6
					rightMargin: 6
					bottomMargin: 4
				}
				color: Qt.rgba(0, 0, 0, 0.54)
				text: "Secondary Text"
			}
		}

		Rectangle {
			anchors {
				left: parent.left
				right: parent.right
			}
			height: 23
			color: tile
			border.color: Qt.rgba(0, 0, 0, 0.12) // divider


			Text {
				id: disabledText
				anchors {
					fill: parent
					topMargin: 4
					leftMargin: 6
					rightMargin: 6
					bottomMargin: 4
				}
				color: Qt.rgba(0, 0, 0, 0.26)
				font.pointSize: 10
				text: "Disabled Text"
			}
		}
	}

	Rectangle {
		id: bottomBar
		color: accent
		anchors {
			left: parent.left
			right: parent.right
			bottom: parent.bottom
		}
		height: 16
	}
}
