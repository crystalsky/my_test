#include <math.h>
#include <iostream>
#include <GLTools.h>
#include <gl/glut.h>

const GLfloat Pi = 3.1415926536f;

GLBatch triangleBathch;
GLShaderManager shaderManager;

void changeSize(int w, int h)
{
	glViewport(0, 0, w, h);
}

void setupRC()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	shaderManager.InitializeStockShaders();

	GLfloat vVerts[] = {
		-0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	triangleBathch.Begin(GL_TRIANGLES, 3);
	triangleBathch.CopyVertexData3f(vVerts);
	triangleBathch.End();
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};

	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
	triangleBathch.Draw();

	glutSwapBuffers();
}


int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Trangle");
	glutReshapeFunc(changeSize);

	glutDisplayFunc(RenderScene);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "GLEW Error:" << glewGetErrorString(err);
		return 1;
	}

	setupRC();

	glutMainLoop();

	return 0;
}



