import QtQuick 2.6

TaskFooterForm {

	property string client: "Client"
	property string activity: "Activity"
	property string target: "Target"

	clientTag.text: client
	activityTag.text: activity
	targetTag.text: target
}
