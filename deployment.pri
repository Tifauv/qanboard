isEmpty(target.path) {
    target.path = /opt/$${TARGET}/bin
    export(target.path)
}
desktop.path = /usr/share/applications
desktop.file = qanboard.desktop
INSTALLS = target desktop

export(INSTALLS)
