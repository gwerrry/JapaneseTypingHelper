import QtQuick
import QtQuick.Window
import QtQuick.Controls

Window {
    readonly property int a_width: 800
    readonly property int a_height: 600
	readonly property color bgColor: "#E3E3E3"
    readonly property color lightBgColor: "#7A7A7A"

    /* Button Style stuff */
    readonly property color buttonBgColor: "#AAB2BD"
    readonly property color buttonHoverColor: "#C4CDDA"
    readonly property color buttonPopHoverColor: "#FF5E5E"
    readonly property color buttonClickColor: "#656D78"
    readonly property int buttonRadius: 7
	
    visible: true
    width: a_width
    height: a_height
	
    title: mainMenuSplashText

	
    Rectangle {
            width: a_width
            height: a_height
            visible: true

            color: bgColor

            Page {
                id: main_menu
                opacity: 1
                visible: true
                enabled: true
                anchors.fill: parent
                Rectangle {
                    color: bgColor
                    width: parent.width
                    height: parent.height
                    visible: true

                    Text {
                        id: main_label
                        x: 214
                        y: 65
                        width: 372
                        height: 67
                        visible: true
                        text: mainMenuSplashText
                        font.pixelSize: 50
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Button {
                        id: main_play_button
                        x: 239
                        y: 212
                        width: 334
                        height: 48
                        opacity: 1
                        visible: true
                        text: mainMenuPlayText
                        background: Rectangle {
                            color: parent.down ? buttonClickColor : (parent.hovered ? buttonHoverColor : buttonBgColor)
                            radius: buttonRadius
                        }
                        onClicked: {
                            main_menu.visible = false
                            game_menu.visible = true
                        }
                    }

                    Button {
                        id: main_options_button
                        x: 239
                        y: 282
                        width: 334
                        height: 48
                        visible: true
                        text: mainMenuOptionsText
                        background: Rectangle {
                            color: parent.down ? buttonClickColor : (parent.hovered ? buttonHoverColor : buttonBgColor)
                            radius: buttonRadius
                        }
                        onClicked: {
                            main_menu.visible = false
                            settings_menu.visible = true
                        }
                    }

                    Button {
                        id: main_exit_button
                        x: 239
                        y: 352
                        width: 334
                        height: 48
                        visible: true
                        text: mainMenuExitText
                        background: Rectangle {
                            color: parent.down ? buttonClickColor : (parent.hovered ? buttonHoverColor : buttonBgColor)
                            radius: buttonRadius
                        }
                        onClicked: backend.quit()
                    }
                }
            }

            Page {
                id: settings_menu
                opacity: 1
                anchors.fill: parent
                antialiasing: true
                visible: false
                enabled: true
                Rectangle {
                    color: bgColor
                    width: parent.width
                    height: parent.height
                    visible: true

                    Text {
                        id: settings_label
                        x: 214
                        y: 65
                        width: 372
                        height: 67
                        opacity: 1
                        visible: true
                        text: settingsMenuSplashText
                        font.pixelSize: 50
                        horizontalAlignment: Text.AlignHCenter
                        fontSizeMode: Text.Fit
                    }

                    Label {
                        id: music_label
                        x: 108
                        y: 164
                        width: 186
                        height: 48
                        visible: true
                        color: "#000000"
                        text: settingsMenuMusicVolumeText
                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 20
                    }

                    Label {
                        id: sfx_label
                        x: 108
                        y: 218
                        width: 186
                        height: 48
                        visible: true
                        color: "#000000"
                        text: settingsMenuSfxVolumeText
                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 20
                    }

                    Slider {
                        id: sfx_slider
                        x: 300
                        y: 218
                        width: 286
                        height: 48
                        visible: true
                        antialiasing: true
                        snapMode: RangeSlider.SnapAlways
                        touchDragThreshold: 1
                        stepSize: 1
                        to: 100
                        from: 0
                        value: 1
                    }

                    ComboBox {
                        id: language_box
                        x: 300
                        y: 276
                        width: 199
                        height: 52
                        font.pointSize: 14
                        currentIndex: 0
                        model: ListModel {
                            id: language_list
                            ListElement {
                                text: "English"
                            }
                            ListElement {
                                text: "日本語"
                            }
                        }
                        background: Rectangle {
                            color: parent.down ? buttonClickColor : (parent.hovered ? buttonHoverColor : buttonBgColor)
                            radius: buttonRadius
                        }
                    }

                    Label {
                        id: sfx_label1
                        x: 108
                        y: 276
                        width: 186
                        height: 48
                        visible: true
                        color: "#000000"
                        text: settingsMenuLanguageText
                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 20
                    }

                    Label {
                        id: label
                        x: 585
                        y: 164
                        width: 73
                        height: 48
                        color: "#000000"
                        text: music_slider.value
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 19
                    }

                    Slider {
                        id: music_slider
                        x: 300
                        y: 164
                        width: 286
                        height: 48
                        visible: true
                        snapMode: RangeSlider.SnapAlways
                        enabled: true
                        antialiasing: true
                        touchDragThreshold: 1
                        stepSize: 1
                        to: 100
                        value: 1
                    }

                    Label {
                        id: label1
                        x: 585
                        y: 218
                        width: 73
                        height: 48
                        color: "#000000"
                        text: sfx_slider.value
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 19
                    }

                    Button {
                        id: setttings_back_button
                        x: 299
                        y: 435
                        width: 200
                        height: 40
                        text: backToMainMenuText
                        background: Rectangle {
                            color: parent.down ? buttonClickColor : (parent.hovered ? buttonHoverColor : buttonBgColor)
                            radius: buttonRadius
                        }
						onClicked: {
						    settings_menu.visible = false
							main_menu.visible = true
                        }
                    }

                    Button {
                        id: setttings_save_button
                        x: 300
                        y: 389
                        width: 200
                        height: 40
                        text: settingsMenuSaveText
                        background: Rectangle {
                            color: parent.down ? buttonClickColor : (parent.hovered ? buttonHoverColor : buttonBgColor)
                            radius: buttonRadius
                        }
                    }
                }
            }

            Page {
                id: game_menu
                opacity: 1
                visible: false
                anchors.fill: parent
                enabled: true
                Rectangle {
                    x: 0
                    y: 0
                    color: bgColor
                    antialiasing: true
                    width: parent.width
                    height: parent.height

                    Column {
                        id: column
                        x: 0
                        y: 0
                        width: 200
                        height: 600

                        Rectangle {
                            color: lightBgColor
                            radius: 0
                            border.width: 0
                            width: parent.width
                            height: parent.height
                            Switch {
                                id: katakana_switch
                                x: 0
                                y: 73
                                width: 200
                                height: 48
                                text: gameMenuKatakanaSwitcherText
                                font.pointSize: 14
                                antialiasing: true
                            }

                            Label {
                                id: game_options_label
                                x: 0
                                y: 0
                                width: 200
                                height: 54
                                text: gameMenuOptionsText
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.pointSize: 27
                            }

                            Switch {
                                id: number_row_switch
                                x: 0
                                y: 192
                                width: 200
                                height: 48
                                text: gameMenuNumberRowText
                                antialiasing: true
                                font.pointSize: 14
                                font.bold: true
                                font.family: "Courier"
                            }

                            Switch {
                                id: top_row_switch
                                x: 0
                                y: 246
                                width: 200
                                height: 48
                                text: gameMenuTopRowText
                                antialiasing: true
                                font.pointSize: 14
                                font.bold: true
                                font.family: "Courier"
                            }

                            Label {
                                id: enabled_rows_label
                                x: 0
                                y: 132
                                width: 200
                                height: 54
                                text: gameMenuEnabledRowsText
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.pointSize: 21
                            }

                            Switch {
                                id: middle_row_switch
                                x: 0
                                y: 300
                                width: 200
                                height: 48
                                text: gameMenuMiddleRowText
                                antialiasing: true
                                font.pointSize: 14
                                font.bold: true
                                font.family: "Courier"
                            }

                            Switch {
                                id: bottom_row_switch
                                x: 0
                                y: 354
                                width: 200
                                height: 48
                                text: gameMenuBottomRowText
                                smooth: true
                                antialiasing: true
                                font.pointSize: 14
                                font.bold: true
                                font.family: "Courier"
                            }

                            Button {
                                id: game_back_button
                                x: 8
                                y: 549
                                width: 184
                                height: 48
                                text: backToMainMenuText
                                highlighted: false
                                flat: false
                                antialiasing: true
                                background: Rectangle {
                                    color: parent.down ? buttonClickColor : (parent.hovered ? buttonHoverColor : buttonBgColor)
                                    radius: buttonRadius
                                }
                            }
                        }
                    }

                    Label {
                        id: correct_label
                        x: 212
                        y: 509
                        width: 166
                        height: 19
                        text: gameMenuCorrectText
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignTop
                    }

                    Label {
                        id: wrong_label
                        x: 626
                        y: 509
                        width: 166
                        height: 19
                        text: gameMenuWrongText
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignTop
                    }

                    Label {
                        id: amount_correct_label
                        x: 212
                        y: 534
                        width: 166
                        height: 58
                        text: qsTr("0")
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    Label {
                        id: amount_wrong_label
                        x: 626
                        y: 534
                        width: 166
                        height: 58
                        text: qsTr("0")
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    Button {
                        id: reset_counter_button
                        x: 384
                        y: 509
                        width: 236
                        height: 48
                        text: gameMenuResetText
                        antialiasing: true
                        flat: false
                        highlighted: false
                        background: Rectangle {
                            color: parent.down ? buttonClickColor : (parent.hovered ? buttonPopHoverColor : buttonBgColor)
                            radius: buttonRadius
                        }
                    }

                    Label {
                        id: please_press_label
                        x: 382
                        y: 60
                        text: gameMenuSplashText
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 28
                        font.bold: true
                    }

                    Label {
                        id: current_char_label
                        x: 393
                        y: 140
                        text: qsTr("あ")
                        font.pointSize: 200
                    }
                }
            }
	    }
}
