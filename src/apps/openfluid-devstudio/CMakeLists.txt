

CONFIGURE_FILE(devstudioconfig.hpp.in "${CMAKE_CURRENT_BINARY_DIR}/devstudioconfig.hpp" @ONLY)
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_BINARY_DIR}")

SET(DEVSTUDIO_CPP MainWindow.cpp DevStudioPreferencesManager.cpp)
                     
SET(DEVSTUDIO_HPP MainWindow.hpp DevStudioPreferencesManager.hpp)

QT4_WRAP_UI(DEVSTUDIO_UI MainWindow.ui)

### RESOURCES #

QT4_ADD_RESOURCES(DEVSTUDIO_QRC resources/openfluiddevstudio.qrc)

SET(BUILDER_WIN32RC)

IF(WIN32)
  IF(MINGW)
    # resource compilation for MinGW
    ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources/openfluiddevstudio-win32.o
                       COMMAND windres.exe 
                       ARGS -I${CMAKE_CURRENT_SOURCE_DIR}/resources 
                            -i${CMAKE_CURRENT_SOURCE_DIR}/resources/openfluiddevstudio-win32.rc 
                            -o${CMAKE_CURRENT_BINARY_DIR}/resources/openfluiddevstudio-win32.o)
    SET(DEVSTUDIO_WIN32RC ${CMAKE_CURRENT_BINARY_DIR}/resources/openfluiddevstudio-win32.o)
  ELSE()
    SET(DEVSTUDIO_WIN32RC ${CMAKE_CURRENT_SOURCE_DIR}/resources/openfluiddevstudio-win32.rc)
  ENDIF()
ENDIF()



### MAIN LIB AND EXECUTABLE #

ADD_LIBRARY(openfluid-devstudio-main SHARED ${DEVSTUDIO_CPP} ${DEVSTUDIO_HPP}
                                            ${DEVSTUDIO_UI} ${DEVSTUDIO_QRC})


TARGET_LINK_LIBRARIES(openfluid-devstudio-main 
                      ${QT_QTCORE_LIBRARIES}
                      ${QT_QTGUI_LIBRARIES}
                      openfluid-ui-common
                      openfluid-waresdev
                      openfluid-ui-waresdev
                     )
       
       
                      
SET_TARGET_PROPERTIES(openfluid-devstudio-main PROPERTIES VERSION "${OPENFLUID_VERSION_MAJOR}.${OPENFLUID_VERSION_MINOR}" 
                                        SOVERSION "${OPENFLUID_VERSION_MAJOR}.${OPENFLUID_VERSION_MINOR}.${OPENFLUID_VERSION_PATCH}"
                                        LIBRARY_OUTPUT_DIRECTORY "${OFBUILD_DIST_LIB_DIR}"
                                        RUNTIME_OUTPUT_DIRECTORY "${OFBUILD_DIST_LIB_DIR}"
                                        ARCHIVE_OUTPUT_DIRECTORY "${OFBUILD_DIST_LIB_DIR}"
                                        AUTOMOC ON
                                        COMPILE_DEFINITIONS "OPENFLUID_DLL"
                                        DEFINE_SYMBOL "OPENFLUID_DLL_EXPORTS")


SET(DEVSTUDIO_GUI_OPTION)

IF(WIN32)
  SET(DEVSTUDIO_GUI_OPTION WIN32)
ENDIF()

ADD_EXECUTABLE(openfluid-devstudio ${DEVSTUDIO_GUI_OPTION} main.cpp ${DEVSTUDIO_WIN32RC})

SET_TARGET_PROPERTIES(openfluid-devstudio PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OFBUILD_DIST_BIN_DIR}"
                                                   AUTOMOC ON)


SET_TARGET_PROPERTIES(openfluid-devstudio PROPERTIES OUTPUT_NAME ${OPENFLUID_DEVSTUDIO_APP})


TARGET_LINK_LIBRARIES(openfluid-devstudio
                      openfluid-devstudio-main
                      openfluid-ui-common
                      openfluid-waresdev
                      openfluid-ui-waresdev
                     )
                                   
INSTALL(TARGETS openfluid-devstudio-main
        RUNTIME DESTINATION ${OFBUILD_BIN_INSTALL_PATH}
        LIBRARY DESTINATION ${OFBUILD_LIB_INSTALL_PATH}
        ARCHIVE DESTINATION ${OFBUILD_LIB_INSTALL_PATH})
               
INSTALL(TARGETS openfluid-devstudio
        RUNTIME DESTINATION ${OFBUILD_BIN_INSTALL_PATH})       
      