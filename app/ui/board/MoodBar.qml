import QtQuick 2.9
import QtQuick.Layouts 1.12

Item {
	id: bar

	property var model
	
	ListView {
		id: layout
		
		anchors.fill: parent
		spacing: 0
		verticalLayoutDirection: ListView.BottomToTop
		
		model: bar.model
		
		delegate: Rectangle {
			color: model.color
			
			width: layout.width
			implicitHeight: model.taskCount / bar.model.taskCount * layout.height
		}
	}
}
