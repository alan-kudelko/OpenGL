This repository represents my first experience working with OpenGL. It includes my initial implementation of essential classes and utilities designed to support future projects involving OpenGL and real-time rendering. I am currently working on the implementation of basic classes that will serve as the foundation for building a larger OpenGL project, such as an Arkanoid-style game. 

My custom classes are located in the GLS folder and include:
1. GL_VertexData: Stores vertex data used by GL_Shapes;
2. GL_Shapes: A base class for GL_Triangle and GL_Polygon, designed to simplify and automate the construction of geometric primitives;
3. GL_Shader: Handles loading, compiling, linking, and debugging of GLSL shaders;
4. GL_Collider: Contains geometry used for collision detection and handles collision processing;
5. GL_Component: A base class for GL_Shapes, GL_Shader, GL_Collider, and future components, allowing them to be used within GL_GameObject;
6. GL_GameObject: Represents a single object in the game;
7. GL_SceneRenderer: Responsible for rendering GL_GameObject instances within the scene;
8. GL_CollisionManager: Manages collision detection logic and will be integrated into the GL_Game class;
9. GL_Script: Handles user-created scripts as separate .DLL files (planned for future implementation);
10. GL_SceneManager: Manages the current game scene;
11. GL_Game: Runs the main game loop and coordinates core systems like rendering, collision detection, and scene management.