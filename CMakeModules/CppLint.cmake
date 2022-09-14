find_package(PythonInterp)

set(CPPLINT_VERSION "1.5.5")

if(PYTHONINTERP_FOUND AND NOT CPPLINT_FOUND)
  file(DOWNLOAD "https://github.com/cpplint/cpplint/archive/refs/tags/${CPPLINT_VERSION}.tar.gz" "${CMAKE_CURRENT_BINARY_DIR}/cpplint.tar.gz")
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar xz cpplint.tar.gz
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  set(CPPLINT_COMMAND "${CMAKE_CURRENT_BINARY_DIR}/cpplint-${CPPLINT_VERSION}/cpplint.py" CACHE FILEPATH "CppLint command")
  set(CPPLINT_FOUND ON CACHE BOOL "CppLint found")
endif()

function(enable_check_style)
  if(CPPLINT_FOUND)
    add_custom_target(check_style)
  endif()
endfunction()

function(target_check_style TARGET)
  if(CPPLINT_FOUND)
    get_target_property(TARGET_SOURCES ${TARGET} SOURCES)

    set(TARGET_NAME "check_style_${TARGET}")

    set(SOURCES_LIST)
    foreach(sourcefile ${TARGET_SOURCES})
        if(sourcefile MATCHES \\.c$|\\.cxx$|\\.cpp$|\\.cc$|\\.h$|\\.hh$)
            list(APPEND SOURCES_LIST ${sourcefile})
        endif()
    endforeach(sourcefile)

    add_custom_target(${TARGET_NAME} ${PYTHON_EXECUTABLE} ${CPPLINT_COMMAND} "--quiet" ${SOURCES_LIST}
                      DEPENDS ${SOURCES_LIST}
                      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    add_dependencies(check_style ${TARGET_NAME})
    set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "check_style")
  endif()
endfunction()

enable_check_style()
