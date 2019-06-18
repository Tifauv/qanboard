import QtQuick 2.9

TaskHeaderForm {

	property int taskId: 1
	property string title: "Title"

	taskIdLbl.text: qsTr("#%1").arg(taskId)
	titleLbl.text: title
}
