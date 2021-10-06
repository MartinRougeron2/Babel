SOURCES   = ./src/GUI/* \
            ./src/client/main.cpp
HEADERS   = ./src/GUI/UserMenu.h \
            ./src/GUI/Contact.h \
            ./src/GUI/App.h \
            ./src/GUI/ModifyPopup.h \
            ./src/GUI/Login.hpp \
            ./src/GUI/ContactLabel.hpp

QT          += widgets

# install
target.path = $$[QT_INSTALL_EXAMPLES]
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS babel_client.pro
sources.path = $$[QT_INSTALL_EXAMPLES]
INSTALLS += target sources


symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
maemo5: include($$QT_SOURCE_TREE/examples/maemo5pkgrules.pri)

symbian: warning(This example might not fully work on Symbian platform)
maemo5: warning(This example might not fully work on Maemo platform)
simulator: warning(This example might not fully work on Simulator platform)