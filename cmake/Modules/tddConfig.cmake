INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_TDD tdd)

FIND_PATH(
    TDD_INCLUDE_DIRS
    NAMES tdd/api.h
    HINTS $ENV{TDD_DIR}/include
        ${PC_TDD_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    TDD_LIBRARIES
    NAMES gnuradio-tdd
    HINTS $ENV{TDD_DIR}/lib
        ${PC_TDD_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TDD DEFAULT_MSG TDD_LIBRARIES TDD_INCLUDE_DIRS)
MARK_AS_ADVANCED(TDD_LIBRARIES TDD_INCLUDE_DIRS)

