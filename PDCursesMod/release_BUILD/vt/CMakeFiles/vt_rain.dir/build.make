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
include vt/CMakeFiles/vt_rain.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include vt/CMakeFiles/vt_rain.dir/compiler_depend.make

# Include the progress variables for this target.
include vt/CMakeFiles/vt_rain.dir/progress.make

# Include the compile flags for this target's objects.
include vt/CMakeFiles/vt_rain.dir/flags.make

vt/CMakeFiles/vt_rain.dir/__/demos/rain.c.o: vt/CMakeFiles/vt_rain.dir/flags.make
vt/CMakeFiles/vt_rain.dir/__/demos/rain.c.o: /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/demos/rain.c
vt/CMakeFiles/vt_rain.dir/__/demos/rain.c.o: vt/CMakeFiles/vt_rain.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object vt/CMakeFiles/vt_rain.dir/__/demos/rain.c.o"
	cd /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/vt && /usr/bin/clang-13 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vt/CMakeFiles/vt_rain.dir/__/demos/rain.c.o -MF CMakeFiles/vt_rain.dir/__/demos/rain.c.o.d -o CMakeFiles/vt_rain.dir/__/demos/rain.c.o -c /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/demos/rain.c

vt/CMakeFiles/vt_rain.dir/__/demos/rain.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/vt_rain.dir/__/demos/rain.c.i"
	cd /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/vt && /usr/bin/clang-13 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/demos/rain.c > CMakeFiles/vt_rain.dir/__/demos/rain.c.i

vt/CMakeFiles/vt_rain.dir/__/demos/rain.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/vt_rain.dir/__/demos/rain.c.s"
	cd /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/vt && /usr/bin/clang-13 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/demos/rain.c -o CMakeFiles/vt_rain.dir/__/demos/rain.c.s

# Object files for target vt_rain
vt_rain_OBJECTS = \
"CMakeFiles/vt_rain.dir/__/demos/rain.c.o"

# External object files for target vt_rain
vt_rain_EXTERNAL_OBJECTS =

vt/rain: vt/CMakeFiles/vt_rain.dir/__/demos/rain.c.o
vt/rain: vt/CMakeFiles/vt_rain.dir/build.make
vt/rain: vt/libpdcursesstatic.a
vt/rain: vt/CMakeFiles/vt_rain.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable rain"
	cd /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/vt && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vt_rain.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
vt/CMakeFiles/vt_rain.dir/build: vt/rain
.PHONY : vt/CMakeFiles/vt_rain.dir/build

vt/CMakeFiles/vt_rain.dir/clean:
	cd /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/vt && $(CMAKE_COMMAND) -P CMakeFiles/vt_rain.dir/cmake_clean.cmake
.PHONY : vt/CMakeFiles/vt_rain.dir/clean

vt/CMakeFiles/vt_rain.dir/depend:
	cd /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/vt /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/vt /home/DATA/git/Gecko/HTML/qparse/ManagedObject/llvm_mcjit/PDCursesMod/release_BUILD/vt/CMakeFiles/vt_rain.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : vt/CMakeFiles/vt_rain.dir/depend

