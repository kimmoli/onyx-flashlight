import QtQuick 2.0
import Sailfish.Silica 1.0

Page
{
    id: page

    property bool torchIsOn: false
    property int brightness: 1

    property bool stroboIsOn: false
    property int interval: 200

    onBrightnessChanged:
    {
        Torch.set(torchIsOn, stroboIsOn, brightness, interval)
    }

    onIntervalChanged:
    {
        Torch.set(torchIsOn, stroboIsOn, brightness, interval)
    }

    onTorchIsOnChanged:
    {
        Torch.set(torchIsOn, stroboIsOn, brightness, interval)
    }

    onStroboIsOnChanged:
    {
        Torch.set(torchIsOn, stroboIsOn, brightness, interval)
    }

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
                enabled: !stroboIsOn
                text: torchIsOn ? "Off" : "On"
                onClicked: torchIsOn = !torchIsOn
            }
            Button
            {
                anchors.horizontalCenter: parent.horizontalCenter
                enabled: !torchIsOn
                text: "Strobo"
                onClicked: stroboIsOn = !stroboIsOn
            }
            Slider
            {
                width: parent.width - 2*Theme.paddingLarge
                anchors.horizontalCenter: parent.horizontalCenter
                label: "Brightness"
                valueText: value
                minimumValue: 1
                maximumValue: 400
                value: brightness
                stepSize: 1
                onValueChanged: brightness = value
            }
            Slider
            {
                width: parent.width - 2*Theme.paddingLarge
                anchors.horizontalCenter: parent.horizontalCenter
                label: "Strobo interval"
                valueText: value
                minimumValue: 20
                maximumValue: 500
                value: interval
                stepSize: 1
                onValueChanged: interval = value
            }
        }
    }
}


