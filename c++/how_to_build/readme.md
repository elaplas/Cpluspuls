# How to build static library 

1. Build object files from c++ files. Object files are intermediate files that are machine binary files and allow us to build files and projects independently.

g++ -c add.cpp -o obj_add.o
g++ -c mult.cpp -o obj_mult.o

2. Make an static library file from object files using archive app commands

ar rcs static_mathlib.a obj_add.o obj_mult.o 

3. Make an executable using static library. The executable file is independent from static library after being built because it contains all information in static library

g++ main.cpp -o independent_main static_mathlib.a -lm


# How to build shared (dynamic) library 

1. Build object files from c++ files. Object files are intermediate files that are machine binary files and allow us to build files and projects independently.

g++ -c add.cpp -o obj_add.o
g++ -c mult.cpp -o obj_mult.o

2. Make shared library file from object files using archive app commands

g++ -shared -fPIC -o shared_mathlib.so obj_add.o obj_mult.o

3. Make an executable using shared library. The executable file is dependent on shared library after being built because it does only contains the path where the shared library lies


g++ main.cpp -o dependent_main ./shared_mathlib.so -lm

hint: "./shared_mathlib.so -lm" adds the information that the shared library "shared_mathlib.so" lies in current directory

# Difference between static and shared libraries

Shared and static libraries are two common ways of organizing and distributing code in C++ and other programming languages. They have significant differences in terms of how they are linked with and used by applications. Here are the key differences between shared (dynamic) and static libraries:

1. **Linking**:

   - **Static Libraries**:
     - Static libraries are linked at compile-time.
     - All the code and dependencies are included in the final executable.
     - The resulting executable is larger because it contains a copy of the library's code.
     - Static libraries are typically denoted by `.a` (on Unix-like systems) or `.lib` (on Windows).

   - **Shared (Dynamic) Libraries**:
     - Shared libraries are linked at runtime.
     - The code is not included in the final executable but is loaded into memory when the program starts or when the library is explicitly loaded.
     - Multiple applications can use the same shared library, saving disk space and memory.
     - Shared libraries are typically denoted by `.so` (on Unix-like systems) or `.dll` (on Windows).

2. **Size**:

   - **Static Libraries**:
     - Increase the size of the executable because they are included in it.
     - Every application using the same static library has its copy of the library code.

   - **Shared (Dynamic) Libraries**:
     - Reduce the size of the executable because they are not included in it.
     - Multiple applications can share a single copy of the library, saving disk space.

3. **Updates and Maintenance**:

   - **Static Libraries**:
     - Require recompilation of the entire application if the library is updated.
     - Each application has its copy of the library, so updating one does not affect the others.

   - **Shared (Dynamic) Libraries**:
     - Can be updated without recompiling the applications.
     - All applications using the shared library benefit from the update.

4. **Load Time**:

   - **Static Libraries**:
     - Faster load time because there is no need to load external libraries at runtime.

   - **Shared (Dynamic) Libraries**:
     - Slightly slower load time because the library needs to be loaded into memory when the application starts.

5. **Portability**:

   - **Static Libraries**:
     - More portable because they do not rely on the presence of external library files.
     - The executable contains all necessary code.

   - **Shared (Dynamic) Libraries**:
     - May require specific library versions or installation of the shared library on the system where the program is run.
     - Dependency on external libraries can make distribution more complex.

6. **Security and Isolation**:

   - **Static Libraries**:
     - Provide better isolation because each application has its copy of the library.
     - Less susceptible to issues caused by library updates.

   - **Shared (Dynamic) Libraries**:
     - Shared libraries can introduce vulnerabilities if not properly managed, as multiple applications may rely on the same code and library versions.

In summary, the choice between static and shared libraries depends on factors like application size, memory usage, ease of updates, and deployment considerations. Static libraries are more straightforward to use but can result in larger executables, while shared libraries offer more efficient resource usage and easier maintenance but require careful management of dependencies. The decision should be based on your specific project requirements.