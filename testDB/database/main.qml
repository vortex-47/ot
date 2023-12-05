import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Window 2.12

import dbTest 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Test DataBase")

    Column {
        Label {
            id: l1
            text: "Здесь хочу вывести имя "
        }
        Label {
            id: l2
            text: "Здесь хочу вывести возраст"
        }
        Label {
            id: l3
            text: "Здесь хочу вывести вес"
        }
    }

    Component.onCompleted: {
        DataBase.init()
        console.log(DataBase.getName(
                        2)) // тут я вызываю метод который возращает мне только имя с этим проблем нет
    }
}
