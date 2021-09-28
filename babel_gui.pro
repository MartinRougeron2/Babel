SOURCES   = ./src/GUI/ModifyPopup.cpp \
            ./src/GUI/UserMenu.cpp \
            ./src/GUI/Contact.cpp \
            ./src/GUI/App.cpp \
            ./src/server/babel.cpp
HEADERS   = ./include/GUI/UserMenu.h \
            ./include/GUI/Contact.h \
            ./include/GUI/App.h \
            ./include/GUI/ModifyPopup.h

QT          += widgets

# install
target.path = $$[QT_INSTALL_EXAMPLES]
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS babel_gui.pro
sources.path = $$[QT_INSTALL_EXAMPLES]
INSTALLS += target sources



symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
maemo5: include($$QT_SOURCE_TREE/examples/maemo5pkgrules.pri)

symbian: warning(This example might not fully work on Symbian platform)
maemo5: warning(This example might not fully work on Maemo platform)
simulator: warning(This example might not fully work on Simulator platform)