cmake_minimum_required(VERSION 4.3)
# Project definition.
project(geheim VERSION 1.0.3 DESCRIPTION "Encodes/Decodes specified input stream" LANGUAGES C)
set(VENDOR "Saulnier")
# We are C99 inclined ... for now.
set(CMAKE_C_STANDARD 99)

# Collect files from the source directory.
file(GLOB_RECURSE SOURCES *.c) 
# Make sources part of the project.
add_executable(geheim ${SOURCES})

# define the include (header-) file(s) location.
target_include_directories(geheim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
# Build time binary location.
set_target_properties(geheim PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
# Define clang compiler flags.
target_compile_options(geheim PUBLIC -std=c99 -Wall -Wextra -Wpedantic -g -O3 -MP -MD)
# Define clang libraries needed.
target_link_libraries(geheim PUBLIC crypto)

# Determine instalation  destination locations.
include(GNUInstallDirs)
if(APPLE)
	# macOS
	set(BIN_DEST "bin")
	set(DOC_DEST "share/doc/geheim")
	set(LICENSE_DEST "share/licenses/geheim")
	set(MAN_DEST "share/man/man1")
else()
	# Linux
	set(BIN_DEST ${CMAKE_INSTALL_BINDIR})
	set(DOC_DEST ${CMAKE_INSTALL_DOCDIR})
	set(LICENSE_DEST "share/licenses/geheim")
	set(MAN_DEST ${CMAKE_INSTALL_MANDIR}/man1)
endif()


# Install binary on system.
install(TARGETS geheim DESTINATION ${BIN_DEST})

# Install auxiliaries - documentation.
install(FILES ../doc/README.md DESTINATION ${DOC_DEST})
install(FILES ../doc/geheim.html DESTINATION ${DOC_DEST})
install(FILES ../doc/geheim.pdf DESTINATION ${DOC_DEST})
# Install auxiliaries - license.
install(FILES ../doc/LICENSE DESTINATION ${LICENSE_DEST})
# Install auxiliaries - man page.
install(FILES ../doc/geheim.1 DESTINATION ${MAN_DEST})

