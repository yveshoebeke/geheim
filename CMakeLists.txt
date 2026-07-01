cmake_minimum_required(VERSION 4.3)
# Project definition.
project(geheim VERSION 1.0.3 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Collect files from the source directory.
file(GLOB_RECURSE SOURCES src/*.c) 

# Make sources part of the project.
add_executable(geheim ${SOURCES})

# define the include (header-) file(s) location.
target_include_directories(geheim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

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
	set(HTML_DOC_DEST "share/doc/geheim/html")
	set(PDF_DOC_DEST "share/doc/geheim/pdf")
	set(LICENSE_DEST "share/licenses/geheim")
	set(MAN_DEST "share/man/man1")
else()
	# Linux/Unix
	set(BIN_DEST ${CMAKE_INSTALL_BINDIR})
	set(DOC_DEST ${CMAKE_INSTALL_DOCDIR})
	set(HTML_DOC_DEST ${CMAKE_INSTALL_DOCDIR}/html)
	set(PDF_DOC_DEST ${CMAKE_INSTALL_DOCDIR}/pdf)
	set(LICENSE_DEST "share/licenses/geheim")
	set(MAN_DEST ${CMAKE_INSTALL_MANDIR}/man1)
endif()


# Install binary on system.
install(TARGETS geheim DESTINATION ${BIN_DEST})

# Install auxiliaries - documentation.
install(FILES doc/README.md DESTINATION ${DOC_DEST})
install(FILES doc/html/geheim.html DESTINATION ${HTML_DOC_DEST})
install(FILES doc/pdf/geheim.pdf DESTINATION ${PDF_DOC_DEST})
# Install auxiliaries - license.
install(FILES LICENSE DESTINATION ${LICENSE_DEST})
# Install auxiliaries - man page.
install(FILES doc/man/geheim.1 DESTINATION ${MAN_DEST})

