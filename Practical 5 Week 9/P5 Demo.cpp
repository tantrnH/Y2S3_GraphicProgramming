#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#define WINDOW_TITLE "Practical 5"

float tx = 0, tz = 0, tSpeed = 1.0;		//tx,tz with tSpeed for modelview
bool isOrtho = true;					//is Ortho view?
float oNear = -10, oFar = 10;			//ortho near & far (z-axis)
float pNear = 1, pFar = 10;				//perpective near & far (z-axis)
float r1 = 3.0;							//sphere 1 radius
float ptx = 0, pty = 0, ptSpeed = 0.1;	//tx,ty with ptSpeed for projection
float pry = 0, prSpeed = 1.0;           //ry with prSpeed for projection

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg){
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == 'L') {
			pry += prSpeed;		// anticlockwise = positive
		}
		else if (wParam == 'R') {
			pry -= prSpeed;		// clockwise = negative
		}
		else if (wParam == VK_UP) {		//press 'UP' arrow key to move backward
			if (isOrtho) {
				if (tz > oNear + r1)			//ortho near boundary
					tz -= tSpeed;
			}
			else {
				if (tz > pNear - pFar)	//perspective far boundary
					tz -= tSpeed;
			}
		}
		else if (wParam == VK_DOWN) {	//press 'DOWN' arrow key to move forward
			if (isOrtho) {
				if (tz < oFar - r1)			//ortho far boundary  //adding  '- r1' in oFar letting the model showing consisting in the projection
					tz += tSpeed;
			}
			else {
				if (tz < pNear - r1)	//perspective near boundary
					tz += tSpeed;
			}
		}
		else if (wParam == VK_LEFT) {	//press 'LEFT' to move left the modelview
			tx -= tSpeed;
		}
		else if (wParam == VK_RIGHT) {	//press 'RIGHT' to move right the modelview
			tx += tSpeed;
		}
		else if (wParam == 'O') {		//press 'O' for ortho view
			isOrtho = true;
			tz = 0;
		}
		else if (wParam == 'P') {		//press 'P' for prespective view
			isOrtho = false;
			tz = pNear - r1;
		}
		else if (wParam == 'A') {	//press 'A' to move left the projection
			ptx -= ptSpeed;
		}
		else if (wParam == 'D') {	//press 'D' to move right the projection
			ptx += ptSpeed;
		}
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
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_LINE);
	gluSphere(sphere, r, 30, 30);
	gluDeleteQuadric(sphere);
}

void projection() {
	glMatrixMode(GL_PROJECTION);	//refer to the projection matrix
	glLoadIdentity();				//reset the projection matrix

	glTranslatef(ptx, pty, 0.0);	//tx, ty for the projection
	glRotatef(pry, 0.0, 1.0, 0.0);  //ry for projection

	if (isOrtho) {
		glOrtho(-10, 10, -10, 10, oNear, oFar);		//ortho view
	}
	else{
		glFrustum(-10, 10, -10, 10, pNear, pFar);	//prespective view
		//gluPerspective(45, 1.0, 1.0, 10.0);
	}
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	projection();					//projection

	glMatrixMode(GL_MODELVIEW);		//refer to the modelview matrix
	glLoadIdentity();				//reset the modelview transformation matrix				
	glTranslatef(tx, 0.0, tz);		//tx,tz for modelview
	
	drawSphere(r1);					//sphere 1
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
		900, 10, 300, 300,
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