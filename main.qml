import QtQuick
import VTKPLUS
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3

Window {

    width: 640
    height: 480
    visibility: "Maximized"
    visible: true
    title: qsTr("MReader")
    Material.primary: Material.Indigo
    Material.accent: Material.LightBlue
    ColumnLayout{
        anchors.fill: parent
        spacing: 0
        MenuBar {
            Layout.fillWidth: true
            Menu{
                id: fileMenu
                title: 'Files'
                Action { text: qsTr("&Open...") }
                Action { text: qsTr("&Save") }
            }

            Menu{
                id: aboutMenu
                title: 'About'
                Action { text: qsTr("&Information...") }
            }

        }

        Item{
            Layout.fillWidth: true
            Layout.fillHeight: true
            objectName:"view"
            VTKRenderWindow {
                objectName: "RenderWindowQt"
                id: vtkwindow
                anchors.fill: parent
            }

            // add one or more vtk render items
            VTKRenderItem {
                objectName: "ConeView"
                anchors.fill: parent
                renderWindow: vtkwindow
            }

        }
    }
}
