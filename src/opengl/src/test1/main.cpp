#include <math.h>
#include <glad/glad.h>
#include <GL/glfw3.h>
#include <iostream>

const GLfloat Pi = 3.1415926536f;

// namespace gl_test_1
// {
// 	namespace t1
// 	{
// 		void rect()
// 		{
// 			glClearColor(0.5, 0.3, 1.0, 0.50);  
// 
// 			glClear(GL_COLOR_BUFFER_BIT);  
// 
// 			glColor3f(1.0, 0.3, 0.5);  
// 
// 			glRectf(-0.5, -0.5, 0.5, 0.8);
// 
// 			glFlush();
// 		}
// 
// 		void circle()
// 		{
// 			glClear(GL_COLOR_BUFFER_BIT);
// 			glBegin(GL_POLYGON);
// 
// 			const GLfloat R = 0.5f;
// 			const GLint N = 30;
// 			for (int i = 0; i < N; ++i)
// 			{
// 				glVertex2f(R * cos(2 * Pi / N * i), R * sin(2 * Pi / N * i));
// 			}
// 
// 			glEnd();
// 			glFlush();
// 		}
// 
// 		void FiveAngle()
// 		{
// 			glClear(GL_COLOR_BUFFER_BIT);
// 			glBegin(GL_LINE_LOOP);
// 
// 			GLfloat a = 1 / (2-2*cos(72*Pi/180));
// 			GLfloat bx = a * cos(18 * Pi/180);
// 			GLfloat by = a * sin(18 * Pi/180);
// 			GLfloat cy = -a * cos(18 * Pi/180);
// 			GLfloat
// 				PointA[2] = { 0, a },
// 				PointB[2] = { bx, by },
// 				PointC[2] = { 0.5, cy },
// 				PointD[2] = { -0.5, cy },
// 				PointE[2] = { -bx, by };
// 
// 			glClear(GL_COLOR_BUFFER_BIT);
// 			// 按照A->C->E->B->D->A的顺序，可以一笔将五角星画出
// 			glBegin(GL_LINE_LOOP);
// 			glVertex2fv(PointA);
// 			glVertex2fv(PointC);
// 			glVertex2fv(PointE);
// 			glVertex2fv(PointB);
// 			glVertex2fv(PointD);
// 			glEnd();
// 			glFlush();
// 
// 			glEnd();
// 		}
// 
// 		void sinx()
// 		{
// 			glClear(GL_COLOR_BUFFER_BIT);
// 			glBegin(GL_LINES);
// 			glVertex2f(-1.0f, 0.0f);
// 			glVertex2f(1.0f, 0.0f);         // 以上两个点可以画x轴
// 			glVertex2f(0.0f, -1.0f);
// 			glVertex2f(0.0f, 1.0f);         // 以上两个点可以画y轴
// 			glEnd();
// 			glBegin(GL_LINE_STRIP);
// 			const GLfloat factor = 0.1f;
// 			for(GLfloat x = -1.0f / factor; x < 1.0f/factor; x += 0.01f)
// 			{
// 				glVertex2f(x*factor, sin(x)*factor);
// 			}
// 			glEnd();
// 			glFlush();
// 		}
// 
// 		//#define GL_TEST_1_RECT
// 		//#define GL_TEST_1_CIRCLE
// 		//#define GL_TEST_1_FIVEANGLE
// #define GL_TEST_1_SINX
// 		void run()
// 		{
// #ifdef GL_TEST_1_RECT
// 			glutDisplayFunc(rect);
// #elif defined(GL_TEST_1_CIRCLE)
// 			glutDisplayFunc(circle);
// #elif defined(GL_TEST_1_FIVEANGLE)
// 			glutDisplayFunc(FiveAngle);
// #elif defined(GL_TEST_1_SINX)
// 			disp(sinx);
// #endif
// 		}
// 	}
// 	
// 	namespace t2
// 	{
// 		void test_glPointSize()
// 		{
// 			glClear(GL_COLOR_BUFFER_BIT);
// 			//指定点象素大小
// 			glPointSize(5.0f);
// 			glBegin(GL_POINTS);
// 			glVertex2f(0, 0);
// 			glVertex2f(0.5, 0.5);
// 			glEnd();
// 
// 			glFlush();
// 		}
// 
// 		void test_glLineWidth_glLineStipple()
// 		{
// 			glClear(GL_COLOR_BUFFER_BIT);
// 
// 			//直线可以指定宽度
// 			glLineWidth(5.0f);
// 			glBegin(GL_LINES);
// 			glVertex2f(0, 0);
// 			glVertex2f(0.5, 0.5);
// 			glEnd();
// 
// 			//画虚线
// 			glEnable(GL_LINE_STIPPLE);
// 			glLineStipple(2, 0x0f0f);
// 			glBegin(GL_LINES);
// 			glVertex2f(0, 0);
// 			glVertex2f(-0.5, 0.5);
// 			glDisable(GL_LINE_STIPPLE);
// 			glEnd();
// 
// 			glFlush();
// 		}
// 
// 		void test_glLineStipple()
// 		{
// 			glClear(GL_COLOR_BUFFER_BIT);
// 
// 			//画虚线
// 			glEnable(GL_LINE_STIPPLE);
// 			glLineWidth(5.0f);
// 			glLineStipple(2, 0x0f0f);
// 			glBegin(GL_LINES);
// 			glVertex2f(0, 0);
// 			glVertex2f(0.5, 0.5);
// 			glDisable(GL_LINE_STIPPLE);
// 
// 			glEnd();
// 
// 			glFlush();
// 		}
// 
// 		void test_glPolygonMode()
// 		{
// 			glClear(GL_COLOR_BUFFER_BIT);
// 
// 			glPolygonMode(GL_FRONT, GL_FILL);//设置正面为填充方式
// 			glPolygonMode(GL_BACK, GL_LINE); // 设置反面为边缘绘制方式
// 			
// 			glFrontFace(GL_CCW);	//设置CCW方向为“正面”，CCW即CounterClockWise，逆时针
// 			//glFrontFace(GL_CW);
// 
// 			glBegin(GL_POLYGON);
// 			glVertex2f(-0.5f, -0.5f);
// 			glVertex2f(0.0f, -0.5f);
// 			glVertex2f(0.0f, 0.0f);
// 			glVertex2f(-0.5f, 0.0f);
// 			glEnd();
// 
// 			glBegin(GL_POLYGON);
// 			glVertex2f(0.0f, 0.0f);
// 			glVertex2f(0.0f, 0.5f);
// 			glVertex2f(0.5f, 0.5f);
// 			glVertex2f(0.5f, 0.0f);
// 
// 			glEnd();
// 
// 			glFlush();
// 		}
// 
// 		static GLubyte Mask[128] =
// 		{
// 			0x00, 0x00, 0x00, 0x00,    //   这是最下面的一行
// 			0x00, 0x00, 0x00, 0x00,
// 			0x03, 0x80, 0x01, 0xC0,    //   麻
// 			0x06, 0xC0, 0x03, 0x60,    //   烦
// 			0x04, 0x60, 0x06, 0x20,    //   的
// 			0x04, 0x30, 0x0C, 0x20,    //   初
// 			0x04, 0x18, 0x18, 0x20,    //   始
// 			0x04, 0x0C, 0x30, 0x20,    //   化
// 			0x04, 0x06, 0x60, 0x20,    //   ，
// 			0x44, 0x03, 0xC0, 0x22,    //   不
// 			0x44, 0x01, 0x80, 0x22,    //   建
// 			0x44, 0x01, 0x80, 0x22,    //   议
// 			0x44, 0x01, 0x80, 0x22,    //   使
// 			0x44, 0x01, 0x80, 0x22,    //   用
// 			0x44, 0x01, 0x80, 0x22,
// 			0x44, 0x01, 0x80, 0x22,
// 			0x66, 0x01, 0x80, 0x66,
// 			0x33, 0x01, 0x80, 0xCC,
// 			0x19, 0x81, 0x81, 0x98,
// 			0x0C, 0xC1, 0x83, 0x30,
// 			0x07, 0xE1, 0x87, 0xE0,
// 			0x03, 0x3F, 0xFC, 0xC0,
// 			0x03, 0x31, 0x8C, 0xC0,
// 			0x03, 0x3F, 0xFC, 0xC0,
// 			0x06, 0x64, 0x26, 0x60,
// 			0x0C, 0xCC, 0x33, 0x30,
// 			0x18, 0xCC, 0x33, 0x18,
// 			0x10, 0xC4, 0x23, 0x08,
// 			0x10, 0x63, 0xC6, 0x08,
// 			0x10, 0x30, 0x0C, 0x08,
// 			0x10, 0x18, 0x18, 0x08,
// 			0x10, 0x00, 0x00, 0x08    // 这是最上面的一行
// 		};
// 
// 
// 		//#define GL_TEST_2_glPointSize
// 		//#define GL_TEST_2_glLineWidth_glLineStipple
// 		//#define GL_TEST_2_glLineStipple
// #define GL_TEST_2_glPolygonMode
// 		void run()
// 		{
// #ifdef GL_TEST_2_glPointSize
// 			glutDisplayFunc(test_glPointSize);
// #elif defined(GL_TEST_2_glLineWidth_glLineStipple)
// 			glutDisplayFunc(test_glLineWidth_glLineStipple);
// #elif defined(GL_TEST_2_glLineStipple)
// 			glutDisplayFunc(test_glLineStipple);
// #elif defined(GL_TEST_2_glPolygonMode)
// 			glutDisplayFunc(test_glPolygonMode);
// #endif
// 		}
// 	}
// 
// 	namespace t3
// 	{
// 		void test_glPointSize()
// 		{
// 			glClear(GL_COLOR_BUFFER_BIT);
// 			//指定点象素大小
// 			glPointSize(5.0f);
// 			glBegin(GL_POINTS);
// 			glVertex2f(0, 0);
// 			glVertex2f(0.5, 0.5);
// 			glEnd();
// 
// 			glFlush();
// 		}
// 
// 		void test_glLineWidth_glLineStipple()
// 		{
// 			glClear(GL_COLOR_BUFFER_BIT);
// 
// 			//直线可以指定宽度
// 			glLineWidth(5.0f);
// 			glBegin(GL_LINES);
// 			glVertex2f(0, 0);
// 			glVertex2f(0.5, 0.5);
// 			glEnd();
// 
// 			//画虚线
// 			glEnable(GL_LINE_STIPPLE);
// 			glLineStipple(2, 0x0f0f);
// 			glBegin(GL_LINES);
// 			glVertex2f(0, 0);
// 			glVertex2f(-0.5, 0.5);
// 			glDisable(GL_LINE_STIPPLE);
// 			glEnd();
// 
// 			glFlush();
// 		}
// 
// 		void test_glLineStipple()
// 		{
// 			glClear(GL_COLOR_BUFFER_BIT);
// 
// 			//画虚线
// 			glEnable(GL_LINE_STIPPLE);
// 			glLineWidth(5.0f);
// 			glLineStipple(2, 0x0f0f);
// 			glBegin(GL_LINES);
// 			glVertex2f(0, 0);
// 			glVertex2f(0.5, 0.5);
// 			glDisable(GL_LINE_STIPPLE);
// 
// 			glEnd();
// 
// 			glFlush();
// 		}
// 
// 		void test_glPolygonMode()
// 		{
// 			glClear(GL_COLOR_BUFFER_BIT);
// 
// 			glPolygonMode(GL_FRONT, GL_FILL);//设置正面为填充方式
// 			glPolygonMode(GL_BACK, GL_LINE); // 设置反面为边缘绘制方式
// 
// 			glFrontFace(GL_CCW);	//设置CCW方向为“正面”，CCW即CounterClockWise，逆时针
// 			//glFrontFace(GL_CW);
// 
// 			glBegin(GL_POLYGON);
// 			glVertex2f(-0.5f, -0.5f);
// 			glVertex2f(0.0f, -0.5f);
// 			glVertex2f(0.0f, 0.0f);
// 			glVertex2f(-0.5f, 0.0f);
// 			glEnd();
// 
// 			glBegin(GL_POLYGON);
// 			glVertex2f(0.0f, 0.0f);
// 			glVertex2f(0.0f, 0.5f);
// 			glVertex2f(0.5f, 0.5f);
// 			glVertex2f(0.5f, 0.0f);
// 
// 			glEnd();
// 
// 			glFlush();
// 		}
// 
// 		//#define GL_TEST_2_glPointSize
// 		//#define GL_TEST_2_glLineWidth_glLineStipple
// 		//#define GL_TEST_2_glLineStipple
// #define GL_TEST_2_glPolygonMode
// 		void run()
// 		{
// #ifdef GL_TEST_2_glPointSize
// 			glutDisplayFunc(test_glPointSize);
// #elif defined(GL_TEST_2_glLineWidth_glLineStipple)
// 			glutDisplayFunc(test_glLineWidth_glLineStipple);
// #elif defined(GL_TEST_2_glLineStipple)
// 			glutDisplayFunc(test_glLineStipple);
// #elif defined(GL_TEST_2_glPolygonMode)
// 			glutDisplayFunc(test_glPolygonMode);
// #endif
// 		}
// 	}
// 
// 	//#define TEST_t1
// 	//#define TEST_t2
// 	#define TEST_t3
// 	void run(int argc,char** argv)
// 	{
// 		glutInit(&argc, argv);
// 
// 		//设置显示方式
// 		glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
// 
// 		glutInitWindowPosition(100, 100);
// 
// 		glutInitWindowSize(600, 600);
// 
// 		glutCreateWindow (argv[0]);
// 
// #ifdef TEST_t1
// 		t1::run();
// #elif defined(TEST_t2)
// 		t2::run();
// #elif defined(TEST_t3)
// 		t3::run();
// #endif
// 		glutMainLoop();
// 	}
// }
// 
// namespace gl_test_2
// {
// 	void run(int argc, char *argv[])
// 	{
// 
// 	}
// }
// 
// namespace gl_test_3
// {
// 	void run(int argc, char *argv[])
// 	{
// 
// 	}
// }
// 
// 
// //改变大小时调用的函数
// void ChangeSize(GLsizei w,GLsizei h)
// {
// 	if (h==0) {
// 		h=1;
// 	}
// 	//设置视区尺寸
// 	glViewport(0, 0, w, h);
// 	//重置坐标系统，使用投影变换复位
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 
// 	if (w<=h) {
// 		glOrtho (0.0f,250.0f, 0.0f,250.0f*h/w, 1.0f, -1.0f);
// 	}else
// 	{
// 		glOrtho (0.0f,250.0f*w/h, 0.0f,250.0f, 1.0f, -1.0f);
// 	}
// 	glMatrixMode(GL_MODELVIEW);
// 	glLoadIdentity();
// }

// int main(int argc, char *argv[])
// {
// #if 1
// 	//gl_test_1::run(argc, argv);
// #endif
// 
// #if 0
// 	gl_test_2::run(argc, argv);
// #endif
// 
// 	return 0;
// }

#include <glad/glad.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}    

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}



