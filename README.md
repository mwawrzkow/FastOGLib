# WIP: FastOGLib - Fast OpenGL Library

Fast and scalable library, able to create OpenGL progams on osx/linux/windows machines. 

# Instalation of Library
Actually does not provide plug in solution. Saying that so it's needed to download all source codes of Lib and dependent libs. 
```bash 
git stash
git pull
git submodule sync && git submodule update --init
```
## Linux/OSX
After checking out the desired version of library building is straight forward: 
```bash 
mkdir build
cd build 
cmake .. 
make
```
## Windows 
Unfortunetly on Windows the GNU compiler with make is required (MVC option is no tested - Feel free to test i will try to help my best). In order to build the app it's needed to select correct compiler: 
```powershell
mkdir build 
git stash
git pull
git submodule sync && git submodule update --init
cd build 
cmake .. -G "MinGW Makefiles" 
mingw32-make.exe -j 10 -l 10
```

## Developing the application
Actually in order of developement on this library the [main.cpp](Engine/Core/core/main.cpp) file has to be modified. In future months I'll be adding more functionality, which can me monitored in issues, and after some time, I'll provide  CMake style libraries. 

# Further information
Further information can be found in the .readme.md/README.md file. [Futher information](.readme.md/README.md)

# Contributors 
@mwawrzkow - Marcin Wawrzków - owner 
