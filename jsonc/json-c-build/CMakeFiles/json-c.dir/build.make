# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /home/codespace/.local/lib/python3.10/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/codespace/.local/lib/python3.10/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspaces/mc833/jsonc/json-c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/mc833/jsonc/json-c-build

# Include any dependencies generated for this target.
include CMakeFiles/json-c.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/json-c.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/json-c.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/json-c.dir/flags.make

CMakeFiles/json-c.dir/arraylist.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/arraylist.c.o: /workspaces/mc833/jsonc/json-c/arraylist.c
CMakeFiles/json-c.dir/arraylist.c.o: CMakeFiles/json-c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/mc833/jsonc/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/json-c.dir/arraylist.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/json-c.dir/arraylist.c.o -MF CMakeFiles/json-c.dir/arraylist.c.o.d -o CMakeFiles/json-c.dir/arraylist.c.o -c /workspaces/mc833/jsonc/json-c/arraylist.c

CMakeFiles/json-c.dir/arraylist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/arraylist.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/mc833/jsonc/json-c/arraylist.c > CMakeFiles/json-c.dir/arraylist.c.i

CMakeFiles/json-c.dir/arraylist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/arraylist.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/mc833/jsonc/json-c/arraylist.c -o CMakeFiles/json-c.dir/arraylist.c.s

CMakeFiles/json-c.dir/debug.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/debug.c.o: /workspaces/mc833/jsonc/json-c/debug.c
CMakeFiles/json-c.dir/debug.c.o: CMakeFiles/json-c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/mc833/jsonc/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/json-c.dir/debug.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/json-c.dir/debug.c.o -MF CMakeFiles/json-c.dir/debug.c.o.d -o CMakeFiles/json-c.dir/debug.c.o -c /workspaces/mc833/jsonc/json-c/debug.c

CMakeFiles/json-c.dir/debug.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/debug.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/mc833/jsonc/json-c/debug.c > CMakeFiles/json-c.dir/debug.c.i

CMakeFiles/json-c.dir/debug.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/debug.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/mc833/jsonc/json-c/debug.c -o CMakeFiles/json-c.dir/debug.c.s

CMakeFiles/json-c.dir/json_c_version.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/json_c_version.c.o: /workspaces/mc833/jsonc/json-c/json_c_version.c
CMakeFiles/json-c.dir/json_c_version.c.o: CMakeFiles/json-c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/mc833/jsonc/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/json-c.dir/json_c_version.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/json-c.dir/json_c_version.c.o -MF CMakeFiles/json-c.dir/json_c_version.c.o.d -o CMakeFiles/json-c.dir/json_c_version.c.o -c /workspaces/mc833/jsonc/json-c/json_c_version.c

CMakeFiles/json-c.dir/json_c_version.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/json_c_version.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/mc833/jsonc/json-c/json_c_version.c > CMakeFiles/json-c.dir/json_c_version.c.i

CMakeFiles/json-c.dir/json_c_version.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/json_c_version.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/mc833/jsonc/json-c/json_c_version.c -o CMakeFiles/json-c.dir/json_c_version.c.s

CMakeFiles/json-c.dir/json_object.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/json_object.c.o: /workspaces/mc833/jsonc/json-c/json_object.c
CMakeFiles/json-c.dir/json_object.c.o: CMakeFiles/json-c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/mc833/jsonc/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/json-c.dir/json_object.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/json-c.dir/json_object.c.o -MF CMakeFiles/json-c.dir/json_object.c.o.d -o CMakeFiles/json-c.dir/json_object.c.o -c /workspaces/mc833/jsonc/json-c/json_object.c

CMakeFiles/json-c.dir/json_object.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/json_object.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/mc833/jsonc/json-c/json_object.c > CMakeFiles/json-c.dir/json_object.c.i

CMakeFiles/json-c.dir/json_object.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/json_object.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/mc833/jsonc/json-c/json_object.c -o CMakeFiles/json-c.dir/json_object.c.s

