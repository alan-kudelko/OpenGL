This repository represents my first experience working with OpenGL. It includes my initial implementation of essential classes and utilities designed to support future projects involving OpenGL and real-time rendering. I am currently working on the implementation of basic classes that will serve as the foundation for building a larger OpenGL project, such as an Arkanoid-style game. 

My custom classes are located in the GLS folder and include:
1. GL_VertexData: stores vertex data used by GL_Shapes;
2. GL_Shapes: a base class for GL_Triangle and GL_Polygon, designed to simplify and automate the construction of geometric primitives;
3. GL_Shader: handles loading, compiling, linking, and debugging of GLSL shaders;
4. GL_Colider: contains geometry used for collision detection and handles collision processing;
5. GL_Component: a base class for GL_Shapes, GL_Shader, GL_Colider and future components, enabling them to be used within the GL_GameObject class;
6. GL_GameObject: represents a single object in the game;
7. GL_SceneRenderer: responsible for rendering GL_GameObject instances within the scene;
8. GL_CollisionManager: handles collision detection logic; will be integrated as a component of the GL_Game class.