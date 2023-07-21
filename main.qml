import QtQuick 2.12
import QtQuick.Window 2.12
import FluentUI 1.0

FluWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Column {
        FluButton {
            text:"测试"
            onClicked: {
                showSuccess("nice!")
            }
        }
        FluFilledButton {
            text: "输入框"
        }
        FluTextBox {
            placeholderText: "666"
        }
    }


}
