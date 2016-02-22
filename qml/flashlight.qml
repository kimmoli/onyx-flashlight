import QtQuick 2.0
import Sailfish.Silica 1.0

ApplicationWindow
{
    initialPage: Qt.resolvedUrl("pages/Flashlight.qml")
    cover: CoverBackground
    {
        Column
        {
            anchors.centerIn: parent
            Label
            {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Flashlight"
            }
        }
        CoverActionList
        {
            id: coverAction

            CoverAction
            {
                iconSource: "image://theme/icon-cover-location"
                onTriggered: Torch.torchState = !Torch.torchState
            }
        }
    }
}


