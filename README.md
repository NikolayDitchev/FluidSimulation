
C++ Fluid Simulation using the SFML framework. The CmakeLists.txt file installs SFML automatically in the project, you don't need to install SFML to test it.

Controls:

    Left mouse button: adding fluid
    Right mouse button: adding a block of solid

To test in a docker container, a X-Server is needed. For Windows you can install X-Server from sourceforge.net - https://sourceforge.net/projects/vcxsrv/.
After you have started your X-Server you can build the docker image:

  ```
  docker build -t <image-name> /path/to/the/project
  ```

When you run the image you have to provide an environment variable DISPLAY, that indicates the port your X-server is listening on. Example:

```
docker run --env DISPLAY=host.docker.internal:0.0 --rm -it <image-name>
```

To test the project without docker GCC 13.1.0 must be installed in case you are running Windows. On Linux or MacOS any GCC and CMake versions are fine.
Commands for building the binary:

Linux or MacOS:

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Windows:

```
cmake -S . -B build
cmake --build build --config Release
```
The binary will be located in <your-project-directory>/build/bin/Release.
