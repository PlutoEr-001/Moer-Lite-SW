# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\JetBrains\Toolbox\apps\CLion\ch-0\232.8660.186\bin\cmake\win\x64\bin\cmake.exe

# The command to remove a file.
RM = D:\JetBrains\Toolbox\apps\CLion\ch-0\232.8660.186\bin\cmake\win\x64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\plutoEr\CLionProjects\Moer-lite

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\plutoEr\CLionProjects\Moer-lite\cmake-build-debug-mingw

# Include any dependencies generated for this target.
include externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/compiler_depend.make

# Include the progress variables for this target.
include externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/progress.make

# Include the compile flags for this target's objects.
include externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/flags.make

externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/tiny_obj_loader.cc.obj: externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/flags.make
externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/tiny_obj_loader.cc.obj: C:/Users/plutoEr/CLionProjects/Moer-lite/externals/tinyobjloader/tiny_obj_loader.cc
externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/tiny_obj_loader.cc.obj: externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\plutoEr\CLionProjects\Moer-lite\cmake-build-debug-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/tiny_obj_loader.cc.obj"
	cd /d C:\Users\plutoEr\CLionProjects\Moer-lite\cmake-build-debug-mingw\externals\tinyobjloader && C:\Users\plutoEr\Environment\x86_64-8.1.0-release-win32-sjlj-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/tiny_obj_loader.cc.obj -MF CMakeFiles\tinyobjloader.dir\tiny_obj_loader.cc.obj.d -o CMakeFiles\tinyobjloader.dir\tiny_obj_loader.cc.obj -c C:\Users\plutoEr\CLionProjects\Moer-lite\externals\tinyobjloader\tiny_obj_loader.cc

externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/tiny_obj_loader.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinyobjloader.dir/tiny_obj_loader.cc.i"
	cd /d C:\Users\plutoEr\CLionProjects\Moer-lite\cmake-build-debug-mingw\externals\tinyobjloader && C:\Users\plutoEr\Environment\x86_64-8.1.0-release-win32-sjlj-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\plutoEr\CLionProjects\Moer-lite\externals\tinyobjloader\tiny_obj_loader.cc > CMakeFiles\tinyobjloader.dir\tiny_obj_loader.cc.i

externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/tiny_obj_loader.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinyobjloader.dir/tiny_obj_loader.cc.s"
	cd /d C:\Users\plutoEr\CLionProjects\Moer-lite\cmake-build-debug-mingw\externals\tinyobjloader && C:\Users\plutoEr\Environment\x86_64-8.1.0-release-win32-sjlj-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\plutoEr\CLionProjects\Moer-lite\externals\tinyobjloader\tiny_obj_loader.cc -o CMakeFiles\tinyobjloader.dir\tiny_obj_loader.cc.s

# Object files for target tinyobjloader
tinyobjloader_OBJECTS = \
"CMakeFiles/tinyobjloader.dir/tiny_obj_loader.cc.obj"

# External object files for target tinyobjloader
tinyobjloader_EXTERNAL_OBJECTS =

C:/Users/plutoEr/CLionProjects/Moer-lite/target/lib/libtinyobjloader.a: externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/tiny_obj_loader.cc.obj
C:/Users/plutoEr/CLionProjects/Moer-lite/target/lib/libtinyobjloader.a: externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/build.make
C:/Users/plutoEr/CLionProjects/Moer-lite/target/lib/libtinyobjloader.a: externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\plutoEr\CLionProjects\Moer-lite\cmake-build-debug-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library C:\Users\plutoEr\CLionProjects\Moer-lite\target\lib\libtinyobjloader.a"
	cd /d C:\Users\plutoEr\CLionProjects\Moer-lite\cmake-build-debug-mingw\externals\tinyobjloader && $(CMAKE_COMMAND) -P CMakeFiles\tinyobjloader.dir\cmake_clean_target.cmake
	cd /d C:\Users\plutoEr\CLionProjects\Moer-lite\cmake-build-debug-mingw\externals\tinyobjloader && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\tinyobjloader.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/build: C:/Users/plutoEr/CLionProjects/Moer-lite/target/lib/libtinyobjloader.a
.PHONY : externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/build

externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/clean:
	cd /d C:\Users\plutoEr\CLionProjects\Moer-lite\cmake-build-debug-mingw\externals\tinyobjloader && $(CMAKE_COMMAND) -P CMakeFiles\tinyobjloader.dir\cmake_clean.cmake
.PHONY : externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/clean

externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\plutoEr\CLionProjects\Moer-lite C:\Users\plutoEr\CLionProjects\Moer-lite\externals\tinyobjloader C:\Users\plutoEr\CLionProjects\Moer-lite\cmake-build-debug-mingw C:\Users\plutoEr\CLionProjects\Moer-lite\cmake-build-debug-mingw\externals\tinyobjloader C:\Users\plutoEr\CLionProjects\Moer-lite\cmake-build-debug-mingw\externals\tinyobjloader\CMakeFiles\tinyobjloader.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : externals/tinyobjloader/CMakeFiles/tinyobjloader.dir/depend

