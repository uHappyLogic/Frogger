### FAQ

* What IDE can I use to build this project

> Project was comfigured to be built in MS Visual Studio 17

* What are the targets, and platforms for which this project can be compiled?

> x64/x86 Windows

* Can I use the `comp` script to compile

> Although, the script was modified to reflect differences between template, and current project structure, it was not tested.

### Potential Errors:

* Std libs cannot be found

> PPM on solution; Properties; Configuration Properties; General; Windows SDK Version; choose the one available

* SDL2.ddl was not found

> Change project target from x64 to x86