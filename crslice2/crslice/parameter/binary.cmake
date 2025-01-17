set(Script ${PYTHON_MODULES}/textlizer.py)

set(JSONS base.json
		fdm_filament_common.json
		fdm_machine_common.json
		fdm_process_common.json
		)	  

foreach(json ${JSONS})
	set(binary_json ${json}.h)
	
	add_custom_command(
		OUTPUT
			${CMAKE_CURRENT_BINARY_DIR}/${binary_json}
		COMMAND
			"${Python3_EXECUTABLE}" ${Script}
			${CMAKE_CURRENT_SOURCE_DIR}/parameter/base/${json}
			${CMAKE_CURRENT_BINARY_DIR}/${binary_json}
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/parameter/base/${json}
	)

	set_source_files_properties(
		${CMAKE_CURRENT_BINARY_DIR}/${binary_json}
		PROPERTIES GENERATED TRUE
		)
		
	list(APPEND BINARY_JSONS ${CMAKE_CURRENT_BINARY_DIR}/${binary_json})
endforeach()
	
set(KEY_JSONS extruder_keys.json
			  machine_keys.json
			  material_keys.json
			  profile_keys.json
		  )	
foreach(json ${KEY_JSONS})
	set(binary_json ${json}.h)
	
	add_custom_command(
		OUTPUT
			${CMAKE_CURRENT_BINARY_DIR}/${binary_json}
		COMMAND
			"${Python3_EXECUTABLE}" ${Script}
			${CMAKE_CURRENT_SOURCE_DIR}/parameter/keys/${json}
			${CMAKE_CURRENT_BINARY_DIR}/${binary_json}
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/parameter/keys/${json}
	)

	set_source_files_properties(
		${CMAKE_CURRENT_BINARY_DIR}/${binary_json}
		PROPERTIES GENERATED TRUE
		)
		
	list(APPEND BINARY_JSONS ${CMAKE_CURRENT_BINARY_DIR}/${binary_json})
endforeach()

list(APPEND DEFS USE_BINARY_JSON)