import QtQuick 2.6
import Sailfish.Silica 1.0

import QtPositioning 5.3
import QtLocation 5.0
import "../assets"

Page {
    PositionSource {
        id: positionSource
        updateInterval: 1000
        nmeaSource: "/usr/share/ru.auroraos.PositioningAndLocation/nmea/path.nmea"
        active: true
    }
    Map {
        id: map
        plugin: Plugin {
            id: mapPlugin
            name: "webtiles"
            allowExperimental: false
            PluginParameter { name: "webtiles.scheme"; value: "http" }
            PluginParameter { name: "webtiles.host"; value: "a.tile.openstreetmap.fr" }
            PluginParameter { name: "webtiles.path"; value: "/hot/${z}/${x}/${y}.png" }
        }
        anchors.fill: parent
        gesture.enabled: true
        gesture.activeGestures: MapGestureArea.PinchGesture | MapGestureArea.PanGesture
        zoomLevel: sl.value
        Binding {
            target: map
            property: "center"
            value: positionSource.position.coordinate
            when: positionSource.position.coordinate.isValid
        }
        Component.onCompleted: {
            center = QtPositioning.coordinate(55.751244, 37.618423)
            map.addMapItem(foots)
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                var circle = Qt.createQmlObject("import QtLocation 5.0; MapCircle {}", map)
                circle.center = map.toCoordinate(Qt.point(mouse.x, mouse.y));
                circle.radius = 20.0;
                circle.color = "green";
                circle.border.width = 1;
                map.addMapItem(circle);
            }
        }
    }
    Slider {
        id: sl
        width: parent.width
        anchors.bottom: parent.bottom
        minimumValue: map.minimumZoomLevel
        maximumValue: map.maximumZoomLevel
        value: 11
        stepSize: 0.1
    }
    Footprints {
        id: foots
        visible: positionSource.position.coordinate.isValid
        coordinate: positionSource.position.coordinate
        diameter: Math.min(map.width, map.height) / 8
    }
}

