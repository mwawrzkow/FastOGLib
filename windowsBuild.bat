mkdir build 
git stash
git pull
git submodule sync && git submodule update --init
cd build 
cmake .. -G "MinGW Makefiles" 
mingw32-make.exe -j 10 -l 10
 cd .\Engine\Core\
  .\main.exe
    cd ../..
