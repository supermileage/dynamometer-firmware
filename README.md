# dynamometer-firmware

## Cloning the repo

This repository uses submodules, so to clone you must enter the command:

```
git clone --recurse-submodules <ENTER HTML OR SSH ADDRESS HERE>
```

If you have already cloned the repo, then you can navigate to your local copy of the repo and enter

```
git submodule init
git submodule update
```
## Building the Project
If you haven't already, install vscode and the platformIO extension for vscode (through the extension management tool).  Once these are installed, open the project folder.  PlatformIO will automatically start downloading and installing the packages and libraries needed to build this project.  This will take some time, maybe ~20 minutes.

Once the packages are installed, you can click the PlatformIO:build (checkmark) icon in the bottom left of your vscode window.

### Windows Users
Before opening the repo in vscode with the platformIO extension, make sure to run the git command:
```
git config --system core.longpaths true
```
If you have attempted to open the project with platformIO before running the above command, you may need to delete your platformIO cache, which can be found here:
```
C:\Users\myuser\.platformio\.cache
```

## Unit Tests
### Running the tests
The simplest way to run this project's unit tests is to open a terminal in the project's root folder and run:
```
make run-tests
```

### Windows users
Currently, the tests won't compile natively on windows (because they include ```<unistd.h>``` among other filesystem libraries), so windows users will either have to build and run the tests through wsl, or modify the test source files so they can be compiled and run natively.

To compile and run the tests with wls, open a wsl terminal instance in the project's root folder and run the above command.  Make sure you are running the latest version of wsl2.

Note that you must install gcc to run (and optionally gdb for debugging) the tests.  This can be done with the following command:

```
sudo apt-get install build-essential gdb -y
```

### macOS users

If you haven't already, you will need to first install the xcode developer tools package:

```
xcode-select --install
```

### Testmate Extension
If you would like to run/manage this projects unit tests with the testmate test extension, add the following entry to your settings.json file:

```
{
  // other entries ...
  // add this:
  "testMate.cpp.test.advancedExecutables": [
    {
      "pattern": "${workspaceFolder}/test/bin/*",
      "runTask": {
        "before":[
            "build tests"
        ]
      }
    }
  ]
}
```
This provides a useful interactive display for running tests and viewing test results.

**Unfortunately it is not currently set up for use in windows.**
