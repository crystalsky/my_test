#include "GL/glew.h"
#include "GL/freeglut.h"
#include "LoadShaders.h"
#include <stdlib.h>
#define BUFFER_OFFSET(x)  ((const void*) (x))
enum  VAO_IDs
{
	Triangles, 
	NumVAOs = 100
};

enum Buffer_IDs
{
	ArrayBuffer,
	NumBuffers
};

enum Attrib_IDs
{
	vPosition = 0
};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

void init()
{
	//分配顶点数组对象
	glGenVertexArrays(NumVAOs, VAOs);
	
	//绑定顶点数组对象
	glBindVertexArray(VAOs[Triangles]);

	GLfloat Vertices[NumVertices][2] = 
	{
		{ -0.9, -0.9},
		{ -0.85, -0.9},
		{ -0.9, 0.85},
		{ 0.9, -0.85},
		{ 0.9, 0.9},
		{ -0.85, 0.9}
	};

	//分配顶点缓存对象
	glGenBuffers(NumBuffers, Buffers);

	//绑定缓存对象(指定当前激活对象)
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);

	//将数据载入缓存对象
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "triangles.vert"},
		{GL_FRAGMENT_SHADER, "triangles.frag"},
		{GL_NONE, NULL}
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	//设置index位置的着色器的数据
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	//设置是否启用与index索引相关联的顶点数组
	glEnableVertexAttribArray(vPosition);
}

void display()
{
	//清除指定的缓存数据并征调为当前的清除值
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAOs[Triangles]);

	//使用当前绑定的顶点数组元素来建立一系列的几何图元
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	//强制之前的命令立即执行
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("test2");

	if (glewInit())
	{
		exit(EXIT_FAILURE);
	}

	init();

	glutDisplayFunc(display);

	glutMainLoop();
	
	return 0;
}