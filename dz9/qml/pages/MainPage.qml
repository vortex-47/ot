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
import Nemo.DBus 2.0

Page {
    PageHeader {
        objectName: "pageHeader"
        title: qsTr("Домашнее задание №9")
    }
    DBusInterface {
        id: dbusNotify
        service: 'org.freedesktop.Notifications'
        path: '/org/freedesktop/Notifications'
        iface: 'org.freedesktop.Notifications'
    }
//    DBusInterface {
//        id: dbusList
//        service: 'org.freedesktop.DBus'
//        path: '/org/freedesktop/DBus'
//        iface: 'org.freedesktop.DBus'
//        bus: DBus.SessionBus
//    }
//    Button {
//        id: sendNotify
//        anchors.centerIn: parent
//        text: "Отправить уведомление"
//        onClicked: {
//            dbusList.typedCall('ListNames', undefined, function(result) {
//                sessionServices = result.filter(function(value) {
//                return value[0] !== ':'}
//                ).sort();
//            });
//            //console.log(t);
//        }
//    }
    Button {
        id: sendNotify
        anchors.centerIn: parent
        text: "Отправить уведомление"
        onClicked: {
            dbusNotify.call("Notify", ["Test", 0, "фыв", "Test Notify", "asd", [], [], 10000]);
            var t = dbusNotify.typedCall("Notify", [
                                     {
                                         'type': 's',
                                         'value': 'Test'
                                     },
                                     {
                                         'type': 'u',
                                         'value': 0
                                     },
                                     {
                                         'type': 's',
                                         'value': ''
                                     },
                                     {
                                         'type': 's',
                                         'value': 'Test'
                                     },
                                     {
                                         'type': 's',
                                         'value': 'asdasd'
                                     },
                                     {
                                         'type': 'as',
                                         'value': []
                                     },
                                     {
                                         'type': 'a{sv}',
                                         'value': []
                                     },
                                     {
                                         'type': 'i',
                                         'value': 10000
                                     }
                                 ], function(ttt){console.log(ttt)});
            console.log(t);
        }
    }
}
