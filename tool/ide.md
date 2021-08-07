# IDE

{% tabs %}
{% tab title='vim' %}

* [enter without key](https://code.visualstudio.com/docs/remote/troubleshooting)
* github1s.com: show github in vscode

> Terms

* workspace: specific to a project and can be shared across developers on a project
  * override user settings

* Icons
  ![img](images/20210214_173530.png)

```json
// wsname.code-workspace
// 1. Mutliple repository in a single workspace
{
  "folders": [
    {
      "path": "."
    },
    {
      "path": "../algorithm"
    },
    {
      "path": "../theory"
    },
    {
      "path": "../language"
    },
  ],
  "settings": {
    "editor.tabSize": 2
  }
}
```

> Example

* How to lint all files?
  * VScode by default only lint openned files, so replace ; -> ; will force lint all files

* Formatting doesn't work
  ![Show debug output](images/20210430_044249.png)

* VSCode doesn't recognize html linting
  * Check files associations in settings

* Error: Waiting for server log... (ssh)
  * rm -rf $HOME/.vscode-server

* Invisible _ in terminal
  * "terminal.integrated.fontSize": 13

{% endtab %}
{% endtabs %}

{% tabs %}
{% tab title='vim' %}

* vscode.Settings.json
  * user level: located in ~/.vscode/settings.json
  * workspace: overwrite user level settings, located in .vscode/settings.json
  ![Do not include git ignored files](images/20210612_124808.png)

* vscode.Cmake Tools
  * Cmake: Reset CMake Tools Extension State
  * configure

  ```json
  // An object containing key : value pairs, which will be passed onto CMake when configuring
  // It does the same thing as passing -DVAR_NAME=ON via cmake.configureArgs.
  {
    "cmake.configureSettings": {"KEY" : "{env:VAR}"}
  }

  // c_cpp_properties.json
  {
    "configurations": [
    {
      "name": "Linux",
      "intelliSenseMode": "gcc-x64",
      "includePath": [
      "${workspaceFolder}/src",
      "${workspaceFolder}/lib",
      "${workspaceFolder}/test",
      "~/SFML-2.5.1/include",
      "/usr/local/include/**",
      "/usr/include/**"
      ],
      "defines": [ "_DEBUG" ],
      "cStandard": "c11",
      "cppStandard": "c++17",
      "forcedInclude": [ "${workspaceFolder}/src/PCH.hpp" ]
    },
    {
      "name": "Mac",
      "intelliSenseMode": "${default}",
      "compilerPath": "/usr/bin/clang",
      "macFrameworkPath": [
      "/Library/Frameworks",
      "/System/Library/Frameworks"
      ],
      "includePath": [
      "${workspaceFolder}/src",
      "${workspaceFolder}/lib",
      "${workspaceFolder}/test",
      "/usr/local/include/**"
      ],
      "defines": [ "_DEBUG" ],
      "cStandard": "c11",
      "cppStandard": "c++17",
      "forcedInclude": [ "${workspaceFolder}/src/PCH.hpp" ]
    },
    {
      "name": "Win32",
      "intelliSenseMode": "gcc-x64",
      "compilerPath": "C:/mingw32/bin/gcc.exe",
      "includePath": [
      "${workspaceFolder}/src",
      "${workspaceFolder}/lib",
      "${workspaceFolder}/test",
      "C:/SFML-2.5.1/include"
      ],
      "defines": [
      "_DEBUG",
      "UNICODE",
      "_UNICODE"
      ],
      "cStandard": "c11",
      "cppStandard": "c++17",
      "forcedInclude": [ "${workspaceFolder}/src/PCH.hpp" ]
    }
    ],
    "version": 4
  }
  ```

{% endtab %}
{% tab title='vim' %}

* vscode.settings.json

  ```json
  {
    // General
    "editor.fontSize": 14, // Controls the font size in pixels
    "editor.rulers": [100], // No rulers are drawn if array is empty
    "editor.wordWrapColumn": 120,
    "editor.formatOnSave": true,
    "files.autoSaveDelay": 1000, // Controls the delay in ms after which a dirty file is saved automatically
    "files.exclude": {                   // don't show in file explorer
      ".vscode/launch.json": true,
      "env/windows/*.sh": true,
      "env/osx/dmg.applescript": true,
      "bin/": true,
      "build/": true,
    },

    // Use environment variable ${env:Name}
    "args": ["${env:USERNAME}"]

    // c++ related
    "C_Cpp.clang_format_style": "file",                            // use .clang-format in current / home directory
    "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools", // use CMakeLists.txt for linting
    "editor.wordWrapColumn": 120,
  }
  ```

* vscode.java extension package
  * java.home: set Java IDK location

  ```json
  "java.home" : "/software/CSE/oracle-java-se-14/jdk-14.0.2"
  ```

* vscode.sort import

  ```json
  "python.formatting.autopep8Args": [
    "--max-line-length=200"
  ],
  "python.linting.pylintArgs": ["--generate-members"],           // disable cv2 warning
  "python.pythonPath": "${workspaceFolder}/env/bin/python3",     // python3 -m venv env
  "python.linting.pylintArgs": [
    "--load-plugins=pylint_django", // for django
    "--rcfile=${workspaceFolder}/.pylintrc"
  ]
  ```

{% endtab %}
{% endtabs %}

* Tasks.json: configured to run scripts, start processes within VS Code without having to enter a command line
  * command: The actual command to execute
  * dependsOn: run other tasks before
  * dependsOrder= "sequence": how task dependencies are executed
  * group: Defines to which group the task belongs
  * label: The task's label used in the user interface
  * options: Override the defaults for env, or shell
    * cwd: Set current directory
  * presentation: control how the Integrated Terminal panel behaves when running tasks
    * reveal = always: whether panel is brought to front (never, silent)
    * focus = false: Controls whether the terminal is taking input focus or not
  * runOptions: Defines when and how a task is run
  * type: either be shell (interpreted as a shell command) or process
  * problemMatcher: (ex: "$gcc")

  ```json
  // 1. differnet settings with env for platform
  {
    "version": "2.0.0",
    "tasks": [
      {
        "type": "npm",
        "script": "build",
        "path": "javascript/embed/2a_redux_todo/",
        "group": "build",
        "problemMatcher": [],
        "label": "npm: build - javascript/embed/2a_redux_todo",
        "detail": "react-scripts build",
        "linux": {
          "options": {
            "env": { "PATH": "${config:terminal.integrated.env.linux.PATH}" }
          }
        },
        "osx": {
          "options": {
            "env": { "PATH": "${config:terminal.integrated.env.osx.PATH}" }
          }
        }
      }
    ],
    // 2. Problem matcher
    "problemMatcher": {
      "owner": "cpp",
      "fileLocation": ["relative", "${workspaceFolder}"],
      "pattern": {
        "regexp": "^(.*):(\\d+):(\\d+):\\s+(warning|error):\\s+(.*)$",
        "file": 1,
        "line": 2,
        "column": 3,
        "severity": 4,
        "message": 5
      }
    }
  }
  ```

* keybinding.json

  ```json
  {
    "key": "cmd+1",
    "command": "type",
    "args": {
      "text": "{% tabs %}\n{% tab title='' %}\n{% endtab %}\n{% endtabs %}"
    },
    "when": "editorTextFocus"
  }
  ```

> Example

* Install
  * Window
    * docs.microsoft.com/en-us/windows/wsl/install-win10
  * Mac
    * $HOME/Library/Application Support/Code/User/settings.json

> Error

* Lagging: Renderer Type dom

## Extension

* vim: Well integrated with vscode (:vs)
  * vim.active
  * vim.mode != : [ex]'Insert'

* docker: show all images and containers

* Remote - Containers

```sh
export PATH="$PATH:$HOME/.vscode-server/bin/<directory with a hash-like name>/bin/"
```

```json
// .devcontainer/devcontainer.json
{
  "image": "mcr.microsoft.com/vscode/devcontainers/typescript-node:0-12",
  "forwardPorts": [3000],
  "extensions": ["dbaeumer.vscode-eslint"]
}
```

* Prettier

```json
// 1. settings.json
"[typescript]": {
  "editor.tabSize": 2,
  "editor.formatOnSave": true,
  "editor.defaultFormatter": "esbenp.prettier-vscode"
}

// 2. .prettierrc
{
  "semi": true,
  "trailingComma": "all",
  "singleQuote": false,
  "printWidth": 80,
  "tabWidth": 4,
  "arrowParens": "avoid"
}
```