CMakeFiles/json-c.dir/json_object_iterator.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/json_object_iterator.c.o: /workspaces/mc833/jsonc/json-c/json_object_iterator.c
CMakeFiles/json-c.dir/json_object_iterator.c.o: CMakeFiles/json-c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/mc833/jsonc/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/json-c.dir/json_object_iterator.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/json-c.dir/json_object_iterator.c.o -MF CMakeFiles/json-c.dir/json_object_iterator.c.o.d -o CMakeFiles/json-c.dir/json_object_iterator.c.o -c /workspaces/mc833/jsonc/json-c/json_object_iterator.c

CMakeFiles/json-c.dir/json_object_iterator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/json_object_iterator.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/mc833/jsonc/json-c/json_object_iterator.c > CMakeFiles/json-c.dir/json_object_iterator.c.i

CMakeFiles/json-c.dir/json_object_iterator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/json_object_iterator.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/mc833/jsonc/json-c/json_object_iterator.c -o CMakeFiles/json-c.dir/json_object_iterator.c.s

CMakeFiles/json-c.dir/json_tokener.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/json_tokener.c.o: /workspaces/mc833/jsonc/json-c/json_tokener.c
CMakeFiles/json-c.dir/json_tokener.c.o: CMakeFiles/json-c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/mc833/jsonc/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/json-c.dir/json_tokener.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/json-c.dir/json_tokener.c.o -MF CMakeFiles/json-c.dir/json_tokener.c.o.d -o CMakeFiles/json-c.dir/json_tokener.c.o -c /workspaces/mc833/jsonc/json-c/json_tokener.c

CMakeFiles/json-c.dir/json_tokener.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/json_tokener.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/mc833/jsonc/json-c/json_tokener.c > CMakeFiles/json-c.dir/json_tokener.c.i

CMakeFiles/json-c.dir/json_tokener.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/json_tokener.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/mc833/jsonc/json-c/json_tokener.c -o CMakeFiles/json-c.dir/json_tokener.c.s

CMakeFiles/json-c.dir/json_util.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/json_util.c.o: /workspaces/mc833/jsonc/json-c/json_util.c
CMakeFiles/json-c.dir/json_util.c.o: CMakeFiles/json-c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/mc833/jsonc/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/json-c.dir/json_util.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/json-c.dir/json_util.c.o -MF CMakeFiles/json-c.dir/json_util.c.o.d -o CMakeFiles/json-c.dir/json_util.c.o -c /workspaces/mc833/jsonc/json-c/json_util.c

CMakeFiles/json-c.dir/json_util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/json_util.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/mc833/jsonc/json-c/json_util.c > CMakeFiles/json-c.dir/json_util.c.i

CMakeFiles/json-c.dir/json_util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/json_util.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/mc833/jsonc/json-c/json_util.c -o CMakeFiles/json-c.dir/json_util.c.s

CMakeFiles/json-c.dir/json_visit.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/json_visit.c.o: /workspaces/mc833/jsonc/json-c/json_visit.c
CMakeFiles/json-c.dir/json_visit.c.o: CMakeFiles/json-c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/mc833/jsonc/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/json-c.dir/json_visit.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/json-c.dir/json_visit.c.o -MF CMakeFiles/json-c.dir/json_visit.c.o.d -o CMakeFiles/json-c.dir/json_visit.c.o -c /workspaces/mc833/jsonc/json-c/json_visit.c

CMakeFiles/json-c.dir/json_visit.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/json_visit.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/mc833/jsonc/json-c/json_visit.c > CMakeFiles/json-c.dir/json_visit.c.i

CMakeFiles/json-c.dir/json_visit.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/json_visit.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/mc833/jsonc/json-c/json_visit.c -o CMakeFiles/json-c.dir/json_visit.c.s

CMakeFiles/json-c.dir/linkhash.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/linkhash.c.o: /workspaces/mc833/jsonc/json-c/linkhash.c
CMakeFiles/json-c.dir/linkhash.c.o: CMakeFiles/json-c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/mc833/jsonc/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/json-c.dir/linkhash.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/json-c.dir/linkhash.c.o -MF CMakeFiles/json-c.dir/linkhash.c.o.d -o CMakeFiles/json-c.dir/linkhash.c.o -c /workspaces/mc833/jsonc/json-c/linkhash.c

