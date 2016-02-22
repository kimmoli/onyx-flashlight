import QtQuick 2.0
import Sailfish.Silica 1.0

Page
{
    id: page

    SilicaFlickable
    {
        anchors.fill: parent

        PullDownMenu
        {
            MenuItem
            {
                text: "About..."
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"),
                                          { "version": "0.0.0",
                                              "year": "2016",
                                              "name": "Flashlight",
                                              "imagelocation": "/usr/share/icons/hicolor/86x86/apps/onyx-flashlight.png"} )
            }
        }

        contentHeight: column.height

        Column
        {
            id: column

            width: page.width
            spacing: Theme.paddingLarge
            PageHeader
            {
                title: "Flashlight"
            }
            Button
            {
                anchors.horizontalCenter: parent.horizontalCenter
                enabled: !Torch.stroboState
                text: Torch.torchState ? "Off" : "On"
                onClicked: Torch.torchState = !Torch.torchState
            }
            Button
            {
                anchors.horizontalCenter: parent.horizontalCenter
                enabled: !Torch.torchState
                text: "Strobo"
                onClicked: Torch.stroboState = !Torch.stroboState
            }
            Slider
            {
                width: parent.width - 2*Theme.paddingLarge
                anchors.horizontalCenter: parent.horizontalCenter
                label: "Brightness"
                valueText: value
                minimumValue: 1
                maximumValue: 400
                value: Torch.brightness
                stepSize: 1
                onValueChanged: Torch.brightness = value
            }
            Slider
            {
                width: parent.width - 2*Theme.paddingLarge
                anchors.horizontalCenter: parent.horizontalCenter
                label: "Strobo interval"
                valueText: value
                minimumValue: 20
                maximumValue: 500
                value: Torch.interval
                stepSize: 1
                onValueChanged: Torch.interval = value
            }
        }
    }
}


