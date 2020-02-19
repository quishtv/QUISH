CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/forms ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/forms ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings/forms)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif ()

find_package(Qrcode)
if (QRCODE_FOUND)
    include_directories ( ${QRCODE_INCLUDE_DIR} )
    link_directories ( ${QRCODE_LIBRARY_DIRS} )
endif()

unset(Qt5Enables)
foreach(comp Widgets Core Gui Network LinguistTools DBus Svg Charts)
    find_package(Qt5${comp})
    set(Qt5Enables "${Qt5Enables};Qt5${comp}_FOUND")
    if(Qt5${comp}_FOUND)
        MESSAGE(STATUS "FOUND QT5${comp}")
        include_directories(${include_directories} ${Qt5${comp}_INCLUDE_DIRS} ${QT_USE_FILE})
        add_definitions(${Qt5${comp}_DEFINITIONS})
        list(APPEND Qt5_LIBRARIES ${Qt5${comp}_LIBRARIES})
    else()
        MESSAGE(WARNING "Cant find Qt5${comp}")
    endif()
endforeach(comp)

if (Qt5DBus_FOUND)
    add_compile_options("-DUSE_DBUS")
endif()

if (Qt5Charts_FOUND)
    add_compile_options("-DUSE_QTCHARTS")
endif()

find_program(MOC_BIN NAMES moc moc-qt5 qt5-moc
        PATHS /usr/lib/qt5/bin /usr/lib/x86_64-linux-gnu/qt5/bin /usr/local/opt/qt/bin /usr/local/opt/qt5/bin
        NO_DEFAULT_PATH
        NO_SYSTEM_ENVIRONMENT_PATH)
if (MOC_BIN)
    MESSAGE(STATUS "FOUND MOC ${MOC_BIN}")

endif ()

# Why isn't this done automatically??
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_AUTOMOC_MOC_OPTIONS "-DQ_OS_MAC")
endif()

file(GLOB LOCAL_QT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
source_group("QtHeaders" FILES ${LOCAL_QT_HEADERS})

find_package(Protobuf REQUIRED)
if(Protobuf_FOUND)
    message(STATUS "Found Protobuf compiler: ${Protobuf_PROTOC_EXECUTABLE}")
    message(STATUS "Found Protobuf library: ${Protobuf_LIBRARIES}")
endif()
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/paymentrequest.proto)

SET(QT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/bantablemodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/blockexplorer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/bitcoinaddressvalidator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/bitcoinamountfield.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/bitcoinunits.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/clientmodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/csvmodelwriter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/governancepage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/guiutil.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/intro.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/networkstyle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/notificator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/optionsdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/optionsmodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/peertablemodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/platformstyle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/qvalidatedlineedit.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/qvaluecombobox.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rpcconsole.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/splashscreen.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/trafficgraphwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utilitydialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/addressbookpage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/addresstablemodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/askpassphrasedialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/coincontroldialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zQTVcontroldialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/coincontroltreewidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/proposalframe.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/editaddressdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/openuridialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/paymentrequestplus.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/paymentserver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/recentrequeststablemodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/transactiondesc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/transactionfilterproxy.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/transactionrecord.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/transactiontablemodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/walletmodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/walletmodeltransaction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zQTVcontroldialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/QUISHgui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/loadingdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/pwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/guitransactionsutils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/snackbar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/navmenuwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/lockunlock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/receivedialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/furabstractlistitemdelegate.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/txviewholder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/qtutils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/expandablebutton.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/walletpassworddialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/topbar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/txrow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/addressfilterproxymodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/dashboardwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/coincontrolQTVwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/addresslabelrow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/contactdropdownrow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/contactsdropdown.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/optionbutton.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/mninfodialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/coldstakingmodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/mnmodel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/masternodewizarddialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/mnrow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/masternodeswidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/sendchangeaddressdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/sendconfirmdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/sendcustomfeedialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/sendchangeaddressdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/sendmultirow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/send.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/addnewaddressdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/addnewcontactdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/requestdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/receivewidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/myaddressrow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/csrow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/addressholder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/tooltipmenu.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/addresseswidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/defaultdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/coldstakingwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings/settingsbackupwallet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings/settingsbittoolwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings/settingsconsolewidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings/settingsdisplayoptionswidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings/settingsfaqwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings/settingsinformationwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings/settingsmainoptionswidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings/settingsmultisenddialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings/settingsmultisendwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings/settingssignmessagewidgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings/settingswalletoptionswidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings/settingswalletrepairwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings/settingswidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/welcomecontentwidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/splash.cpp
        )

