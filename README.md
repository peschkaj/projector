# Projector

Generate C++ projects and project files on the fly.

## Usage

`projector <verb> <noun>`

### Commands

`projector new <project>`
`projector generate <class>`

## Creating a new project

`projector new <project>`

Creates a new project as a child of the current directory.

1. Initializes a git repository.
2. Copies in project templates from a template directory.
2. Creates a `CMakeLists.txt` file and completes information in the file.


### Options

- `--template-dir=<path>` Template folder to use for generating a new project.
- `--build-type=<build-type>` Sets the make build type, defaults to `debug`. See [CMake Useful Variables][1] for a list of all options.
- `--boost` Adds basic Boost support to `CMakeLists.txt`
- `--boost-version` Require a specific version of Boost to be present
- `--boost-components=<csv,of,boost,components>` Adds a list of Boost components to the `find_package` portion of

**TODO** allow variadic `--cmake-option=CMAKE_OPTION_GOES_HERE:VALUE` to be passed in.



[1]: https://cmake.org/Wiki/CMake_Useful_Variables
