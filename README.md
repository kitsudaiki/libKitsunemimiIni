# libKitsuneIni

## Description

This library provides the functionality to parse and handle the content of ini-files. It only converts string, but doesn't read files from the storage.

### About my kitsune libraries

My first libraries hab really common names like libCommon and so on, but I thought this could be hard to find my code between other libraries, when my projects will become bigger. So I decided to make a common name over all my libraries, similar to the boost-libraries, for a better handling. I decided to use `Kitsune` as name for my projects, because Kitsunemimi are moe. ;)

### About my repositories in general

At the moment there are over 10 Kitsune-libraries an multiple tools in my private repos. I plan to make all open-source, but I have much to learn about open-source-projects. Most of all I have to improve my ticket-handling. So please help me to improve my workflow.

All my projects are mirrored to gitlab, where I have still my gitlab-ci runner. 

I don't really like it to write much comments into header-files. More exactly I absolutly hate it, when I have to search the provided functions of a header between a massive amount of comments. Header-files are for me primary to have an overview, of all provided functions, which I have see as fast as possible. Comments of functions, parameters and return-values in my code are only written into the source-file. So when something is unclear for a specific method, than look into the source-file. If the comment there are not helpful for you, then please write me a mail or an issue to fix this. 

## Build

I write my projects with the Qt-creator, but without Qt itself. 

### Requirements

#### Official repositories

paket | version
--- | ---
g++ | 6.3.0
qt5-qmake | 5.7.1
bison | 3.0.4
flex | 2.6.1 

This are the version I have installed under Debian Stable via apt. Some older or newer version should work as well. I write my projects with the Qt-creator, but without Qt itself. Thats why qmake is required to build my projects.

IMPORTANT: All my projects are only tested on Linux. 

#### Kitsune-repositories

Repository-Name | Version-Tag | Download-Path
--- | --- | ---
libKitsuneCommon | 0.5.1 |  https://github.com/tobiasanker/libKitsuneCommon.git


### build library

In all of my repositories you will find a `build.sh`. You only have to run this script. It doesn't required sudo, because you have to install required tool via apt, for example, by yourself. But if other projects from me are required, it download them from github and build them in the correct version too. This script is also use by the ci-pipeline, so its tested with every commit.

Before running the build-script:

```bash
.
└── libKitsuneIni
    ├── build.sh
    └── ...
```

After running the build-script:

```bash
.
├── build
│   ├── libKitsuneCommon
│   │   └── ...
│   └── libKitsuneIni
│       └── ...
│
├── libKitsuneCommon
│   └── ...
├── libKitsuneIni
│   ├── build.sh
│   └── ...
│
└── result
    ├── include
    │   ├── libKitsuneCommon
    │   │   └── ...
    │   └── libKitsuneIni
    │       └── ...
    │
    ├── libKitsuneCommon.so -> libKitsuneCommon.so.0.5.1
    ├── libKitsuneCommon.so.0 -> libKitsuneCommon.so.0.5.1
    ├── libKitsuneCommon.so.0.5 -> libKitsuneCommon.so.0.5.1
    ├── libKitsuneCommon.so.0.5.1
    │
    ├── libKitsuneIni.so -> libKitsuneIni.so.0.2.0
    ├── libKitsuneIni.so.0 -> libKitsuneIni.so.0.2.0
    ├── libKitsuneIni.so.0.2 -> libKitsuneIni.so.0.2.0
    └── libKitsuneIni.so.0.2.0
```

It create automatic a `build` and `result` directory in the directory, where you have cloned the project. At first it build all into the `build`-directory and after all build-steps are finished, it copy the include directory from the cloned repository and the build library into the `result`-directory. So you have all in one single place.

Tested on Debian and Ubuntu. If you use Centos, Arch, etc and the build-script fails on your machine, then please write me a mail and I will try to fix the script.


## Usage

**Header-file:** `ini_item.h`

The `IniItem`-class is the handler for the ini-file-content. The functions in the header should be really self-explaned, if something is unclear, see the following example or the comments in the cpp-file.

```cpp
#include <ini_item.h>

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
std::pair<bool, std::string> result = object.parse(testString);
// if result.first is true, then paring was successful

DataItem* value = object.get("DEFAULT", "x")
// if value is a nullptr, then the group and/or item doesn't exist
// the DataItem-class comes from my library libKitsuneCommon


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
