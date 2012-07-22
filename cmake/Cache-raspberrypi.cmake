# MARSHMALLOW
set(MARSHMALLOW_BUILD_TITLE "Marshmallow Raspberry Pi" CACHE STRING "")

set(MARSHMALLOW_VIEWPORT_WIDTH     "720" CACHE STRING "")
set(MARSHMALLOW_VIEWPORT_HEIGHT    "480" CACHE STRING "")
set(MARSHMALLOW_VIEWPORT_DEPTH     "24"  CACHE STRING "")
set(MARSHMALLOW_VIEWPORT_REFRESH   "60"  CACHE STRING "")
set(MARSHMALLOW_VIEWPORT_FULLSCREEN ON   CACHE BOOL   "")

set(MARSHMALLOW_VIEWPORT_GRAB_INPUT ON   CACHE BOOL   "")

set(MARSHMALLOW_VIEWPORT_DUMMY      OFF  CACHE BOOL   "")
set(MARSHMALLOW_VIEWPORT_OPENGL     ON   CACHE BOOL   "")

set(MARSHMALLOW_OPENGL_EGL          ON   CACHE BOOL   "")
set(MARSHMALLOW_OPENGL_ES2          ON   CACHE BOOL   "")
set(MARSHMALLOW_OPENGL_VC           ON   CACHE BOOL   "")

set(MARSHMALLOW_WITH_BOX2D          ON   CACHE BOOL   "")
set(MARSHMALLOW_WITH_LUA            OFF  CACHE BOOL   "")

# CMAKE
set(CMAKE_C_FLAGS "-mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard"   CACHE STRING "")
set(CMAKE_C_FLAGS_RELEASE "-fomit-frame-pointer"                    CACHE STRING "")
set(CMAKE_CXX_FLAGS "-mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard" CACHE STRING "")
set(CMAKE_CXX_FLAGS_RELEASE "-fomit-frame-pointer"                  CACHE STRING "")

set(CMAKE_FIND_ROOT_PATH   "/opt/vc"           CACHE INTERNAL "")
set(CMAKE_SKIP_BUILD_RPATH  FALSE              CACHE INTERNAL "")
set(CMAKE_INSTALL_RPATH    "./lib:/opt/vc/lib" CACHE STRING   "")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE    CACHE INTERNAL "")
set(CMAKE_BUILD_WITH_INSTALL_RPATH    TRUE     CACHE INTERNAL "")

