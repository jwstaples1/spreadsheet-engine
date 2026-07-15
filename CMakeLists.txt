# CMakeList.txt : CMake project for SpreadsheetEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SpreadsheetEngine")

# Add source to this project's executable.
add_executable (SpreadsheetEngine "SpreadsheetEngine.cpp" "SpreadsheetEngine.h" "src/core/Spreadsheet.cpp" "src/core/Spreadsheet.h"   "src/core/cell/CellAddress.cpp" "src/core/cell/CellAddress.h"  "src/core/cell/CellValue.h" "src/core/cell/ConstantValue.h" "src/core/cell/types/NumericValue.h" "src/core/cell/types/NumericValue.cpp" "src/core/cell/types/StringValue.cpp" "src/core/cell/types/StringValue.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SpreadsheetEngine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

option(WEB "Build as WASM output" OFF)

if(WEB) 

    set_target_properties(SpreadsheetEngine PROPERTIES
        SUFFIX ".html"
    )

    target_link_options(SpreadsheetEngine PRIVATE
        "-sEXPORTED_FUNCTIONS=_main"
        "-sEXPORTED_RUNTIME_METHODS=ccall,cwrap"
    )
endif()

