# libKitsunemimiIni

![Gitlab pipeline status](https://img.shields.io/gitlab/pipeline/kitsudaiki/libKitsunemimiIni?label=build%20and%20test&style=flat-square)
![GitHub tag (latest SemVer)](https://img.shields.io/github/v/tag/kitsudaiki/libKitsunemimiIni?label=version&style=flat-square)
![GitHub](https://img.shields.io/github/license/kitsudaiki/libKitsunemimiIni?style=flat-square)
![C++Version](https://img.shields.io/badge/c%2B%2B-14-blue?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux--x64-lightgrey?style=flat-square)

## Description

This library provides the functionality to parse and handle the content of ini-files. It only converts string, but doesn't read files from the storage.


## Build

### Requirements

name | repository | version | task
--- | --- | --- | ---
g++ | g++ | >= 6.0 | Compiler for the C++ code.
make | make | >= 4.0 | process the make-file, which is created by qmake to build the programm with g++
qmake | qt5-qmake | >= 5.0 | This package provides the tool qmake, which is similar to cmake and create the make-file for compilation.
FLEX | flex | >= 2.6 | Build the lexer-code for all used parser.
GNU Bison | bison | 3.x | Build the parser-code together with the lexer-code.

Installation on Ubuntu/Debian:

```bash
sudo apt-get install g++ make qt5-qmake flex bison
```

IMPORTANT: All my projects are only tested on Linux. 

### Kitsunemimi-repositories

Repository-Name | Version-Tag | Download-Path
--- | --- | ---
libKitsunemimiCommon | v0.18.0 |  https://github.com/kitsudaiki/libKitsunemimiCommon.git

HINT: These Kitsunemimi-Libraries will be downloaded and build automatically with the build-script below.

### build library

In all of my repositories you will find a `build.sh`. You only have to run this script. It doesn't required sudo, because you have to install required tool via apt, for example, by yourself. But if other projects from me are required, it download them from github and build them in the correct version too. This script is also use by the ci-pipeline, so its tested with every commit.


Run the following commands:

```
git clone https://github.com/kitsudaiki/libKitsunemimiIni.git
cd libKitsunemimiIni
./build.sh
cd ../result
```

It create automatic a `build` and `result` directory in the directory, where you have cloned the project. At first it build all into the `build`-directory and after all build-steps are finished, it copy the include directory from the cloned repository and the build library into the `result`-directory. So you have all in one single place.

Tested on Debian and Ubuntu. If you use Centos, Arch, etc and the build-script fails on your machine, then please write me a mail and I will try to fix the script.


## Usage

**Header-file:** `libKitsunemimiIni/ini_item.h`

The `IniItem`-class is the handler for the ini-file-content. The functions in the header should be really self-explaned, if something is unclear, see the following example or the comments in the cpp-file.

```cpp
#include <libKitsunemimiIni/ini_item.h>

// short test-string for demonstration. 
const std::string testString(
                "[DEFAULT]\n"
                "key = asdf.asdf\n"
                "id = 550e8400-e29b-11d4-a716-446655440000\n"
                "x = 2\n"
                "\n"
                "[xyz]\n"
                "poi_poi = 1.300000\n"
                "\n");

IniItem object;

// parse the test-string
std::string errorMessage = "";
bool result = object.parse(testString, errorMessage);
// if result.first is true, then paring was successful

DataItem* value = object.get("DEFAULT", "x")
// if value is a nullptr, then the group and/or item doesn't exist
// the DataItem-class comes from my library libKitsunemimiCommon


// get an item of the ini-file-content
int getValue = value->getInt();
// getValue now contains 2

// it could also be converted into a stirng with the toString-method
std::string getValue = object.get("DEFAULT", "x")->toString();


// set or overwrite a value
object.set("group", "item", 42, true)
// arguments: group-name, item-name, value (string, int or float), force-flag
// if the group or item doesn't exist, it will be created
// force-flag must be true, to overwrite an existing item


// remove item or group
object.removeEntry("group", "item");
object.removeGroup("group");


// convert back into an ini-file-string
std::string output = object.toString();
// output-variable would contain the same like the inital parsed testString
// but with some additional double quotes at the strin-values and maybe another 
// order of the groups and keys inside the groups

```


## Contributing

Please give me as many inputs as possible: Bugs, bad code style, bad documentation and so on.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
