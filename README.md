Basic SDL2 app, demonstrating rendering an animated, axis-aligned box.

# Dependencies

MACOSX - using homebrew to install SDL2 dependencies.

```
brew install sdl2
brew install sdl2_image
brew install sdl2_gfx
```

# Build

Make a build directory:

```
mkdir build
cd build
cmake ..
```

While standing in the build directory, you can build your application with:

```
cmake --build .
```

While standing in the build directory, you can run your application with:

```
./MyApplication     
```

# Configure Project

Modify CMakeLists.txt to set variable names for your project
- ProjectName
    - Set this to the name of your application
- ProjectSources
    - Add any more 
- MyApplication.h/.cpp
    - Rename to the name of your project & modify as required
- Main.cpp
    - Modify name of 'MyApplication'
