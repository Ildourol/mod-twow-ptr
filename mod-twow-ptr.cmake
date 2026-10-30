# Optional CMake hooks for mod-twow-ptr.
#
# Source files under src/ are discovered automatically,
# conf/*.conf.dist files are copied automatically, and Addmod_twow_ptrScripts()
# (and alias Addmod_twow_ptr_masterScripts()) is invoked by the generated module loader.
#
# This file is included twice by the engine build system:
#   TORTOISE_MODULE_CMAKE_PHASE=DISCOVERY
#   TORTOISE_MODULE_CMAKE_PHASE=POST_TARGETS
#
# Use TW_* helpers for compatibility with Turtle vMaNGOS. Do not use AC_* names.

if(TORTOISE_MODULE_CMAKE_PHASE STREQUAL "DISCOVERY")
  # Module source files under src/ are auto-discovered.
  # Configuration templates under conf/ are auto-copied.
endif()
