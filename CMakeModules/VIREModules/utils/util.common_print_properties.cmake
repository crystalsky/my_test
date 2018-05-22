#.rst:
# COMMON_PRINT_PROPERTIES
# -----------------
#
# Convenience macros for printing properties and variables, useful e.g. for debugging.
#
# ::
#
#  COMMON_PRINT_PROPERTIES([TARGETS target1 ..  targetN]
#                         [SOURCES source1 .. sourceN]
#                         [DIRECTORIES dir1 .. dirN]
#                         [TESTS test1 .. testN]
#                         [CACHE_ENTRIES entry1 .. entryN]
#                         PROPERTIES prop1 .. propN )
#
# This macro prints the values of the properties of the given targets,
# source files, directories, tests or cache entries.  Exactly one of the
# scope keywords must be used.  Example::
#
#    COMMON_PRINT_PROPERTIES(TARGETS foo bar PROPERTIES
#                           LOCATION INTERFACE_INCLUDE_DIRS)
#
# This will print the LOCATION and INTERFACE_INCLUDE_DIRS properties for
# both targets foo and bar.

include(CMakeParseArguments)

function(COMMON_PRINT_PROPERTIES )
  set(options )
  set(oneValueArgs PREFIX)
  set(multiValueArgs TARGETS SOURCES TESTS DIRECTORIES CACHE_ENTRIES PROPERTIES )

  cmake_parse_arguments(CPP "${options}" "${oneValueArgs}" "${multiValueArgs}"  ${ARGN})

  if(CPP_UNPARSED_ARGUMENTS)
    message(FATAL_ERROR "Unknown keywords given to COMMON_print_properties(): \"${CPP_UNPARSED_ARGUMENTS}\"")
    return()
  endif()

  if(NOT CPP_PROPERTIES)
    message(FATAL_ERROR "Required argument PROPERTIES missing in cmake_print_properties() call")
    return()
  endif()

  set(mode)
  set(items)
  set(keyword)

  if(CPP_TARGETS)
    set(items ${CPP_TARGETS})
    set(mode ${mode} TARGETS)
    set(keyword TARGET)
  endif()

  if(CPP_SOURCES)
    set(items ${CPP_SOURCES})
    set(mode ${mode} SOURCES)
    set(keyword SOURCE)
  endif()

  if(CPP_TESTS)
    set(items ${CPP_TESTS})
    set(mode ${mode} TESTS)
    set(keyword TEST)
  endif()

  if(CPP_DIRECTORIES)
    set(items ${CPP_DIRECTORIES})
    set(mode ${mode} DIRECTORIES)
    set(keyword DIRECTORY)
  endif()

  if(CPP_CACHE_ENTRIES)
    set(items ${CPP_CACHE_ENTRIES})
    set(mode ${mode} CACHE_ENTRIES)
    set(keyword CACHE)
  endif()

  if(NOT mode)
    message(FATAL_ERROR "Mode keyword missing in cmake_print_properties() call, must be one of TARGETS SOURCES TESTS DIRECTORIES CACHE_ENTRIES PROPERTIES")
    return()
  endif()

  list(LENGTH mode modeLength)
  if("${modeLength}" GREATER 1)
    message(FATAL_ERROR "Multiple mode keyword used in cmake_print_properties() call, it must be exactly one of TARGETS SOURCES TESTS DIRECTORIES CACHE_ENTRIES PROPERTIES")
    return()
  endif()

  set(_prifix)
  if(NOT CPP_PREFIX)
    set(_prifix "  ")
  else()
    set(_prifix ${CPP_PREFIX})
  endif()

  set(msg "\n")
  foreach(item ${items})

    set(itemExists TRUE)
    if(keyword STREQUAL "TARGET")
      if(NOT TARGET ${item})
      set(itemExists FALSE)
      string(APPEND msg "\n No such TARGET \"${item}\" !\n\n")
      endif()
    endif()

    if (itemExists)
      string(APPEND msg "${_prifix}Properties for ${keyword} ${item}:\n")
      foreach(prop ${CPP_PROPERTIES})

        get_property(propertySet ${keyword} ${item} PROPERTY "${prop}" SET)

        if(propertySet)
          get_property(property ${keyword} ${item} PROPERTY "${prop}")
          string(APPEND msg "${_prifix}  ${item}.${prop} = \"${property}\"\n")
        else()
          string(APPEND msg "${_prifix}   ${item}.${prop} = <NOTFOUND>\n")
        endif()
      endforeach()
    endif()

  endforeach()
  message(STATUS "${msg}")

endfunction()
