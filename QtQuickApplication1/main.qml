import QtQuick
import QtQuick.Window

Window {
    readonly property int a_width: 800
    readonly property int a_height: 600

    readonly property color backgroundColor: "#E3E3E3"
    readonly property color lightBackgroundColor: "#7A7A7A"

    /* Button Style stuff */
    readonly property color buttonBackgroudColor: "#FFFFFF"
    readonly property color buttonHoverColor: "#D3D3D3"
    readonly property color buttonPopHoverColor: "#FF5E5E"
    readonly property color buttonClickColor: "#bbbbbb"
    readonly property int buttonRadius: 7
	
    visible: true
    width: a_width
    height: a_height
    title: qsTr("Hello World")
}
