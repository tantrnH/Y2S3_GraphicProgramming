
#include <Windows.h>
#include <gl/GL.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 2 Week 3"

/* Translate  glTranslatef(tx,ty,tz);         tx: + = right, - = left ;ty: + = up, - = down; tz: + == x and y += 1, - == x and y -=1; */
// MT = [ 1 0 0 Tx]
//      [ 0 2 0 Ty]
//      [ 0 0 1 Tz]
//      [ 0 0 0 1 ]

/* Rotation   glRotationf(angle,rx,ry,rz);    */
// M(Rz) = [ cos0 -sin0  0  0 ]
//         [ sin0  cos0  0  0 ]
//         [  0     0    1  0 ]
//         [  0     0    0  1 ]

// M(Rx) = [  1    0     0    0 ]
//         [  0   cos0 -sin0  0 ]
//         [  0   sin0  cos0  0 ]
//         [  0    0     0    1 ]

// M(Rz) = [ cos0  0  sin0 0 ]
//         [  0    1   0   0 ]
//         [-sin0  0  cos0 0 ]
//         [  0    0   0   1 ]

/* Scaling    glScalef(sx,sy,sz); */
// M(S) =  [ Sx 0  0  0 ]
//         [ 0  Sy 0  0 ]
//         [ 0  0  Sz 0 ]
//         [ 0  0  0  1 ]

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

void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();					//reset the transformation, let the drawed shape move and stop at the location we set at (tx)
	glTranslatef(0.5, -0.5, 0.0);		// tx(0.5) ty(-0.5), tx means the move speed of the movement 
	glBegin(GL_TRIANGLES);
		glVertex2f(-0.5, 0.0);
		glVertex2f(0.0, 0.5);
		glVertex2f(0.5, 0.0);
	glEnd();
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