INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_SANDBOX sandbox)

FIND_PATH(
    SANDBOX_INCLUDE_DIRS
    NAMES sandbox/api.h
    HINTS $ENV{SANDBOX_DIR}/include
        ${PC_SANDBOX_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    SANDBOX_LIBRARIES
    NAMES gnuradio-sandbox
    HINTS $ENV{SANDBOX_DIR}/lib
        ${PC_SANDBOX_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SANDBOX DEFAULT_MSG SANDBOX_LIBRARIES SANDBOX_INCLUDE_DIRS)
MARK_AS_ADVANCED(SANDBOX_LIBRARIES SANDBOX_INCLUDE_DIRS)

