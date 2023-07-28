import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.2

Item {
    id: chatMessageItem
    width: parent.width
    height: 20 + messageLabel.height
    anchors.left: parent.left
    anchors.leftMargin: 5

    property string sender
    property string message
    property string timestamp
    property url avatarUrl

    ColumnLayout {
        spacing: 2
        RowLayout {
            spacing: 10
            Text {
                text: sender
                Layout.alignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            Text {
                text: timestamp
                Layout.alignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
        }
        Text {
            id: messageLabel
            text: message
            width: parent.width
            Layout.leftMargin: 10
        }
    }


}