CMakeFiles/json-c.dir/linkhash.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/linkhash.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/mc833/jsonc/json-c/linkhash.c > CMakeFiles/json-c.dir/linkhash.c.i

CMakeFiles/json-c.dir/linkhash.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/linkhash.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/mc833/jsonc/json-c/linkhash.c -o CMakeFiles/json-c.dir/linkhash.c.s

CMakeFiles/json-c.dir/printbuf.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/printbuf.c.o: /workspaces/mc833/jsonc/json-c/printbuf.c
CMakeFiles/json-c.dir/printbuf.c.o: CMakeFiles/json-c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/mc833/jsonc/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/json-c.dir/printbuf.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/json-c.dir/printbuf.c.o -MF CMakeFiles/json-c.dir/printbuf.c.o.d -o CMakeFiles/json-c.dir/printbuf.c.o -c /workspaces/mc833/jsonc/json-c/printbuf.c

CMakeFiles/json-c.dir/printbuf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/printbuf.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/mc833/jsonc/json-c/printbuf.c > CMakeFiles/json-c.dir/printbuf.c.i

CMakeFiles/json-c.dir/printbuf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/printbuf.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/mc833/jsonc/json-c/printbuf.c -o CMakeFiles/json-c.dir/printbuf.c.s

CMakeFiles/json-c.dir/random_seed.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/random_seed.c.o: /workspaces/mc833/jsonc/json-c/random_seed.c
CMakeFiles/json-c.dir/random_seed.c.o: CMakeFiles/json-c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/mc833/jsonc/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/json-c.dir/random_seed.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/json-c.dir/random_seed.c.o -MF CMakeFiles/json-c.dir/random_seed.c.o.d -o CMakeFiles/json-c.dir/random_seed.c.o -c /workspaces/mc833/jsonc/json-c/random_seed.c

CMakeFiles/json-c.dir/random_seed.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/random_seed.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/mc833/jsonc/json-c/random_seed.c > CMakeFiles/json-c.dir/random_seed.c.i

CMakeFiles/json-c.dir/random_seed.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/random_seed.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/mc833/jsonc/json-c/random_seed.c -o CMakeFiles/json-c.dir/random_seed.c.s

CMakeFiles/json-c.dir/strerror_override.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/strerror_override.c.o: /workspaces/mc833/jsonc/json-c/strerror_override.c
CMakeFiles/json-c.dir/strerror_override.c.o: CMakeFiles/json-c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/mc833/jsonc/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/json-c.dir/strerror_override.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/json-c.dir/strerror_override.c.o -MF CMakeFiles/json-c.dir/strerror_override.c.o.d -o CMakeFiles/json-c.dir/strerror_override.c.o -c /workspaces/mc833/jsonc/json-c/strerror_override.c

CMakeFiles/json-c.dir/strerror_override.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/strerror_override.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/mc833/jsonc/json-c/strerror_override.c > CMakeFiles/json-c.dir/strerror_override.c.i

CMakeFiles/json-c.dir/strerror_override.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/strerror_override.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/mc833/jsonc/json-c/strerror_override.c -o CMakeFiles/json-c.dir/strerror_override.c.s

CMakeFiles/json-c.dir/json_pointer.c.o: CMakeFiles/json-c.dir/flags.make
CMakeFiles/json-c.dir/json_pointer.c.o: /workspaces/mc833/jsonc/json-c/json_pointer.c
CMakeFiles/json-c.dir/json_pointer.c.o: CMakeFiles/json-c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/mc833/jsonc/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/json-c.dir/json_pointer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/json-c.dir/json_pointer.c.o -MF CMakeFiles/json-c.dir/json_pointer.c.o.d -o CMakeFiles/json-c.dir/json_pointer.c.o -c /workspaces/mc833/jsonc/json-c/json_pointer.c

