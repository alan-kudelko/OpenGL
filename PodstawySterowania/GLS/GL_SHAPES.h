#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <string>
#include <iostream>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GL_GPUResourceTracker.h"

extern GLS::GL_GPUResourceTracker GL_GPUresourceTracker;

namespace GLS{
	struct GL_VertexData{
		glm::vec3 xyz;
		glm::vec4 rgba;
		glm::vec2 uv;
	};
	
    class GL_SHAPE{
	protected:
        std::string _name;
		GLenum _memoryLocation;
        GLuint _VAO;
        GLuint _VBO;
		GLuint _shaderProgram;
		GLfloat*_vertices;
		GLuint _vertN;
		GLuint* _texture;
    public:
        GL_SHAPE(std::string name="brak",GLuint shaderProgram=0,GLenum memoryLocation=GL_STATIC_DRAW);
        virtual ~GL_SHAPE();

        virtual void GLdrawShape(GLFWwindow*window)=0;
		void GLtransform(glm::vec3 transformVector);
		void GLrotate(glm::vec3 rotationVector);
		void GLscale(glm::vec3 scaleVector);
		std::string GLgetName()const;
		GLenum GLgetMemoryLocation()const;
		GLuint GLgetVAO()const;
		GLuint GLgetVBO()const;
		GLuint GLgetShader()const;
        GLfloat*GLgetVertices()const;
    };
	class GL_TRIANGLE:public GL_SHAPE{
		public:
		GL_TRIANGLE(GLfloat*vertices,std::string name,GLuint shaderProgram,GLenum memoryLocation=GL_DYNAMIC_DRAW);
		~GL_TRIANGLE();
		void GLdrawShape(GLFWwindow*window)override;
	};
	class GL_RECTANGLE:public GL_SHAPE{
		GLuint _EBO;
		GLuint _indices[6]{1,2,3,0,1,3};
		//Dla reszty poligonow mozna zrobic iteracyjny generator
		//Budujemy trojki 123
		//                130
		//                141
		//                152 no cos takiego, jest na kartce
		public:
        GL_RECTANGLE(GLfloat*vertices,std::string name,GLuint shaderProgram,GLenum memoryLocation=GL_STATIC_DRAW);
        ~GL_RECTANGLE();

		void GLdrawShape(GLFWwindow*window)override;
	};
}
/*
	Utworzyć nowy interfejs klasy, który będzie później fragmentem całości
	Obiekt typu bazowego GL_SHAPE powinien:
	1. umożliwić interfejs zmiany wierzchołków w trakcie działania programu
	2. Udostępniać domyślny konstruktor, generujący w sposób automatyczny wierzchołki najlepiej jakby znajdowały się np. na okręgu o danym domyślnym promieniu tj. pierwiastki równań zespolonych wyższych stopni
	3. Rozważyć funkcję zaprzyjaźnioną GLS::GLTransform korzystającą z biblioteki glm
	6. Do punktu 4, lepiej stworzyć strukturę, która będzie przekazywana i zwracana do/z obiektu
	7. Pola w strukturze powinny zawierać współrzędne, normalne, pozycję tekstury to na razie wystarczy, w przyszłości to może być również obiektowe w zależności ile atrybutów będzie potrzebnych
	8. Biblioteka STB.h do tekstur
	
	Aktualny konstruktor GL_SHAPE(std::string name="brak",GLuint shaderProgram=0,GLenum memoryLocation=GL_STATIC_DRAW);

	GL_SHAPE(GLuint shaderProgram=0,GLenum memoryLocation=GL_STATIC_DRAW);
	//Shape może przechowywać te wierzchołki ale nie wiadomo w jaki sposób mają zostać narysowane
	//Tym zajmie się ovveride'owa metoda klas pochodnych
	
	GL_TRIANGLE(GL_VertexData*vertexData,GLuint shaderProgram,GLenum memoryLocation=GL_STATIC_DRAW);
	GL_TRIANGLE(GLuint shaderProgram,GLenum memoryLocation=GL_STATIC_DRAW);
	
	
Klasa GLS::GL_Shape{
protected:
każdy obiekt, który będzie tutaj dziediczył będzie potrzebować na pewno wierzchołków, na które składają się współrzędne, kolory i na razie tekstury.
Obiekt klasy powinien przechowywać współrzędne środka w postaci wektora, ponieważ będą one nadzorowane przez CPU
środek obiektu powinien się ustalać na geometryczny środek bryły, jest on potrzebny jedynie do zmiany położenia bryły po transformacjach
informacje o użytym shaderze
informacje o użytych rejestrach VBO,VAO oraz EBO
informacje o liczbie wierzchołków
informacja o trybie rysowania jako GLenum



public:
Konstruktor domyślny generujący kształty foremne oparte na jakimś okręgu

interfejs do pobierania oraz ustawiania informacji o wierzchołkach
interfejs do pobierania oraz ustawiania współrzędnych środka bryły
interfejs do pobierania oraz ustawiania wykorzystanego shadera
interfejs do pobierania aktualnie wykorzystanego VAO, VBO oraz EBO
interfejs do pobierania oraz ustawiania wykorzystywanej tekstury
interfejs do zmiany i pobierania trybu rysowania na podstawie typu wyliczeniowego

}

interfejs funkcji zaprzyjaźnionej z klasą GLS_GL_Shape służącej do przekształcania obiektu czyli translacja,rotacja,skalowanie
funkcja powinna móc nadpisywać współrzędne środka bryły

shader później


hierarchia dziedziczenia

            NLine?
               |
Circle------Shape ----Triangle
	          |      
	   Polygon(to już generuje kwadraty prostokąty i domyślnie inne figury foremne)
              

*/