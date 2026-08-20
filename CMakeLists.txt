if(CONFIG_PMW3610 AND CONFIG_ZMK_SPLIT AND NOT CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
  zephyr_library()
  zephyr_library_sources(src/pmw3610_peripheral_compat.c)
endif()

# The pinned conservative Prospector module has two stale calls to ZMK's
# peripheral_slot_index_for_conn(). Its own slot table is the source of truth
# for display connection state, so redirect those calls in that module only.
# Defer this until all Zephyr modules have created their library targets.
if(CONFIG_SHIELD_PROSPECTOR_ADAPTER)
  function(roba_apply_prospector_compat)
    if(TARGET "..__prospector-zmk-module")
      target_compile_definitions(
        "..__prospector-zmk-module" PRIVATE
        peripheral_slot_index_for_conn=psptr_peripheral_slot_index_for_conn)
      target_compile_options("..__prospector-zmk-module" PRIVATE -Wno-unused-variable)
    else()
      message(FATAL_ERROR "Prospector module target was not created")
    endif()
  endfunction()

  if(COMMAND cmake_language)
    cmake_language(
      DEFER DIRECTORY "${APPLICATION_SOURCE_DIR}"
      CALL roba_apply_prospector_compat)
  else()
    message(FATAL_ERROR "CMake is too old for the Prospector compatibility fix")
  endif()
endif()
