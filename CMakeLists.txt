project(stats)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

set(SOURCE_FILES
	src/ConsolePresenter.cpp
	src/DataCollection.cpp
	src/DataGroup.cpp
	src/DataGroupTable.cpp
)

add_library(stats STATIC ${SOURCE_FILES})
