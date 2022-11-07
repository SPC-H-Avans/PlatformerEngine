function(vcpkg_install_deps)
    cmake_parse_arguments(PARSE_ARGV 0 "arg" "" "MANIFEST_ROOT" "")
    message(STATUS "Running vcpkg install for manifest root ${arg_MANIFEST_ROOT}")
    execute_process(
            COMMAND "${Z_VCPKG_EXECUTABLE}" install
            --triplet "${VCPKG_TARGET_TRIPLET}"
            --vcpkg-root "${Z_VCPKG_ROOT_DIR}"
            "--x-wait-for-lock"
            "--x-manifest-root=${arg_MANIFEST_ROOT}"
            "--x-install-root=${_VCPKG_INSTALLED_DIR}"
            "${Z_VCPKG_FEATURE_FLAGS}"
            ${Z_VCPKG_ADDITIONAL_MANIFEST_PARAMS}
            ${VCPKG_INSTALL_OPTIONS}
            OUTPUT_VARIABLE Z_VCPKG_MANIFEST_INSTALL_LOGTEXT
            ERROR_VARIABLE Z_VCPKG_MANIFEST_INSTALL_LOGTEXT
            RESULT_VARIABLE Z_VCPKG_MANIFEST_INSTALL_RESULT
            ${Z_VCPKG_MANIFEST_INSTALL_ECHO_PARAMS}
    )
    message(STATUS "Running vcpkg install for manifest root ${arg_MANIFEST_ROOT} - done")
endfunction()