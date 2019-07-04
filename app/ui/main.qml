import QtQuick 2.9
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.4 as Kirigami
import Qanboard 1.0

Kirigami.ApplicationWindow {
	id: window
	visible: true
	width: 800
	height: 460
	title: qsTr("Qanboard")
	
	globalDrawer: Kirigami.GlobalDrawer {
		title: qsTr("Qanboard")
		titleIcon: "planwork"
		bannerImageSource: "qrc:/images/banner.png"
		
		actions: [
			Kirigami.Action {
				text: qsTr("Quit")
				iconName: "application-exit"
				onTriggered: Qt.quit()
			}
		]
	}

	pageStack.initialPage: boardPage
	
	Component {
		id: boardPage

		BoardPage {
			onShowActivity: pageStack.push(activityPage);
		}
	}

	Component {
		id: activityPage

		ActivityPage {
			onClosePage: pageStack.pop()
		}
	}
}
