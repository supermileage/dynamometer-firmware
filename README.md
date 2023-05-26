# dynamometer-firmware

### Cloning the repo

This repository uses submodules, so to clone you must enter the command:

```
git clone --recurse-submodules <ENTER HTML OR SSH ADDRESS HERE>
```

If you have already cloned the repo, then you can navigate to your local copy of the repo and enter

```
git submodule init
git submodule update
```
### Windows Users
Before opening the repo in vscode with the platformIO extension, make sure to run the git command:
```
git config --system core.longpaths true
```
If you have attempted to open the project with platformIO before running the above command, you may need to delete your platformIO cache, which can be found here:
```
C:\Users\myuser\.platformio\.cache
```

### Unit Tests
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
```
This repo already includes the "build tests" task.
