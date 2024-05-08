cmake_minimum_required(VERSION 3.14)

enable_language(CXX)

#--------------------------------------------------------------------------------------------------
# variables
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

set(RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(RESOURCE_DIR_TARGET ${CMAKE_BINARY_DIR}/resources)

set(PROJECT_NAME Reddot)
set(TEST_NAME UnitTest)


#--------------------------------------------------------------------------------------------------
# project
project(${PROJECT_NAME})


#--------------------------------------------------------------------------------------------------
# builds
# project
file(GLOB_RECURSE PROJECT_SOURCE_FILES ${SRC_DIR}/*.*)
file(GLOB_RECURSE RESOURCE_FILES ${RESOURCE_DIR}/*.*)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES} ${RESOURCE_FILES})

if (MSVC)
	# enable VS-Solution filters support
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	set(ALL_FILES ${PROJECT_SOURCE_FILES} ${RESOURCE_FILES})

	# group files by filters for the Visual Studio
	foreach(FILE ${ALL_FILES}) 
		if(FILE IN_LIST PROJECT_SOURCE_FILES)
			set(RELATIVE_DIR ${SRC_DIR})
			set(SOURCE_GROUP "Source Files")
		elseif(FILE IN_LIST RESOURCE_FILES)
			set(RELATIVE_DIR ${RESOURCE_DIR})
			set(SOURCE_GROUP "Resource Files")
		endif()

		file(RELATIVE_PATH REL_FILE ${RELATIVE_DIR} ${FILE})
		get_filename_component(FOLDER ${REL_FILE} PATH)
		string(REPLACE "/" "\\" GROUP "${FOLDER}")

		if("${FILE}" MATCHES ".*\\.cpp")
			source_group("${SOURCE_GROUP}\\${GROUP}" FILES "${FILE}")
		elseif("${FILE}" MATCHES ".*\\.html")
			source_group("${SOURCE_GROUP}\\${GROUP}" FILES "${FILE}")
		elseif("${FILE}" MATCHES ".*\\.h")
			source_group("Header Files\\${GROUP}" FILES "${FILE}")
		elseif("${FILE}" MATCHES ".*\\.*")
			source_group("${SOURCE_GROUP}\\${GROUP}" FILES "${FILE}")
		endif()
	endforeach()
endif(MSVC)

# resources
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${RESOURCE_DIR}
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    COMMENT "Copying resources to build directory"
)

# tests
file(GLOB_RECURSE TEST_SOURCE_FILES ${TEST_DIR}/*.*)
add_executable(${TEST_NAME} ${TEST_SOURCE_FILES})

if (MSVC)
	# enable VS-Solution filters support
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	# group files by filters for the Visual Studio	
	foreach(FILE ${TEST_SOURCE_FILES}) 
		file(RELATIVE_PATH REL_FILE ${TEST_DIR} ${FILE})
		get_filename_component(FOLDER ${REL_FILE} PATH)
		string(REPLACE "/" "\\" GROUP "${FOLDER}")
		if ("${FILE}" MATCHES ".*\\.cpp")
		   source_group("Source Files\\${GROUP}" FILES "${FILE}")
		elseif("${FILE}" MATCHES ".*\\.html")
		   source_group("Resource Files\\${GROUP}" FILES "${FILE}")
		elseif("${FILE}" MATCHES ".*\\.h")
		   source_group("Header Files\\${GROUP}" FILES "${FILE}")
		else()
		   source_group("Resource Files\\${GROUP}" FILES "${FILE}")
		endif()
	endforeach()
endif (MSVC)

# properties
set_target_properties(${PROJECT_NAME} ${TEST_NAME} 
	PROPERTIES
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
)


#--------------------------------------------------------------------------------------------------
# gtest
#
find_package(GTest REQUIRED)

# add src to the include directories for the test target
target_include_directories(${TEST_NAME} 
	PRIVATE
	${SRC_DIR}
	${GTEST_INCLUDE_DIRS}
	${GTEST_LIBRARY} 
	${GTEST_INCLUDE_DIR}
	${GTEST_MAIN_LIBRARY}
)

# link test target against gtest libraries
target_link_libraries(${TEST_NAME} 
	PRIVATE
	GTest::gtest 
	GTest::gtest_main 
	#GTest::gmock 
	#GTest::gmock_main
)


# libs
SET(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS program_options)
find_package(OpenSSL REQUIRED)

if (MSVC)
	find_package(unofficial-libmysql REQUIRED)
	find_package(Poco REQUIRED COMPONENTS Foundation Net NetSSL Crypto Data DataMySQL)

	set(LIBS_DIRS
		${BOOST_INCLUDE_DIRS}
		${OPENSSL_INCLUDE_DIR} 
		${POCO_INCLUDE_DIRS}
	)

	set(LIBS_LINK
		${BOOST_LIBRARIES} 
		Boost::boost
		Boost::program_options
		unofficial::libmysql::libmysql 
		OpenSSL::SSL 
		OpenSSL::Crypto 
		Poco::Foundation 
		Poco::Net 
		Poco::NetSSL 
		Poco::Crypto 
		Poco::Data 
		Poco::DataMySQL
	)
else ()
	find_package(Poco REQUIRED COMPONENTS Foundation Net NetSSL Crypto Data)

	find_library(MYSQL_LIBRARY
		NAMES mysqlclient libmysqlclient
	)
	find_path(MYSQL_INCLUDE_DIR
		NAMES mysql.h
		PATH_SUFFIXES mysql
	)
	find_library(POCO_DATAMYSQL_LIBRARY
		NAMES PocoDataMySQL libPocoDataMySQL
	)

	if (NOT MYSQL_LIBRARY)
		message(FATAL_ERROR "Can't find MySQL lib")
	endif ()
	if (NOT MYSQL_INCLUDE_DIR)
		message(FATAL_ERROR "Can't find MySQL headers")
	endif ()
	if (NOT POCO_DATAMYSQL_LIBRARY)
		message(FATAL_ERROR "Can't find PocoDataMySQL lib")
	endif ()

	set(LIBS_DIRS
		${BOOST_INCLUDE_DIRS}
		${OPENSSL_INCLUDE_DIR} 
		${POCO_INCLUDE_DIRS}
		${MYSQL_INCLUDE_DIR}
	)

	set(LIBS_LINK
		${BOOST_LIBRARIES} 
		Boost::boost
		Boost::program_options
		Poco::Foundation
		Poco::Net
		Poco::NetSSL
		Poco::Crypto
		Poco::Data
		${MYSQL_LIBRARY}
		${POCO_DATAMYSQL_LIBRARY}
	)
endif (MSVC)

target_include_directories(${PROJECT_NAME} PRIVATE ${LIBS_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS_LINK})

target_include_directories(${TEST_NAME} PRIVATE ${LIBS_DIRS})
target_link_libraries(${TEST_NAME} PRIVATE ${LIBS_LINK})


#--------------------------------------------------------------------------------------------------
# compiler settings
if (MSVC)
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")

	add_compile_options("/std:c++latest")
	
	target_compile_options(${PROJECT_NAME} PRIVATE
		/W4
	)
	target_compile_options(${TEST_NAME} PRIVATE
		/W4
	)
else ()
	target_compile_options(${PROJECT_NAME} PRIVATE
		-std=c++23 -Wall -Wextra -pedantic -Werror -Wno-pessimizing-move
	)
	target_compile_options(${TEST_NAME} PRIVATE
		-std=c++23 -Wall -Wextra -pedantic -Werror -Wno-pessimizing-move
	)
endif (MSVC)


#--------------------------------------------------------------------------------------------------
# deb pkg
if (UNIX)
	install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

	set(CPACK_GENERATOR DEB)

	set(CPACK_PACKAGE_VERSION_MAJOR "1")
	set(CPACK_PACKAGE_VERSION_MINOR "0")
	set(CPACK_PACKAGE_VERSION_PATCH "0")

	set(CPACK_PACKAGE_CONTACT 155024765+ProphetRu@users.noreply.github.com)

	include(CPack)
endif (UNIX)


#--------------------------------------------------------------------------------------------------
# testing
enable_testing()
include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
