import QtQuick 2.12
import QtQuick.Window 2.12
import FluentUI 1.0

FluWindow {
    id: window
    visible: true
    width: 640
    minimumWidth: 480
    minimumHeight: 480
    title: qsTr("聊天工具")
    Row {
        spacing: 5
        Column {
            Rectangle {
                width: 120
                height: window.height - 20
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 10
                anchors.leftMargin: 10
                color: "#e4e4e4"
            }
        }
        Column {
            Rectangle {
                width: window.width - 150
                height: window.height - 20
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 10
                anchors.leftMargin: 140
                Rectangle {
                    width: window.width - 150
                    height: 260
                    ListView {
                        id: chatListView
                        width: parent.width
                        height: parent.height
                        model: ChatModel
                        delegate: ChatMessageDelegate {
                            sender: model.sender
                            message: model.message
                            timestamp: Qt.formatDateTime(model.timestamp, "yyyy-MM-dd hh:mm:ss")
                            avatarUrl: model.avatarUrl
                        }
                    }
                }
                FluMultilineTextBox {
                    id: user_msg
                    width: window.width - 150
                    height: 200
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    placeholderText: "请输入信息"
                    FluButton {
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        anchors.bottomMargin: 15
                        anchors.rightMargin: 20
                        text:"发送"
                        onClicked: {
                            ChatManage.sendMessage(user_msg.text)
                            showSuccess("发送成功!")
                        }
                    }
                }
            }
        }
    }
}
