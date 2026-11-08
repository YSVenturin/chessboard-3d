# Chessboard3D

## Environment

- Windows 64-bit
- Code::Blocks with MinGW 64-bit
- GLFW 3.4
- GLEW 2.1.0
- GLM 1.0.3

The dependencies are installed outside the repository:

```text
C:\glfw-3.4.bin.WIN64
C:\glfw-3.4
C:\glew-2.1.0
C:\glm
```

## Code::Blocks configuration

Open `Chessboard3D.cbp` and check **Project > Build options** for Debug and Release. Adjust the paths to match your computer.

### Compiler search directories

```text
include
C:\glfw-3.4.bin.WIN64\include
C:\glfw-3.4\deps
C:\glew-2.1.0\include
C:\glm
```

### Linker settings

```text
C:\glfw-3.4.bin.WIN64\lib-mingw-w64\libglfw3.a
C:\glfw-3.4.bin.WIN64\lib-mingw-w64\libglfw3dll.a
C:\Program Files\CodeBlocks\MinGW\x86_64-w64-mingw32\lib\libgdi32.a
C:\Program Files\CodeBlocks\MinGW\x86_64-w64-mingw32\lib\libopengl32.a
C:\glew-2.1.0\lib\Release\x64\glew32.lib
C:\glew-2.1.0\lib\Release\x64\glew32s.lib
```

## Build and run

1. Install the dependencies and configure the paths above.
2. Open `Chessboard3D.cbp` in Code::Blocks.
3. Build and run the project.

## Controls

- `W`, `A`, `S`, `D`: move the camera.
- Arrow keys: rotate the camera view.
- `Q` / `Z`: move the camera up / down.
- Left mouse button: select and move a piece.
- Right mouse button: clear the current selection.
- `R`: restore all chess pieces to their initial positions.