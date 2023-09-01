/*******************************************************************************
**
** Copyright (C) 2022 ru.auroraos
**
** This file is part of the Моё приложение для ОС Аврора project.
**
** Redistribution and use in source and binary forms,
** with or without modification, are permitted provided
** that the following conditions are met:
**
** * Redistributions of source code must retain the above copyright notice,
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice,
**   this list of conditions and the following disclaimer
**   in the documentation and/or other materials provided with the distribution.
** * Neither the name of the copyright holder nor the names of its contributors
**   may be used to endorse or promote products derived from this software
**   without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
** OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*******************************************************************************/

import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    objectName: "Page2"
    allowedOrientations: Orientation.All

    PageHeader {
        objectName: "pageHeader"
        title: qsTr("Дополнительные сведения")
    }
    Column {
        anchors.centerIn: parent
        width: parent.width
        spacing: Theme.paddingMedium

        TextField {
            id: fam
            placeholderText: qsTr("Введите фамилию")
            label: qsTr("Фамилия (Большая только первая буква)")
            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
            validator: RegExpValidator {
                regExp: /^[A-ZА-Я][a-zа-я]{1,30}$/
            }
        }
        TextField {
            id: name
            placeholderText: qsTr("Введите имя")
            label: qsTr("Имя (Большая только первая буква)")
            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
            validator: RegExpValidator {
                regExp: /^[A-ZА-Я][a-zа-я]{1,30}$/
            }
        }
        TextField {
            id: ot
            placeholderText: qsTr("Введите отчество")
            label: qsTr("Отчество (Большая только первая буква)")
            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
            validator: RegExpValidator {
                regExp: /^[A-ZА-Я][a-zа-я]{1,30}$/
            }
        }
        TextField {
            id: email
            placeholderText: qsTr("Введите свой e-mail")
            label: qsTr("электронная почта")
            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
            validator: RegExpValidator {
                regExp: /^(([^<>()[\].,;:\s@"]+(\.[^<>()[\].,;:\s@"]+)*)|(".+"))@(([^<>()[\].,;:\s@"]+\.)+[^<>()[\].,;:\s@"]{2,})$/
            }
        }

        TextArea {
            objectName: ""
            id: interests
            placeholderText: qsTr("Введите свои интересы, увлечения")
            label: qsTr("интересы, увлечения")
            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
        }

        TextSwitch {
            id: sogl
            text: qsTr("Даю согласие на обработку персональных данных")
            highlighted : checked ? true : false
        }
        TextSwitch {
            text: qsTr("Даю согласие на рассылку данных рекламного характера")
            highlighted : checked ? true : false
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Сохранить")
            enabled: fam.acceptableInput && name.acceptableInput && ot.acceptableInput && email.acceptableInput && sogl.checked
        }
    }
}
