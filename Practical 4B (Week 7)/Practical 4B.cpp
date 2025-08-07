
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>



#define WINDOW_TITLE "OpenGL Window"


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void drawSphere(double r) {
	GLUquadricObj* sphere = NULL;					//create quadric obj pointer
	sphere = gluNewQuadric();						//create the quadric obj in the memory
	gluQuadricDrawStyle(sphere, GLU_LINE);			//set the drawstyle to line
	gluSphere(sphere, r, 30, 30);					//draw sphere
	gluDeleteQuadric(sphere);						//delete teh quadric obj and free up memory
}

void drawDisk(double inr, double outr) {
	GLUquadricObj* disk = NULL;					//create quadric obj pointer
	disk = gluNewQuadric();						//create the quadric obj in the memory
	gluQuadricDrawStyle(disk, GLU_LINE);		//set the drawstyle to line
	gluDisk(disk, inr, outr, 30, 30);			//draw disk
	gluDeleteQuadric(disk);						//delete teh quadric obj and free up memory
}

void drawCylinder(double br, double tr, double h, int sl, int st) {
	GLUquadricObj* cylinder = NULL;				//create quadric obj pointer
	cylinder = gluNewQuadric();					//create the quadric obj in the memory
	gluQuadricDrawStyle(cylinder, GLU_LINE);	//set the drawstyle to line
	gluCylinder(cylinder, br, tr, h, sl, st);	//draw cylinder
	gluDeleteQuadric(cylinder);					//delete teh quadirc obj and free up memory
}

void drawCone(double tr, double h, int sl, int st) {
	GLUquadricObj* cone = NULL;				//create quadric obj pointer
	cone = gluNewQuadric();					//create the quadric obj in the memory
	gluQuadricDrawStyle(cone, GLU_LINE);	//set the drawstyle to line
	gluCylinder(cone, 0, tr, h, sl, st);	//draw cone
	gluDeleteQuadric(cone);					//delete teh quadirc obj and free up memory
}

void drawPyramid() {

}

void drawCube() {

}

void drawSphereWithoutGLU()
{
	const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;
	GLfloat radius = 0.5;				// We can adjust the size ourself
	int sliceNo = 30, stackNo = 30;

	for (sliceA = 0.0; sliceA < 1 * PI; sliceA += PI / sliceNo)			// change to 1 * PI, it will be half sphere
	{
		glBegin(GL_LINE_STRIP);
		for (stackA = 0.0; stackA < 1 * PI; stackA += PI / stackNo)		// change to 1 * PI, it will be half sphere
		{
			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);
			glVertex3f(x, y, z);
			x = radius * cos(stackA) * sin(sliceA + PI / stackNo);
			y = radius * sin(stackA) * sin(sliceA + PI / sliceNo);
			z = radius * cos(sliceA + PI / sliceNo);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void display()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(0.01, 1.0, 1.0, 1.0);							//rotate in all axis
	
	glColor3f(1.0, 0.0, 0.0);								//red disk
	drawSphere(0.19);
	drawDisk(0.05, 0.2);
	drawSphereWithoutGLU();

	glColor3f(0.0, 0.0, 1.0);
	drawCylinder(0.02, 0.2, 0.8, 10, 10);
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------