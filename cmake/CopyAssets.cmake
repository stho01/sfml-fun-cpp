function(copy_assets_for target)
    foreach(asset IN LISTS ARGN)
        get_filename_component(asset_name "${asset}" NAME)

        # Bestem hvor den skal havne
        if(asset_name STREQUAL "assets")
            # Hvis mappen heter "assets" og kommer fra sample/, kopier til bare assets/
            set(dest "$<TARGET_FILE_DIR:${target}>/assets")
        else()
            # Ellers, f.eks. extensions/assets → assets/extensions/
            set(dest "$<TARGET_FILE_DIR:${target}>/assets/${asset_name}")
        endif()

        add_custom_command(
                TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${asset}"
                "${dest}"
        )

        message(STATUS "📦 Will copy '${asset}' to '${dest}'")
    endforeach()
endfunction()