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
	//���䶥���������
	glGenVertexArrays(NumVAOs, VAOs);
	
	//�󶨶����������
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

	//���䶥�㻺�����
	glGenBuffers(NumBuffers, Buffers);

	//�󶨻������(ָ����ǰ�������)
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);

	//���������뻺�����
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "triangles.vert"},
		{GL_FRAGMENT_SHADER, "triangles.frag"},
		{GL_NONE, NULL}
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	//����indexλ�õ���ɫ��������
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	//�����Ƿ�������index����������Ķ�������
	glEnableVertexAttribArray(vPosition);
}

void display()
{
	//���ָ���Ļ������ݲ�����Ϊ��ǰ�����ֵ
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAOs[Triangles]);

	//ʹ�õ�ǰ�󶨵Ķ�������Ԫ��������һϵ�еļ���ͼԪ
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	//ǿ��֮ǰ����������ִ��
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