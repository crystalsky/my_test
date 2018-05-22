#include(Qt4Macros)
MACRO (VIRE_QT4_WRAP_UI outfiles)
  QT4_EXTRACT_OPTIONS(ui_files ui_options ${ARGN})
  FOREACH (it ${ui_files})
    GET_FILENAME_COMPONENT(outfile ${it} NAME_WE)
    GET_FILENAME_COMPONENT(infile ${it} ABSOLUTE)

    IF(UI_DESTINATION_DIR)
      SET(outfile ${UI_DESTINATION_DIR}/ui_${outfile}.h)
    ELSE(UI_DESTINATION_DIR)
      SET(outfile ${CMAKE_CURRENT_BINARY_DIR}/ui_${outfile}.h)
    ENDIF(UI_DESTINATION_DIR)
    ADD_CUSTOM_COMMAND(OUTPUT ${outfile}
      COMMAND ${QT_UIC_EXECUTABLE}
      ARGS ${ui_options} -o ${outfile} ${infile}
      MAIN_DEPENDENCY ${infile})
    SET(${outfiles} ${${outfiles}} ${outfile})
  ENDFOREACH (it)

ENDMACRO (VIRE_QT4_WRAP_UI)


MACRO (VIRE_QT4_WRAP_CPP outfiles )
# get include dirs
QT4_GET_MOC_FLAGS(moc_flags)
QT4_EXTRACT_OPTIONS(moc_files moc_options ${ARGN})

FOREACH (it ${moc_files})
  GET_FILENAME_COMPONENT(it ${it} ABSOLUTE)
  QT4_MAKE_OUTPUT_FILE(${it} moc_ cpp outfile)
  QT4_CREATE_MOC_COMMAND(${it} ${outfile} "${moc_flags}" "${moc_options}")
  SET(${outfiles} ${${outfiles}} ${outfile})
ENDFOREACH(it)

ENDMACRO (VIRE_QT4_WRAP_CPP)


MACRO (VIRE_QT4_ADD_RESOURCES outfiles )
    QT4_EXTRACT_OPTIONS(rcc_files rcc_options ${ARGN})

    FOREACH (it ${rcc_files})
      GET_FILENAME_COMPONENT(outfilename ${it} NAME_WE)
      GET_FILENAME_COMPONENT(infile ${it} ABSOLUTE)
      GET_FILENAME_COMPONENT(rc_path ${infile} PATH)
      SET(outfile ${CMAKE_CURRENT_SOURCE_DIR}/qrc_${outfilename}.cpp)

      #  parse file for dependencies 
      #  all files are absolute paths or relative to the location of the qrc file
      FILE(READ "${infile}" _RC_FILE_CONTENTS)
      STRING(REGEX MATCHALL "<file[^<]+" _RC_FILES "${_RC_FILE_CONTENTS}")
      SET(_RC_DEPENDS)
      FOREACH(_RC_FILE ${_RC_FILES})
        STRING(REGEX REPLACE "^<file[^>]*>" "" _RC_FILE "${_RC_FILE}")
        STRING(REGEX MATCH "^/|([A-Za-z]:/)" _ABS_PATH_INDICATOR "${_RC_FILE}")
        IF(NOT _ABS_PATH_INDICATOR)
          SET(_RC_FILE "${rc_path}/${_RC_FILE}")
        ENDIF(NOT _ABS_PATH_INDICATOR)
        SET(_RC_DEPENDS ${_RC_DEPENDS} "${_RC_FILE}")
      ENDFOREACH(_RC_FILE)
      ADD_CUSTOM_COMMAND(OUTPUT ${outfile}
        COMMAND ${QT_RCC_EXECUTABLE}
        ARGS ${rcc_options} -name ${outfilename} -o ${outfile} ${infile}
        MAIN_DEPENDENCY ${infile}
        DEPENDS ${_RC_DEPENDS})
      SET(${outfiles} ${${outfiles}} ${outfile})
    ENDFOREACH (it)

  ENDMACRO (VIRE_QT4_ADD_RESOURCES)