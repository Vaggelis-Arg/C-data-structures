# Compilation:

To compile the data structures library, follow these steps:

1. Clone this repository to your local machine or download the source code as a ZIP file.

2. Open a terminal or command prompt and navigate to the root directory containing the `Makefile`.

3. Run the following command to build the library:

```bash
 ~ make
```


This will compile all the data structure modules and create a static library named `LibDataStructures.a` in the same directory.

## Usage

To use the library in your C projects, follow these steps:

1. Copy the `LibDataStructures.a` file and the header files from the `../modules` directory to your project folder.

2. Include the required header files in your C source files to access the data structures you want to use. For example, to use the Stack module, include the following line at the top of your C source file:

```bash
#include "<path_to_your_project_folder>/Stack/Stack.h" (Replace <path_to_your_project_folder> with the actual path to your project folder.)
```

##

To clean the object files and the library created during the compilation process, run:

```bash
 ~ make clean
```
