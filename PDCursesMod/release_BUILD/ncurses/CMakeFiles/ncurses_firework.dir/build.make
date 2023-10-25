# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD

# Include any dependencies generated for this target.
include ncurses/CMakeFiles/ncurses_firework.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include ncurses/CMakeFiles/ncurses_firework.dir/compiler_depend.make

# Include the progress variables for this target.
include ncurses/CMakeFiles/ncurses_firework.dir/progress.make

# Include the compile flags for this target's objects.
include ncurses/CMakeFiles/ncurses_firework.dir/flags.make

ncurses/CMakeFiles/ncurses_firework.dir/__/demos/firework.c.o: ncurses/CMakeFiles/ncurses_firework.dir/flags.make
ncurses/CMakeFiles/ncurses_firework.dir/__/demos/firework.c.o: /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/demos/firework.c
ncurses/CMakeFiles/ncurses_firework.dir/__/demos/firework.c.o: ncurses/CMakeFiles/ncurses_firework.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object ncurses/CMakeFiles/ncurses_firework.dir/__/demos/firework.c.o"
	cd /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/ncurses && /usr/bin/clang-13 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT ncurses/CMakeFiles/ncurses_firework.dir/__/demos/firework.c.o -MF CMakeFiles/ncurses_firework.dir/__/demos/firework.c.o.d -o CMakeFiles/ncurses_firework.dir/__/demos/firework.c.o -c /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/demos/firework.c

ncurses/CMakeFiles/ncurses_firework.dir/__/demos/firework.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ncurses_firework.dir/__/demos/firework.c.i"
	cd /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/ncurses && /usr/bin/clang-13 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/demos/firework.c > CMakeFiles/ncurses_firework.dir/__/demos/firework.c.i

ncurses/CMakeFiles/ncurses_firework.dir/__/demos/firework.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ncurses_firework.dir/__/demos/firework.c.s"
	cd /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/ncurses && /usr/bin/clang-13 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/demos/firework.c -o CMakeFiles/ncurses_firework.dir/__/demos/firework.c.s

# Object files for target ncurses_firework
ncurses_firework_OBJECTS = \
"CMakeFiles/ncurses_firework.dir/__/demos/firework.c.o"

# External object files for target ncurses_firework
ncurses_firework_EXTERNAL_OBJECTS =

ncurses/firework: ncurses/CMakeFiles/ncurses_firework.dir/__/demos/firework.c.o
ncurses/firework: ncurses/CMakeFiles/ncurses_firework.dir/build.make
ncurses/firework: /usr/lib/x86_64-linux-gnu/libncursesw.so
ncurses/firework: /usr/lib/x86_64-linux-gnu/libformw.so
ncurses/firework: ncurses/CMakeFiles/ncurses_firework.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable firework"
	cd /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/ncurses && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ncurses_firework.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ncurses/CMakeFiles/ncurses_firework.dir/build: ncurses/firework
.PHONY : ncurses/CMakeFiles/ncurses_firework.dir/build

ncurses/CMakeFiles/ncurses_firework.dir/clean:
	cd /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/ncurses && $(CMAKE_COMMAND) -P CMakeFiles/ncurses_firework.dir/cmake_clean.cmake
.PHONY : ncurses/CMakeFiles/ncurses_firework.dir/clean

ncurses/CMakeFiles/ncurses_firework.dir/depend:
	cd /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/ncurses /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/ncurses /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/ncurses/CMakeFiles/ncurses_firework.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : ncurses/CMakeFiles/ncurses_firework.dir/depend

