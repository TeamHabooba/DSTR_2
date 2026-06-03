cmake_minimum_required (VERSION 4.0)

# Turning on MSVC compiler hot reload, if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("DSTR" LANGUAGES CXX)

# Uncomment the line below to specify Git executable location if necessary
#set(GIT_EXECUTABLE "C:/Program Files/Git/bin/git.exe") 

# Shortcut to source directory
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# All executables as a list
set(SOURCES

  "${SRC_DIR}/Source.cpp"

)


add_executable (DSTR ${SOURCES})

set_target_properties(DSTR PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(DSTR PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(DSTR PRIVATE ${SRC_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DSTR PROPERTY CXX_STANDARD 20)
endif()
