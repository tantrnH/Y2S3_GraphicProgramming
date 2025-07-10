
// finish all flags of Practical 1 include the extra exercise
#include <Windows.h>	//window class
#include <gl/GL.h>		//openGL class
#include <math.h>		//math class

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical Exercoise 1 Week 3"

int qNo = 5;			//qno
float x = 0, y = 0;		//origin of circle, location
float radius = 1;		//radius
float angle = 0;		//angle
float x2 = 0, y2 = 0;	//point on circle
float PI = 3.1415926;	//PI
int noOfTri = 30;		//no of triangles

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

void pahangFlag() {
	glClearColor(0.0, 0.0, 0.0, 0.0);  // clear the background
	glClear(GL_COLOR_BUFFER_BIT);      // clear the color buffer

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);      // WHITE
	glVertex2f(-0.5, 0.0);     // v1
	glVertex2f(-0.5, 0.5);     // v2
	glVertex2f(0.5, 0.5);      // v3
	glVertex2f(0.5, 0.0);      // v4
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);   // BLACK 
	glVertex2f(-0.5, -0.5);     // v1
	glVertex2f(-0.5, 0.0);      // v2
	glVertex2f(0.5, 0.0);       // v3
	glVertex2f(0.5, -0.5);      // v4
	glEnd();

	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 1.0);   // BLUE
	glVertex2f(-0.5, -0.5);     // v1
	glVertex2f(-0.5, 0.5);      // v2
	glVertex2f(0.5, 0.5);       // v3
	glVertex2f(0.5, -0.5);      // v4
	glEnd();
}

void n9Flag() {
	glClearColor(0.0, 0.0, 0.0, 0.0);  // clear the background
	glClear(GL_COLOR_BUFFER_BIT);      // clear the color buffer

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.5, 0.0);
	glVertex2f(0.5, -0.5);
	glEnd;

	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.5, -0.5);
	glVertex2f(0.0, -0.5);
	glEnd;

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.5, 0.0);
	glVertex2f(1.0, 0.0);
	glVertex2f(1.0, -0.5);
	glVertex2f(0.5, -0.5);
	glEnd;

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.5, -0.5);
	glVertex2f(1.0, -0.5);
	glVertex2f(1.0, -1.0);
	glVertex2f(0.5, -1.0);
	glEnd;
}


void japanFlag()
{
	// Learn how to draw circle
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLE_FAN);	// can use "GL_LINE_LOOP" and commend glVertex2f(x, y) if u just want the outline of the circle
	glColor3f(1.0, 0.0, 0.0);	//RED
	glVertex2f(x, y);		// origin of circle
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {		// PI = half of the circle, 2*PI = whole circle; Or u can just set angle as PI, u can get half circle also; the ori code means draw start from 0 to PI and PI to PI, it will generate a circle
		x2 = x + radius * cos(angle);
		y2 = y + radius * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.8, -0.5);
	glVertex2f(-0.8, 0.5);
	glVertex2f(0.8, 0.5);
	glVertex2f(0.8, -0.5);
	glEnd();
}

void extraExercise() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// emoji face
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0, 1.0, 0.0);	
	glVertex2f(x, y);		// origin of circle
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {		 
		x2 = x + radius * cos(angle);
		y2 = y + radius * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	// emoji left eye
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.5, 0.3);
	glVertex2f(-0.2, -0.3);
	glVertex2f(0.2, -0.3);
	glVertex2f(0.2, 0.3);
	glEnd();
}

void display()
{
	switch (qNo) {
	case 1:
		japanFlag();
		break;

	case 2:
		n9Flag();
		break;

	case 3:
		extraExercise();
		break;

	default:
		extraExercise();
		break;

	}
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