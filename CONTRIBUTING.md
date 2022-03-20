# Development guidelines

## Workflow

Initial build:

- Compile the project (described in the next section)
- Copy all .dll and .exe files from `build/` to your game directory
- Copy the contents of `bin/` to your game directory

Subsequent builds:

- Compile the project
- Copy all .dll and .exe files from `build/` to your game directory
  (we recommend making a script file to do this)

## Compiling on Ubuntu

- **With Docker**:

    Make sure to install Docker and make, then run `make debug`.
    The binaries should appear in the `build/` directory.

- **Without Docker**:

    This scenario is not officially supported, but you can see how it's done by
    examining `docker/Dockerfile` and `docker/entrypoint.sh` for the external
    dependencies and `meson.build` for the local files, then tailoring your
    system to match the process.

## Compiling on Windows

- **Using WSL**:

    Install WSL (video guide: https://www.youtube.com/watch?v=5RTSlby-l9w)

    - Run Powershell as Administrator
    - Copy and paste the following command: `Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux`
    - Restart the computer
    - Go to Windows App Store
    - Install Ubuntu

    Run WSL and continue with the instructions from the `Compiling on Ubuntu` section.

## Coding conventions

While the existing source code does not conform to the rules because it uses
the original Core Design's naming, new code should adhere to the following
guidelines:

- Variables are `lower_snake_case`
- Global variables are `g_PascalCase`
- Module variables are `m_PascalCase`
- Function names are `Module_PascalCase`
- Macros are `UPPER_SNAKE_CASE`
- Struct names are `UPPER_SNAKE_CASE`
- Struct members are `lower_snake_case`
- Enum names are `UPPER_SNAKE_CASE`
- Enum members are `UPPER_SNAKE_CASE`

Try to avoid global variables, if possible declare them as `static` in the
module you're using them. Changes to original game functionality most often
should be configurable.

Other things:

- We use clang-format to automatically format the code
- We do not omit `{` and `}`
- We use K&R brace style
- We condense `if` expressions into one, so:
    ```
    if (a && b) {
    }
    ```

    and not:

    ```
    if (a) {
        if (b) {
        }
    }
    ```

    If the expressions are extraordinarily complex, we refactor these into
    smaller conditions or functions.

## Code formatting

This project uses `clang-format` to take care of automatic code formatting. To
ensure your code conforms to the standard, please run `make lint` after each
commit. If for some reason you can't run it, don't worry, our CI pipeline will
show you what need to be changed in case of mistakes.

## Branching

We commit via pull requests and avoid committing directly to master, which is
a protected branch. Each pull request should have at least one approval before
merging. We never merge until all discussions are marked as resolved and
generally try to test things before merging. When a remark on the code review
is trivial and the PR author has pushed a fix for it, it should be resolved by
the pull request author. Otherwise we don't mark the discussions as resolved
and give a chance for the reviewer to reply. Once all change requests are
addressed, we should re-request a review from the interested parties.

## New version releases

New version releases happen automatically whenever a new tag is pushed to the
`master` branch with the help of GitHub actions.

## Supported compilers

Please be advised that any build systems that are not the one we use for
automating releases (= mingw-w64) come at user's own risk. They might crash or
even refuse to compile. Pull requests are welcome, but those other toolchains
will be always considered supplementary.
