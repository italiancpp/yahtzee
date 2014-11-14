cmake_minimum_required(VERSION 2.6)

set(APP_NAME Yahtzee)
project (${APP_NAME})

option(DEBUG_MODE "Debug or release?" ON)

if(DEBUG_MODE)
	set(CMAKE_BUILD_TYPE DEBUG)
else(DEBUG_MODE)
	set(CMAKE_BUILD_TYPE RELEASE)
endif(DEBUG_MODE)

if (MSVC)

	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd")
	SET(CMAKE_CXX_FLAGS_RELEASE "/MT")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
	add_definitions(/D _VARIADIC_MAX=10)

elseif(CYGWIN)

    set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
    set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

elseif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
	set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

endif()

# architecture
if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
	set(ARCH_DIR "64-bit")
else()
	set(ARCH_DIR "32-bit")
endif()

set(CORE_SRC 
	src/Yahtzee/DicePlayer.cpp
	src/Yahtzee/DiceRoller.cpp
	src/Yahtzee/GameState.cpp
	src/Yahtzee/ScoreCalculator.cpp
	src/Yahtzee/ScoreTable.cpp
	src/Yahtzee/ScoreValues.cpp
	src/Yahtzee/GameConfiguration.cpp
	src/Yahtzee/Yahtzee.cpp
	src/Yahtzee/Die.cpp
	src/Yahtzee/PlayerConfiguration.cpp)

# link_directories(/usr/local/lib)

enable_testing()
set(SRC_TEST
	src/test/yahtzee_test.cpp
	src/test/ScoreCalculatorTests.cpp
	src/test/main.cpp
	src/utils/MemoryLeakListener.cpp
	src/utils/debug-new/DebugNew.cpp
	src/utils/debug-new/MemoryLeak.cpp
)

### TESTING TARGET ###
set(GTEST_ROOT ${CMAKE_SOURCE_DIR}/gtest)
include_directories(${GTEST_ROOT}/include)
include_directories(src/utils/debug-new)
add_subdirectory(${GTEST_ROOT})

add_executable(yahtzee_test ${SRC_TEST} ${CORE_SRC})

set_target_properties(yahtzee_test PROPERTIES COMPILE_DEFINITIONS "CHECK_LEAKS")

if ( MSVC )
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od")
endif()

add_test(yahtzee_test yahtzee_test)
if ( WIN32 )
	target_link_libraries(yahtzee_test gtest_main gtest)
else()
	target_link_libraries(yahtzee_test gtest_main gtest pthread)
endif()

########################

### Console Target ###
set(CONSOLE_SRC
	src/console/ConsoleWriter.cpp
	src/console/main.cpp)

add_executable(${APP_NAME} ${CORE_SRC} ${CONSOLE_SRC})
######################

# set(APP_BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

# set_target_properties(${APP_NAME} PROPERTIES
# 	RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")
# set_target_properties(yahtzee_test PROPERTIES
# 	RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")
