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

import "../elements"

Rectangle {

    id: feedback_top
    x: 0
    y: 0
    width: mainwindow.width
    height: mainwindow.height
    color: "#dd000000"

    property bool someerror: false

    visible: opacity!=0
    opacity: 0
    Behavior on opacity { NumberAnimation { duration: variables.animationSpeed } }
    onOpacityChanged:
        variables.guiBlocked = (opacity==1)

    property int progress: 0
    property bool anonymous: false
    property string accountname: ""

    // Catch all mouse events
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
    }

    Rectangle {

        id: uploading

        opacity: (error.visible||report.visible||obtainingImageUrlDeleteHash.visible||nointerneterror.visible) ? 0 : 1
        Behavior on opacity { NumberAnimation { duration: variables.animationSpeed } }
        visible: opacity!=0

        color: "transparent"
        width: parent.width
        height: childrenRect.height

        y: (parent.height-height)/2

        Column {

            spacing: 20

            Text {
                horizontalAlignment: Text.AlignHCenter
                width: feedback_top.width
                wrapMode: Text.WordWrap
                text: (anonymous
                            ? em.pty+qsTr("Uploading image to imgur.com anonymously")
                            : em.pty+qsTr("Uploading image to imgur.com account:") + " " + accountname)
                color: "white"
                font.pointSize: 40
                font.bold: true
            }

            Text {
                horizontalAlignment: Text.AlignHCenter
                width: feedback_top.width
                wrapMode: Text.WordWrap
                text: variables.currentFile
                color: "white"
                font.pointSize: 30
                font.italic: true
                font.bold: true
            }

            Rectangle {
                color: "transparent"
                width: 1
                height: 1
            }

            CustomProgressBar {
                id: progressbar
                x: (feedback_top.width-width)/2
            }

            CustomButton {
                x: (parent.width-width)/2
                text: em.pty+qsTr("Cancel upload")
                fontsize: 30
                onClickedButton:
                    hide()
            }

        }

    }

    Rectangle {

        id: obtainingImageUrlDeleteHash

        property int code: 0

        opacity: 0
        Behavior on opacity { NumberAnimation { duration: variables.animationSpeed; } }
        visible: opacity!=0

        color: "#00000000"
        anchors.fill: parent

        Rectangle {

            color: "transparent"
            width: childrenRect.width
            height: childrenRect.height
            x: (parent.width-width)/2
            y: (parent.height-height)/2

            Column {

                spacing: 10

                Text {
                    id: obtaintext1
                    width: feedback_top.width-200
                    horizontalAlignment: Text.AlignHCenter
                    //: The image url is the url returned from imgur.com after uploading
                    text: em.pty+qsTr("Obtaining image url")
                    color: "white"
                    font.pointSize: 40
                    font.bold: true
                }

                Text {
                    x: (obtaintext1.width-width)/2
                    property int counter: 0
                    text: counter==0 ? "." :
                         (counter==1 ? ".." :
                         (counter==2 ? "..." :
                         (counter==3 ? "...." :
                         (counter==4 ? "....." :
                         (counter==5 ? "......" :
                         (counter==6 ? "......." :
                         (counter==7 ? "........" :
                         (counter==8 ? "........." :
                         (counter==9 ? ".........." : "..........")))))))))
                    color: "white"
                    font.pointSize: 40
                    font.bold: true
                    Timer {
                        running: obtainingImageUrlDeleteHash.opacity!=0
                        repeat: true
                        interval: 100
                        onTriggered: parent.counter = (parent.counter+1)%10
                    }
                }

                Text {
                    id: obtaintext2
                    width: feedback_top.width-200
                    horizontalAlignment: Text.AlignHCenter
                    text: em.pty+qsTr("Please wait!")
                    color: "white"
                    font.pointSize: 40
                    font.bold: true
                }

                // After 30 seconds we display a "this seems to take a long time" message
                Text {
                    id: longtime
                    visible: false
                    width: feedback_top.width-200
                    horizontalAlignment: Text.AlignHCenter
                    //: Refers to uploading an image to imgur.com
                    text: em.pty+qsTr("This seems to take a long time... If it doesn't work, then there might be a problem with the imgur.com\
 servers at the moment. In that case the only solution is to try again at some later point!")
                    wrapMode: Text.WordWrap
                    color: "red"
                    font.pointSize: 20
                    font.bold: true
                    Timer {
                        id: longtime_timer
                        repeat: false
                        interval: 30000
                        onTriggered: parent.visible = true
                    }

                }

                Rectangle {
                    color: "transparent"
                    width: 1
                    height: 10
                }

                CustomButton {
                    x: (parent.width-width)/2
                    text: em.pty+qsTr("Forget and close")
                    fontsize: 25
                    onClickedButton:
                        hide()
                }

            }

        }

    }

    Rectangle {

        id: error

        property int code: 0

        opacity: 0
        Behavior on opacity { NumberAnimation { duration: variables.animationSpeed; } }
        visible: opacity!=0

        color: "#00000000"
        anchors.fill: parent

        Rectangle {

            color: "transparent"
            width: parent.width
            height: childrenRect.height
            y: (parent.height-height)/2

            Column {

                spacing: 40

                Text {
                    x: 50
                    width: feedback_top.width-100
                    color: "red"
                    font.pointSize: 40
                    font.bold: true
                    wrapMode: Text.WordWrap
                          //: Refers to uploading an image to imgur.com
                    text: em.pty+qsTr("An Error occured while uploading image!") + "\n"
                          + em.pty+qsTr("Error code:") + " " + error.code
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                CustomButton {
                    x: (feedback_top.width-width)/2
                    text: em.pty+qsTr("Close")
                    fontsize: 30
                    onClickedButton:
                        hide()
                }
            }
        }
    }

    Rectangle {

        id: nointerneterror

        opacity: 0
        Behavior on opacity { NumberAnimation { duration: variables.animationSpeed; } }
        visible: opacity!=0

        color: "#00000000"
        anchors.fill: parent

        Rectangle {

            color: "transparent"
            width: parent.width
            height: childrenRect.height
            y: (parent.height-height)/2

            Column {

                spacing: 40

                Text {
                    x: 50
                    width: feedback_top.width-100
                    color: "red"
                    font.pointSize: 40
                    font.bold: true
                    wrapMode: Text.WordWrap
                    //: Refers to uploading an image to imgur.com
                    text: em.pty+qsTr("You don't seem to be able to be connected to the internet... Unable to upload!")
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                CustomButton {
                    x: (parent.width-width)/2
                    text: em.pty+qsTr("Close")
                    fontsize: 30
                    onClickedButton:
                        hide()
                }
            }
        }
    }

    Rectangle {

        id: report

        opacity: 0
        Behavior on opacity { NumberAnimation { duration: variables.animationSpeed; } }
        visible: opacity!=0

        color: "#00000000"
        anchors.fill: parent

        Rectangle {

            color: "transparent"
            width: parent.width
            height: childrenRect.height
            y: (parent.height-height)/2

            Column {

                spacing: 40

                Text {
                    x: 50
                    width: feedback_top.width-100
                    color: "white"
                    font.pointSize: 40
                    wrapMode: Text.WordWrap
                    font.bold: true
                    //: Refers to uploading an image to imgur.com
                    text: em.pty+qsTr("Image successfully uploaded!")
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                Rectangle {

                    color: "transparent"
                    width: childrenRect.width
                    height: childrenRect.height
                    x: (parent.width-width)/2

                    Row {

                        spacing: 10

                        Text {
                            color: "white"
                            font.pointSize: 15
                            font.bold: true
                            //: The url is returned from imgur.com after uploading
                            text: em.pty+qsTr("URL for accessing image") + ": "
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        CustomLineEdit {
                            id: imageurl
                            width: 400
                            text: ""
                        }
                        CustomButton {
                            fontsize: 12
                            y: (parent.height-height)/2
                            text: em.pty+qsTr("visit link")
                            onClickedButton: getanddostuff.openLink(imageurl.text)
                        }

                    }

                }

                Rectangle {

                    color: "transparent"
                    width: childrenRect.width
                    height: childrenRect.height
                    x: (parent.width-width)/2

                    Row {

                        spacing: 10

                        Text {
                            color: "white"
                            font.pointSize: 15
                            font.bold: true
                            //: The url is returned from imgur.com after uploading
                            text: em.pty+qsTr("URL for deleting image") + ": "
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        CustomLineEdit {
                            id: deleteurl
                            width: 400
                            text: ""
                        }
                        CustomButton {
                            fontsize: 12
                            y: (parent.height-height)/2
                            text: em.pty+qsTr("visit link")
                            onClickedButton: getanddostuff.openLink(deleteurl.text)
                        }

                    }

                }

                CustomButton {
                    x: (parent.width-width)/2
                    text: em.pty+qsTr("Close")
                    fontsize: 30
                    onClickedButton:
                        hide()
                }
            }
        }
    }

    Connections {
        target: shareonline_imgur
        onImgurUploadProgress: {
            progressbar.setProgress(perc*100)
            error.opacity = 0
            report.opacity = 0
            nointerneterror.opacity = 0
            obtainingImageUrlDeleteHash.opacity = 0
            if(perc == 1) {
                obtainingImageUrlDeleteHash.opacity = 1
                longtime_timer.restart()
            }
        }
        onFinished: {
            error.opacity = 0
            nointerneterror.opacity = 0
            report.opacity = (feedback_top.someerror ? 0 : 1)
            obtainingImageUrlDeleteHash.opacity = 0
            longtime_timer.stop()
        }
        onImgurUploadError: {
            error.code = err
            error.opacity = 1
            report.opacity = 0
            nointerneterror.opacity = 0
            obtainingImageUrlDeleteHash.opacity = 0
            feedback_top.someerror = true
        }
        onImgurImageUrl: {
            imageurl.text = url
            imageurl.selectAll()
            verboseMessage("Other/ImgurFeedback", "onImgurImageUrl: " + url)
        }

        onImgurDeleteHash: {
            deleteurl.text = "http://imgur.com/delete/" + url
            verboseMessage("Other/ImgurFeedback", "onImgurDeleteHash: " + url)
        }

    }

    Connections {
        target: call
        onImgurfeedbackShow: {
            if(variables.currentFile === "") return
            show(false)
        }
        onImgurfeedbackAnonymShow: {
            if(variables.currentFile === "") return
            show(true)
        }
        onShortcut: {
            if(!feedback_top.visible) return
            if(sh == "Escape")
                hide()
        }
        onCloseAnyElement:
            if(feedback_top.visible)
                hide()
    }

    function show(anonym) {

        verboseMessage("Other/ImgurFeedback", "show(): " + anonym)

        anonymous = anonym
        error.opacity = 0
        report.opacity = 0
        obtainingImageUrlDeleteHash.opacity = 0
        feedback_top.someerror = false
        progressbar.setProgress(0)

        if(!getanddostuff.checkIfConnectedToInternet()) {
            nointerneterror.opacity = 1
            opacity = 1
            return;
        }
        nointerneterror.opacity = 0

        if(!anonymous) {
            var ret = shareonline_imgur.authAccount()
            if(ret !== 0) {
                console.log("Imgur authentication failed!!")
                hide()
                return
            }
            opacity = 1
            accountname = shareonline_imgur.getAccountUsername()
            shareonline_imgur.upload(variables.currentDir + "/" + variables.currentFile)
        } else {
            opacity = 1
            accountname = ""
            shareonline_imgur.anonymousUpload(variables.currentDir + "/" + variables.currentFile)
        }

    }

    function hide() {
        verboseMessage("Other/ImgurFeedback", "hide()")
        error.opacity = 0
        report.opacity = 0
        nointerneterror.opacity = 0
        obtainingImageUrlDeleteHash.opacity = 0
        shareonline_imgur.abort()
        opacity = 0
    }

}
