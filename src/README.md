# Modules

Modules isolate kernel functionality into their own
implementation. As of now, usable modules are:
- [Logging](./log)
- [Memory](./mem)

## Module Layout

Modules, implement a file `export.h` where they define
symbols meant to be exported to the whole kernel, you can
access these by includeing the respective header, and
calling the require function, e.g.
```
#include <log.h>
require_log();
```
for the logging module.

## Module Implementation

The implementation of the module goes within a C source file
of the same name, with all local declarations going inside a
`proto.h` file.

Additionally, module documentation goes in its own `.md` file.

A module looks like this in the file tree:
```
* <module name>
|
+-- export.h
+-- proto.h
+-- <module name>.c
+-- README.md
```

To make the module accessible within the rest of the kernel, we
simply create a basic header in `./include` that includes our
`export` file.
