/**************************************************************************
 **                                                                      **
 ** Copyright (C) 2018 Lukas Spies                                       **
 ** Contact: http://photoqt.org                                          **
 **                                                                      **
 ** This file is part of PhotoQt.                                        **
 **                                                                      **
 ** PhotoQt is free software: you can redistribute it and/or modify      **
 ** it under the terms of the GNU General Public License as published by **
 ** the Free Software Foundation, either version 2 of the License, or    **
 ** (at your option) any later version.                                  **
 **                                                                      **
 ** PhotoQt is distributed in the hope that it will be useful,           **
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of       **
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        **
 ** GNU General Public License for more details.                         **
 **                                                                      **
 ** You should have received a copy of the GNU General Public License    **
 ** along with PhotoQt. If not, see <http://www.gnu.org/licenses/>.      **
 **                                                                      **
 **************************************************************************/

import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import PContextMenu 1.0
import PInteger64 1.0
import "../elements"
import "../handlestuff.js" as Handle

Item {

    id: item

    x: 5+metadata.nonFloatWidth
    y: 5
    Behavior on x { SmoothedAnimation { duration: variables.animationSpeed } }
    Behavior on y { SmoothedAnimation { duration: variables.animationSpeed } }

    width: childrenRect.width
    height: childrenRect.height

    property bool settingsValues: (!settings.quickInfoHideCounter ||
                                   !settings.quickInfoHideFilename ||
                                   !settings.quickInfoHideFilepath ||
                                   variables.filter!="")

    visible: ( (variables.currentFile=="" && settings.quickInfoManageWindow && !variables.isWindowFullscreen) ||
               (settingsValues && !variables.slideshowRunning && variables.currentFile!="") ||
               (variables.slideshowRunning && !settings.slideShowHideQuickInfo) ) &&
             opacity!=0
    opacity: variables.taggingFaces ? 0 : (variables.guiBlocked&&!variables.slideshowRunning ? 0.2 : 1)
    Behavior on opacity { NumberAnimation { duration: variables.animationSpeed } }

    Rectangle {

        id: containerRect

        x: 0
        y: settings.thumbnailPosition != "Top" ? 0 : background.height-height-6

        // it is always as big as the item it contains
        width: childrenRect.width+6
        height: childrenRect.height+6
        clip: true
        Behavior on width { SmoothedAnimation { duration: variables.animationSpeed } }
        Behavior on height { SmoothedAnimation { duration: variables.animationSpeed } }

        // Some styling
        color: colour.quickinfo_bg
        radius: variables.global_item_radius

        // COUNTER
        Text {

            id: counter

            x:3
            y:3

            text: (variables.currentFile==""||settings.quickInfoHideCounter) ?
                      "" :
                      (variables.currentFilePos+1).toString() + "/" + variables.totalNumberImagesCurrentFolder.toString()

            visible: !settings.quickInfoHideCounter

            color: colour.quickinfo_text
            font.bold: true
            font.pointSize: 10

        }

        // FILENAME
        Text {

            id: filename

            y: 3
            anchors.left: counter.right
            anchors.leftMargin: visible ? (counter.visible ? 10 : 5) : 0

            property bool poppler: variables.multiPageCurrentPage!=-1
            property string popplerAppend: " - Page #"+(1+1*variables.multiPageCurrentPage)+"/"+variables.multiPageTotalNumber
            property bool archive: variables.currentFileInsideArchive!=""
            property string archiveAppend: ": "+variables.currentFileInsideArchive

            text: variables.currentFileWithoutExtras==""&&settings.quickInfoManageWindow&&!variables.isWindowFullscreen ?
                      em.pty+qsTr("Click and drag to move and double click to maximize window") :
                      (settings.quickInfoHideFilepath&&settings.quickInfoHideFilename) ?
                          "" :
                          (settings.quickInfoHideFilepath ?
                               "<b>"+variables.currentFileWithoutExtras+"</b>" :
                               (settings.quickInfoHideFilename ?
                                    "<b>"+variables.currentDir+"</b>" :
                                    "<b>"+variables.currentDir+"/"+variables.currentFileWithoutExtras+"</b>")) +
                          (poppler ? popplerAppend : archive ? archiveAppend : "")

            color: colour.quickinfo_text
            font.pointSize: 10
            visible: text!=""

        }

        Text {

            id: zoomlevel

            y: 3
            anchors.left: filename.right
            anchors.leftMargin: visible&&variables.currentFile!="" ? (counter.visible ? 10 : 5) : 0

            text: visible&&variables.currentFile!="" ?
                      "// " + variables.currentZoomLevel + "%" :
                      ""

            color: colour.quickinfo_text
            font.pointSize: 10
            visible: !settings.quickInfoHideZoomLevel

        }

        // Filter label
        Rectangle {
            id: filterLabel
            visible: (variables.filter != "")
            x: ((!filename.visible && !counter.visible) ? 5 : filename.x-filter_delete.width-filterrow.spacing)
            y: ((!filename.visible && !counter.visible) ? (filename.height-height/2)/2 : filename.y+filename.height+2)
            width: childrenRect.width
            height: childrenRect.height
            color: "#00000000"
            Row {
                id: filterrow
                spacing: 5
                // A label for deletion. The one main MouseArea below trackes whether it is hovered or not
                Text {
                    id: filter_delete
                    color: colour.quickinfo_text
                    visible: (variables.filter != "")
                    text: "x"
                    font.pointSize: 10
                }
                Text {
                    color: colour.quickinfo_text
                    font.pointSize: 10
                    //: Used as in 'Filter images'
                    text: em.pty+qsTr("Filter:") + " " + variables.filter
                    visible: (variables.filter != "")
                }
            }
        }


    }

    // One big MouseArea for everything
    MouseArea {

        id: contextmouse

        anchors.fill: parent

        // The label is draggable, though its position is not stored between sessions (i.e., at startup it is always reset to default)
        drag.target: settings.quickInfoManageWindow&&!variables.isWindowFullscreen ? undefined : parent

        property bool buttonPressed: false
        property int previousX: -1
        property int previousY: -1

        hoverEnabled: true
        acceptedButtons: Qt.LeftButton|Qt.RightButton
        // The cursor shape depends on whether we hover the 'x' for deleting the filter or not
        cursorShape: overDeleteFilterLabel?Qt.PointingHandCursor:Qt.ArrowCursor
        property bool overDeleteFilterLabel: false
        onClicked: {
            // A right click shows context menu
            if(mouse.button == Qt.RightButton) {
                context.popup()
                return
            }
            // A left click on 'x' deletes filter (only if set)
            if(overDeleteFilterLabel && Qt.LeftButton) {
                variables.filter = ""
                Handle.loadFile(variables.currentDir+"/"+variables.currentFile, "", true)
                return
            }

            if(settings.quickInfoManageWindow&&!variables.isWindowFullscreen) {

                int64_curTime.value = Date.now()

                if(Math.abs(int64_curTime.value-int64_timeOfPrevClick.value) < 300) {
                    // caught double click
                    mainwindow.emitToggleWindowMaximise()
                    int64_timeOfPrevClick.value = 0
                } else
                    int64_timeOfPrevClick.value = int64_curTime.value

            }
        }
        onPositionChanged: {

            // No filter visible => nothing to do
            if(!filterLabel.visible)  {
                overDeleteFilterLabel = false
                return
            }
            // Check if within text label of 'x'
            var filterXY = mapFromItem(filter_delete, filter_delete.x, filter_delete.y)
            if(mouse.x > filterXY.x && mouse.x < filterXY.x+filter_delete.width
                    && mouse.y > filterXY.y && mouse.y < filterXY.y+filter_delete.height)
                overDeleteFilterLabel = true
            else
                overDeleteFilterLabel = false

        }

        PInteger64 {
            id: int64_curTime
            Component.onCompleted:
                value = Date.now()
        }
        PInteger64 {
            id: int64_timeOfPrevClick
            Component.onCompleted:
                value = Date.now()
        }

        onPressed: {
            buttonPressed = true
            previousX = mouse.x
            previousY = mouse.y
        }
        onReleased: {
            buttonPressed = false
        }
        // It's important to use the onMouseXChanged and onMouseYChanged here, otherwise the window wont move properly!
        onMouseXChanged: {
            if(buttonPressed && settings.quickInfoManageWindow && !variables.isWindowFullscreen) {
                var dx = mouseX - previousX
                if(dx < -5 || dx > 5)
                    mainwindow.emitMoveWindowByX(dx)
            }
        }
        onMouseYChanged: {
            if(buttonPressed && settings.quickInfoManageWindow && !variables.isWindowFullscreen) {
                var dy = mouseY - previousY
                if(dy < -5 || dy > 5)
                    mainwindow.emitMoveWindowByY(dy)
            }
        }
    }

    PContextMenu {

        id: context

        Component.onCompleted: {

            //: The counter shows the position of the currently loaded image in the folder
            addItem(em.pty+qsTr("Show counter"))
            setCheckable(0, true)
            setChecked(0, !settings.quickInfoHideCounter)

            addItem(em.pty+qsTr("Show filepath"))
            setCheckable(1, true)
            setChecked(1, !settings.quickInfoHideFilepath)

            addItem(em.pty+qsTr("Show filename"))
            setCheckable(2, true)
            setChecked(2, !settings.quickInfoHideFilename)

            addItem(em.pty+qsTr("Show zoom level"))
            setCheckable(3, true)
            setChecked(3, !settings.quickInfoHideZoomLevel)

            //: The clsoing 'x' is the button in the top right corner of the screen for closing PhotoQt
            addItem(em.pty+qsTr("Show closing 'x'"))
            setCheckable(4, true)
            setChecked(4, !settings.quickInfoHideX)

        }

        onCheckedChanged: {
            if(index == 0)
                settings.quickInfoHideCounter = !checked
            else if(index == 1)
                settings.quickInfoHideFilepath = !checked
            else if(index == 2)
                settings.quickInfoHideFilename = !checked
            else if(index == 3)
                settings.quickInfoHideZoomLevel = !checked
            else if(index == 4)
                settings.quickInfoHideX = !checked
        }

    }

}
