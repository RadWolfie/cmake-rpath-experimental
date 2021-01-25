cmake_minimum_required (VERSION 3.9)

# create library binary
project(cmake_lib LANGUAGES C)
list(APPEND projects ${PROJECT_NAME})

message("--- DEFAULTS ---")
message("CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
# doc: https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html
include(GNUInstallDirs)
message("CMAKE_INSTALL_BINDIR: ${CMAKE_INSTALL_BINDIR}")
message("CMAKE_INSTALL_DATADIR: ${CMAKE_INSTALL_DATADIR}")
message("CMAKE_INSTALL_DATAROOTDIR: ${CMAKE_INSTALL_DATAROOTDIR}")
message("CMAKE_INSTALL_DOCDIR: ${CMAKE_INSTALL_DOCDIR}")
message("CMAKE_INSTALL_INCLUDEDIR: ${CMAKE_INSTALL_INCLUDEDIR}")
message("CMAKE_INSTALL_INFODIR: ${CMAKE_INSTALL_INFODIR}")
message("CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")
message("CMAKE_INSTALL_LIBEXECDIR: ${CMAKE_INSTALL_LIBEXECDIR}")
message("CMAKE_INSTALL_LOCALEDIR: ${CMAKE_INSTALL_LOCALEDIR}")
message("CMAKE_INSTALL_LOCALSTATEDIR: ${CMAKE_INSTALL_LOCALSTATEDIR}")
message("CMAKE_INSTALL_MANDIR: ${CMAKE_INSTALL_MANDIR}")
message("CMAKE_INSTALL_OLDINCLUDEDIR: ${CMAKE_INSTALL_OLDINCLUDEDIR}")
message("CMAKE_INSTALL_SBINDIR: ${CMAKE_INSTALL_SBINDIR}")
message("CMAKE_INSTALL_SHAREDSTATEDIR: ${CMAKE_INSTALL_SHAREDSTATEDIR}")
message("CMAKE_INSTALL_SYSCONFDIR: ${CMAKE_INSTALL_SYSCONFDIR}")
message("---")

# list of references for how to use RPATH:
# - https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/RPATH-handling
# - https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html?highlight=RPATH
message("--- SETUP RPATH (BEFORE)---")
message("CMAKE_BUILD_RPATH: ${CMAKE_BUILD_RPATH}")
message("CMAKE_INSTALL_RPATH: ${CMAKE_INSTALL_RPATH}")
message("CMAKE_BUILD_WITH_INSTALL_RPATH: ${CMAKE_BUILD_WITH_INSTALL_RPATH}")
message("CMAKE_MACOSX_RPATH: ${CMAKE_MACOSX_RPATH}")
message("MACOSX_RPATH: ${MACOSX_RPATH}")
message("---")

# setup rpath to where binary is at.
if(APPLE)
 set(CMAKE_INSTALL_RPATH "@executable_path")
else()
 set(CMAKE_INSTALL_RPATH "$ORIGIN")
endif()
set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
# fix shared library warning (only for below CMake 3.9)
#set(CMAKE_MACOSX_RPATH ON)

message("--- SETUP RPATH (AFTER) ---")
message("CMAKE_INSTALL_RPATH: ${CMAKE_INSTALL_RPATH}")
message("CMAKE_BUILD_WITH_INSTALL_RPATH: ${CMAKE_BUILD_WITH_INSTALL_RPATH}")
message("CMAKE_MACOSX_RPATH: ${CMAKE_MACOSX_RPATH}")
message("MACOSX_RPATH: ${MACOSX_RPATH}")
message("---")

add_library(${PROJECT_NAME} SHARED include/library.h library.c)

target_compile_definitions(${PROJECT_NAME}
 PRIVATE $<$<C_COMPILER_ID:MSVC>:DLL_API=__declspec\(dllexport\)>
)
#endif()

target_include_directories(${PROJECT_NAME}
 PUBLIC "include"
)

# create main binary
project(cmake_bin LANGUAGES C)
list(APPEND projects ${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.c)

target_compile_definitions(${PROJECT_NAME}
 PRIVATE $<$<C_COMPILER_ID:MSVC>:DLL_API=__declspec\(dllimport\)>
)

target_link_libraries(${PROJECT_NAME} PRIVATE cmake_lib)

add_dependencies(${PROJECT_NAME} cmake_lib)

install(TARGETS ${projects}
 RUNTIME DESTINATION .
 LIBRARY DESTINATION .
)
