import QtQuick 2.9
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.4 as Kirigami

ColumnLayout {
    property alias headingLbl: headingLbl

    implicitHeight: childrenRect.height
    spacing: Kirigami.Units.smallSpacing

    Rectangle {
        id: separator

        height: 1
        color: Kirigami.Theme.disabledTextColor

        Layout.fillWidth: true
        Layout.topMargin: Kirigami.Units.largeSpacing
    }

    Kirigami.Heading {
        id: headingLbl

        text: section
        elide: Text.ElideRight
        color: Kirigami.Theme.disabledTextColor

        horizontalAlignment: Text.AlignHCenter
        Layout.fillWidth: true
    }
}
