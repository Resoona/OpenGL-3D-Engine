# OpenGL-3D-Engine
A 3D engine using OpenGL - In development

This is my first attempt at building a working engine. Expect many bad practices as I figure out how to display anything on the screen.

Overall goal for this project is to generate terrain(Grass/Trees/Water) and object model loading(Buildings). Additionally implement different lighting techniques to the world.

Soon, feel free to follow my progress on my website towards my application!

http://drewcornfield.com/projects.php

![alt text](https://i.imgur.com/kQWbr6B.png)

Compile/Linker instructions:

C++/General - Additional Include Directories:
-Requires GLFW, GLEW, and GLM 9.8.0

Linker/General - Additional Library Directories:
-Requires GLFW and GLEW 32 bit binaries

Linker/Input: glu32.lib, glew32.lib, opengl32.lib, glfw3.lib

These will be added at a later stage so its not required to link

Thanks for checking it out :)


Code is built using the combination of resources (And my own):

https://learnopengl.com/

http://www.opengl-tutorial.org/

https://github.com/TheCherno/Sparky

https://github.com/fegennari/3DWorld