# Workaround until the old rpcconsole UI window is fully removed
set_property(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings/settingsconsolewidget.cpp PROPERTY SKIP_AUTOMOC ON)
execute_process(
        COMMAND ${MOC_BIN} -o moc_settingsconsolewidget.cpp settingsconsolewidget.h
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings
)

execute_process(
        COMMAND ${MOC_BIN} -o moc_pfborderimage.cpp pfborderimage.h
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/QUISH
)
list(APPEND QT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/moc_pfborderimage.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    list(APPEND QT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/macdockiconhandler.mm)
    list(APPEND QT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/macnotificationhandler.mm)
endif()

add_library(qt_stuff STATIC ${BitcoinHeaders} ${QtHeaders} ${QT_SOURCES} ${PROTO_SRCS} ${PROTO_HDRS})
target_include_directories(qt_stuff PUBLIC ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/leveldb/include
        ${CMAKE_SOURCE_DIR}/src/univalue/include
        ${CMAKE_SOURCE_DIR}/src/secp256k1/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH
        ${CMAKE_CURRENT_SOURCE_DIR}/QUISH/settings
        ${OPENSSL_INCLUDE_DIR}
        ${BerkeleyDB_INCLUDE_DIRS}
        )
set_property(TARGET qt_stuff PROPERTY CXX_STANDARD 11)

file(GLOB QT_TRANSLATIONS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/locale/*.ts)

get_filename_component(QM_FILES_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/locale" ABSOLUTE)
set_source_files_properties(${QT_TRANSLATIONS_FILES} PROPERTIES OUTPUT_LOCATION "${QM_FILES_BINARY_DIR}")

QT5_ADD_TRANSLATION(QM ${QT_TRANSLATIONS_FILES})
add_custom_target(translations_target ALL DEPENDS ${QM})

QT5_ADD_RESOURCES(QRC_RESOURCE QUISH.qrc)
QT5_ADD_RESOURCES(QRC_LOCALE_RESOURCE QUISH_locale.qrc)

add_executable(QUISH-qt QUISH.cpp ${QM} ${QRC_RESOURCE} ${QRC_LOCALE_RESOURCE})
add_dependencies(QUISH-qt translations_target libunivalue libsecp256k1 leveldb leveldb_sse42 memenv)
target_include_directories(QUISH-qt PUBLIC ${ENDIAN_INCLUDES})
target_link_libraries(QUISH-qt
        qt_stuff
        univalue
        SERVER_A UTIL_A WALLET_A CLI_A COMMON_A BITCOIN_CRYPTO_A ZEROCOIN_A
        leveldb leveldb_sse42 memenv secp256k1
        ${BerkeleyDB_LIBRARIES} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${PROTOBUF_LIBRARIES} ${LIBEVENT_LIB}
        pthread
        )
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(QUISH-qt "-framework Cocoa")
endif()
if(GMP_FOUND)
    target_link_libraries(QUISH-qt ${GMP_LIBRARY})
    target_include_directories(QUISH-qt PUBLIC ${GMP_INCLUDE_DIR})
endif()
if(ZMQ_FOUND)
    target_link_libraries(QUISH-qt ZMQ_A ${ZMQ_LIB})
    target_include_directories(QUISH-qt PUBLIC ${ZMQ_INCLUDE_DIR})
endif()
if (QRCODE_FOUND)
    target_link_libraries(QUISH-qt ${QRCODE_LIB})
    target_include_directories(QUISH-qt PUBLIC ${QRCODE_INCLUDE_DIR})
endif()
if(MINIUPNP_FOUND)
    target_compile_definitions(QUISH-qt PUBLIC "-DSTATICLIB -DMINIUPNP_STATICLIB")
    target_link_libraries(QUISH-qt ${MINIUPNP_LIBRARY})
    target_include_directories(QUISH-qt PUBLIC ${MINIUPNP_INCLUDE_DIR})
endif()

target_link_libraries(QUISH-qt Qt5::Gui Qt5::Core Qt5::Widgets Qt5::Network Qt5::Svg ${QT_LIBRARIES})
if (Qt5DBus_FOUND)
    target_link_libraries(QUISH-qt Qt5::DBus ${QT_LIBRARIES})
endif()
if (Qt5Charts_FOUND)
    target_link_libraries(QUISH-qt Qt5::Charts ${QT_LIBRARIES})
endif()