CMakeFiles/json-c.dir/json_pointer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-c.dir/json_pointer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/mc833/jsonc/json-c/json_pointer.c > CMakeFiles/json-c.dir/json_pointer.c.i

CMakeFiles/json-c.dir/json_pointer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-c.dir/json_pointer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/mc833/jsonc/json-c/json_pointer.c -o CMakeFiles/json-c.dir/json_pointer.c.s

# Object files for target json-c
json__c_OBJECTS = \
"CMakeFiles/json-c.dir/arraylist.c.o" \
"CMakeFiles/json-c.dir/debug.c.o" \
"CMakeFiles/json-c.dir/json_c_version.c.o" \
"CMakeFiles/json-c.dir/json_object.c.o" \
"CMakeFiles/json-c.dir/json_object_iterator.c.o" \
"CMakeFiles/json-c.dir/json_tokener.c.o" \
"CMakeFiles/json-c.dir/json_util.c.o" \
"CMakeFiles/json-c.dir/json_visit.c.o" \
"CMakeFiles/json-c.dir/linkhash.c.o" \
"CMakeFiles/json-c.dir/printbuf.c.o" \
"CMakeFiles/json-c.dir/random_seed.c.o" \
"CMakeFiles/json-c.dir/strerror_override.c.o" \
"CMakeFiles/json-c.dir/json_pointer.c.o"

# External object files for target json-c
json__c_EXTERNAL_OBJECTS =

libjson-c.so.5.2.0: CMakeFiles/json-c.dir/arraylist.c.o
libjson-c.so.5.2.0: CMakeFiles/json-c.dir/debug.c.o
libjson-c.so.5.2.0: CMakeFiles/json-c.dir/json_c_version.c.o
libjson-c.so.5.2.0: CMakeFiles/json-c.dir/json_object.c.o
libjson-c.so.5.2.0: CMakeFiles/json-c.dir/json_object_iterator.c.o
libjson-c.so.5.2.0: CMakeFiles/json-c.dir/json_tokener.c.o
libjson-c.so.5.2.0: CMakeFiles/json-c.dir/json_util.c.o
libjson-c.so.5.2.0: CMakeFiles/json-c.dir/json_visit.c.o
libjson-c.so.5.2.0: CMakeFiles/json-c.dir/linkhash.c.o
libjson-c.so.5.2.0: CMakeFiles/json-c.dir/printbuf.c.o
libjson-c.so.5.2.0: CMakeFiles/json-c.dir/random_seed.c.o
libjson-c.so.5.2.0: CMakeFiles/json-c.dir/strerror_override.c.o
libjson-c.so.5.2.0: CMakeFiles/json-c.dir/json_pointer.c.o
libjson-c.so.5.2.0: CMakeFiles/json-c.dir/build.make
libjson-c.so.5.2.0: CMakeFiles/json-c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/mc833/jsonc/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking C shared library libjson-c.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/json-c.dir/link.txt --verbose=$(VERBOSE)
	$(CMAKE_COMMAND) -E cmake_symlink_library libjson-c.so.5.2.0 libjson-c.so.5 libjson-c.so

libjson-c.so.5: libjson-c.so.5.2.0
	@$(CMAKE_COMMAND) -E touch_nocreate libjson-c.so.5

libjson-c.so: libjson-c.so.5.2.0
	@$(CMAKE_COMMAND) -E touch_nocreate libjson-c.so

# Rule to build all files generated by this target.
CMakeFiles/json-c.dir/build: libjson-c.so
.PHONY : CMakeFiles/json-c.dir/build

CMakeFiles/json-c.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/json-c.dir/cmake_clean.cmake
.PHONY : CMakeFiles/json-c.dir/clean

CMakeFiles/json-c.dir/depend:
	cd /workspaces/mc833/jsonc/json-c-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/mc833/jsonc/json-c /workspaces/mc833/jsonc/json-c /workspaces/mc833/jsonc/json-c-build /workspaces/mc833/jsonc/json-c-build /workspaces/mc833/jsonc/json-c-build/CMakeFiles/json-c.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/json-c.dir/depend

