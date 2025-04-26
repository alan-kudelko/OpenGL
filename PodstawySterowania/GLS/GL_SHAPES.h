#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <new>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GL_GPUResourceTracker.h"

extern GLS::GL_GPUResourceTracker GL_GPUresourceTracker;

namespace GLS{
	class GL_VertexData{
		glm::vec3 _xyz;
		glm::vec4 _rgba;
		glm::vec2 _uv;
	public:
		GL_VertexData(GLfloat*vertex);
		GL_VertexData(glm::vec3 xyz={},glm::vec4 rgba={},glm::vec2 uv={});
		void GLgetVertexData(GLfloat*vetexData)const;
		glm::vec3 GLgetXYZ()const;
		glm::vec4 GLgetRGBA()const;
		glm::vec2 GLgetUV()const;
		GLuint GLgetVertexSize()const;

		void GLsetVertexData(glm::vec3 xyz={},glm::vec4 rgba={},glm::vec2 uv={});
		void GLsetVertexData(GLfloat*vertexData);
		void GLsetXYZ(glm::vec3 xyz);
		void GLsetRGBA(glm::vec4 rgba);
		void GLsetUV(glm::vec2 uv);

		GL_VertexData&operator=(const GLS::GL_VertexData&vertexData);
		GL_VertexData&operator+(const GLS::GL_VertexData&vertexData);
		GL_VertexData&operator-(const GLS::GL_VertexData&vertexData);
		
		enum{GL_VERTEX_SIZE=9}; //Total number of attributes 3+4+2
	};

    class GL_SHAPE{
	protected:
		GLenum _memoryLocation;
        GLuint _VAO;
        GLuint _VBO;
		GLuint _shaderProgram;
		GL_VertexData*_vertices;
		GLuint _vertN;
    public:
        GL_SHAPE(GLuint shaderProgram=0,GLenum memoryLocation=GL_STATIC_DRAW);
        virtual ~GL_SHAPE();

        virtual void GLdrawShape(GLFWwindow*window)=0;
		void GLtransform(glm::vec3 transformVector);
		void GLrotate(glm::vec3 rotationVector);
		void GLscale(glm::vec3 scaleVector);
		GLenum GLgetMemoryLocation()const;
		GLuint GLgetVAO()const;
		GLuint GLgetVBO()const;
		GLuint GLgetShader()const;
        GLS::GL_VertexData GLgetVertices()const;
    };
	class GL_TRIANGLE:public GL_SHAPE{
		public:
		GL_TRIANGLE(GL_VertexData*vertices,GLuint shaderProgram,GLenum memoryLocation=GL_DYNAMIC_DRAW);
		GL_TRIANGLE(GLuint shaderProgram,GLenum memoryLocation=GL_STATIC_DRAW);
		~GL_TRIANGLE();
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
