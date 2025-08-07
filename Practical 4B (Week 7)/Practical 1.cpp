
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

int qNo = 1;			// question no
float x = 0, y = 0;		//origin of circle
float eX = -0.5, eY = 0.5;
float radius = 0.2;     //radius
float emojiRadius = 1;
float angle = 0;		//angle
float x2 = 0, y2 = 0;	//point on circle
float PI = 3.14159;		//PI
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
		else if (wParam == '1')
			qNo = 1;
		else if (wParam == '2')
			qNo = 2;
		else if (wParam == '3')
			qNo = 3;
		else if (wParam == '4')
			qNo = 4;
		else if (wParam == '5')
			qNo = 5;
		else if (wParam == '6')
			qNo = 6;
		else if (wParam == '7')
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


void triangle() {
	glClearColor(0.0, 0.0, 0.0, 0.0);  // clear the background
	glClear(GL_COLOR_BUFFER_BIT);      // clear the color buffer

	glBegin(GL_TRIANGLES);        // draw a triangle
	glColor3f(1.0, 0.0, 0.0);     // red
	glVertex2f(-0.5, 0.0);    // v1
	glColor3f(0.0, 1.0, 0.0); // green
	glVertex2f(0.0, 0.5);     // v2
	glColor3f(0.0, 0.0, 1.0); // blue
	glVertex2f(0.5, 0.0);     // v3
	glEnd();
}

void point() {
	glClearColor(0.0, 0.0, 0.0, 0.0);  // clear the background
	glClear(GL_COLOR_BUFFER_BIT);      // clear the color buffer

	glPointSize(10.0);         // set the point size
	glBegin(GL_POINTS);        // draw points
	glColor3f(1.0, 0.0, 0.0);     // red
	glVertex2f(-0.5, 0.0);        // v1
	glColor3f(0.0, 1.0, 0.0);     // green
	glVertex2f(0.0, 0.5);         // v2
	glColor3f(0.0, 0.0, 1.0);     // blue
	glVertex2f(0.5, 0.0);         // v3
	glEnd();
}

void lines() {
	glClearColor(0.0, 0.0, 0.0, 0.0);  // clear the background
	glClear(GL_COLOR_BUFFER_BIT);      // clear the color buffer

	glPointSize(10.0);        // set the point size
	glLineWidth(3.0);         // set the line width
	glBegin(GL_LINES);        // draw lines
	glColor3f(1.0, 0.0, 0.0);     // red
	glVertex2f(-0.5, 0.0);        // v1
	glColor3f(0.0, 1.0, 0.0);     // green
	glVertex2f(0.0, 0.5);         // v2
	glColor3f(0.0, 0.0, 1.0);     // blue
	glVertex2f(0.5, 0.0);         // v3
	glEnd();
}

void lineStrip() {
	glClearColor(0.0, 0.0, 0.0, 0.0);  // clear the background
	glClear(GL_COLOR_BUFFER_BIT);      // clear the color buffer

	glPointSize(10.0);        // set the point size
	glLineWidth(3.0);         // set the line width
	glBegin(GL_LINE_STRIP);       // draw the line strip
	glColor3f(1.0, 0.0, 0.0);     // red
	glVertex2f(-0.5, 0.0);        // v1
	glColor3f(0.0, 1.0, 0.0);     // green
	glVertex2f(0.0, 0.5);         // v2
	glColor3f(0.0, 0.0, 1.0);     // blue
	glVertex2f(0.5, 0.0);         // v3
	glColor3f(1.0, 0.0, 0.0);     // red
	glVertex2f(-0.5, 0.0);        // v4
	glEnd();
}

void lineLoop() {
	glClearColor(0.0, 0.0, 0.0, 0.0);  // clear the background
	glClear(GL_COLOR_BUFFER_BIT);      // clear the color buffer

	glPointSize(10.0);        // set the point size
	glLineWidth(3.0);         // set the line width
	glBegin(GL_LINE_LOOP);    // draw the line loop
	glColor3f(1.0, 0.0, 0.0);     // red
	glVertex2f(-0.5, 0.0);        // v1
	glColor3f(0.0, 1.0, 0.0);     // green
	glVertex2f(0.0, 0.5);         // v2
	glColor3f(0.0, 0.0, 1.0);     // blue
	glVertex2f(0.5, 0.0);         // v3
	glEnd();
}

void polygon() {
	glClearColor(0.0, 0.0, 0.0, 0.0);  // clear the background
	glClear(GL_COLOR_BUFFER_BIT);      // clear the color buffer

	glPointSize(10.0);         // set the point size
	glLineWidth(3.0);          // set the line width
	glBegin(GL_POLYGON);       // draw polygon
	glColor3f(1.0, 0.0, 0.0);     // red
	glVertex2f(-0.5, 0.0);        // v1
	glColor3f(0.0, 1.0, 0.0);     // green
	glVertex2f(0.0, 0.5);         // v2
	glColor3f(0.0, 0.0, 1.0);     // blue
	glVertex2f(0.5, 0.0);         // v3
	glEnd();
}

void p1Demo() {
	// glClearColor(0.0, 0.0, 0.0, 0.0);  // clear the background
	// glClear(GL_COLOR_BUFFER_BIT);      // clear the color buffer

	// glBegin(GL_TRIANGLES);        // draw a triangle
	// glColor3f(1.0, 0.0, 0.0);     // red
	// glVertex2f(-0.5, 0.0);    // v1
	// glColor3f(0.0, 1.0, 0.0); // green
	// glVertex2f(0.0, 0.5);     // v2
	// glColor3f(0.0, 0.0, 1.0); // blue
	// glVertex2f(0.5, 0.0);     // v3
	// glEnd();  




	//glClearColor(0.0, 0.0, 0.0, 0.0);  // clear the background
	//glClear(GL_COLOR_BUFFER_BIT);      // clear the color buffer

	//glPointSize(10.0);         // set the point size
	//glBegin(GL_POINTS);        // draw points
	//glColor3f(1.0, 0.0, 0.0);     // red
	//glVertex2f(-0.5, 0.0);        // v1
	//glColor3f(0.0, 1.0, 0.0);     // green
	//glVertex2f(0.0, 0.5);         // v2
	//glColor3f(0.0, 0.0, 1.0);     // blue
	//glVertex2f(0.5, 0.0);         // v3
	//glEnd();




	//glClearColor(0.0, 0.0, 0.0, 0.0);  // clear the background
	//glClear(GL_COLOR_BUFFER_BIT);      // clear the color buffer

	//glPointSize(10.0);        // set the point size
	//glLineWidth(3.0);         // set the line width
	//glBegin(GL_LINES);        // draw lines
	//glColor3f(1.0, 0.0, 0.0);     // red
	//glVertex2f(-0.5, 0.0);        // v1
	//glColor3f(0.0, 1.0, 0.0);     // green
	//glVertex2f(0.0, 0.5);         // v2
	//glColor3f(0.0, 0.0, 1.0);     // blue
	//glVertex2f(0.5, 0.0);         // v3
	//glEnd();





	//glClearColor(0.0, 0.0, 0.0, 0.0);  // clear the background
	//glClear(GL_COLOR_BUFFER_BIT);      // clear the color buffer

	//glPointSize(10.0);        // set the point size
	//glLineWidth(3.0);         // set the line width
	//glBegin(GL_LINE_STRIP);       // draw the line strip
	//glColor3f(1.0, 0.0, 0.0);     // red
	//glVertex2f(-0.5, 0.0);        // v1
	//glColor3f(0.0, 1.0, 0.0);     // green
	//glVertex2f(0.0, 0.5);         // v2
	//glColor3f(0.0, 0.0, 1.0);     // blue
	//glVertex2f(0.5, 0.0);         // v3
	//glEnd();






	//glClearColor(0.0, 0.0, 0.0, 0.0);  // clear the background
	//glClear(GL_COLOR_BUFFER_BIT);      // clear the color buffer

	//glPointSize(10.0);        // set the point size
	//glLineWidth(3.0);         // set the line width
	//glBegin(GL_LINE_LOOP);    // draw the line loop
	//glColor3f(1.0, 0.0, 0.0);     // red
	//glVertex2f(-0.5, 0.0);        // v1
	//glColor3f(0.0, 1.0, 0.0);     // green
	//glVertex2f(0.0, 0.5);         // v2
	//glColor3f(0.0, 0.0, 1.0);     // blue
	//glVertex2f(0.5, 0.0);         // v3
	//glEnd();

}


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
	glClearColor(1.0, 1.0, 1.0, 1.0);  // clear the background
	glClear(GL_COLOR_BUFFER_BIT);      // clear the color buffer

	// RED
	glBegin(GL_TRIANGLES);        // draw a triangle
	glColor3f(1.0, 0.0, 0.0);     // red
	glVertex2f(0.0, 0.5);    // v1
	glVertex2f(-0.8, 0.5);     // v2
	glVertex2f(0.0, 0.0);     // v3
	glEnd();

	// BLACK
	glBegin(GL_TRIANGLES);        // draw a triangle
	glColor3f(0.0, 0.0, 0.0);     // red
	glVertex2f(-0.8, 0.5);    // v1
	glVertex2f(-0.8, 0.0);     // v2
	glVertex2f(0.0, 0.0);     // v3
	glEnd();

	// YELLOW QUAD
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(0.0, 0.5);		// v1
	glVertex2f(0.7, 0.5);		// v2
	glVertex2f(0.7, 0.0);		// v3
	glVertex2f(0.0, 0.0);		// v4
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-0.8, 0.0);		// v1
	glVertex2f(0.7, 0.0);		// v2
	glVertex2f(0.7, -0.5);		// v3
	glVertex2f(-0.8, -0.5);		// v4
	glEnd();

}

void eng() {
	glClearColor(1.0, 1.0, 1.0, 1.0);  // clear the background
	glClear(GL_COLOR_BUFFER_BIT);      // clear the color buffer

	// Flag Size
	glPointSize(10.0);         // set the point size
	glLineWidth(3.0);          // set the line width
	glBegin(GL_LINE_STRIP);       // draw the line strip
	glColor3f(0.0, 0.0, 0.0);     // 
	glVertex2f(-0.5, 0.3);        // v1
	glColor3f(0.0, 0.0, 0.0);     // 
	glVertex2f(0.5, 0.3);         // v2
	glColor3f(0.0, 0.0, 0.0);     // 
	glVertex2f(0.5, -0.5);        // v3
	glColor3f(0.0, 0.0, 0.0);     // 
	glVertex2f(-0.5, -0.5);       // v4
	glColor3f(0.0, 0.0, 0.0);     // 
	glVertex2f(-0.5, 0.3);        // v5
	glEnd();

	// Red Cross
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-0.05, 0.295);		// v1
	glVertex2f(0.05, 0.295);		// v2
	glVertex2f(0.05, -0.495);		// v3
	glVertex2f(-0.05, -0.495);		// v4
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.495, -0.15);		// v1
	glVertex2f(0.495, -0.05);		// v2
	glVertex2f(-0.495, -0.05);		// v3
	glVertex2f(-0.495, -0.15);		// v4
	glEnd();
}

void Scotland() {
	glClearColor(1.0, 1.0, 1.0, 1.0);  // clear the background
	glClear(GL_COLOR_BUFFER_BIT);      // clear the color buffer
	// Flag Size
	glPointSize(10.0);         // set the point size
	glLineWidth(3.0);          // set the line width
	glBegin(GL_LINE_STRIP);       // draw the line strip
	glColor3f(0.0, 0.0, 1.0);     // 
	glVertex2f(-0.5, 0.3);        // v1
	glColor3f(0.0, 0.0, 1.0);     // 
	glVertex2f(0.5, 0.3);         // v2
	glColor3f(0.0, 0.0, 1.0);     // 
	glVertex2f(0.5, -0.5);        // v3
	glColor3f(0.0, 0.0, 1.0);     // 
	glVertex2f(-0.5, -0.5);       // v4
	glColor3f(0.0, 0.0, 1.0);     // 
	glVertex2f(-0.5, 0.3);        // v5
	glEnd();
	// White Cross
	// TOP 
	glBegin(GL_TRIANGLES);        // draw a triangle
	glColor3f(0.0, 0.0, 1.0);     // 
	glVertex2f(-0.4, 0.3);		  // v1 left
	glColor3f(0.0, 0.0, 1.0);	  // 
	glVertex2f(0.4, 0.3);		  // v2 right
	glColor3f(0.0, 0.0, 1.0);	  // 
	glVertex2f(0.0, -0.05);		  // v3 bottom
	glEnd();
	// RIGHT
	glBegin(GL_TRIANGLES);        // draw a triangle
	glColor3f(0.0, 0.0, 1.0);    // 
	glVertex2f(0.5, 0.25);        // v1 top
	glColor3f(0.0, 0.0, 1.0);    // 
	glVertex2f(0.5, -0.45);         // v2 bottom
	glColor3f(0.0, 0.0, 1.0);     // 
	glVertex2f(0.1, -0.1);         // v3 left
	glEnd();
	// BOTTOM
	glBegin(GL_TRIANGLES);        // draw a triangle
	glColor3f(0.0, 0.0, 1.0);     // 
	glVertex2f(0.0, -0.15);        // v1 top
	glColor3f(0.0, 0.0, 1.0);     // 
	glVertex2f(0.4, -0.5);         // v2 right
	glColor3f(0.0, 0.0, 1.0);     // 
	glVertex2f(-0.4, -0.5);         // v3 left
	glEnd();
	// LEFT
	glBegin(GL_TRIANGLES);        // draw a triangle
	glColor3f(0.0, 0.0, 1.0);     // 
	glVertex2f(-0.5, 0.25);        // v1 top
	glColor3f(0.0, 0.0, 1.0);     // 
	glVertex2f(-0.1, -0.1);         // v2 right
	glColor3f(0.0, 0.0, 1.0);     //
	glVertex2f(-0.5, -0.45);         // v3 bottom
	glEnd();
}

void JapanFlag() {
	glClearColor(1.0, 1.0, 1.0, 0.0);  //white
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0, 0.0, 0.0); //red
	glVertex2f(x, y);      //origin of circle
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + radius * cos(angle);
		y2 = y + radius * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	//-- LINE CIRCLE
	//glBegin(GL_LINE_LOOP);
	//glColor3f(1.0, 0.0, 0.0); //red
	// //glVertex2f(x, y);      //origin of circle
	//for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
	//	x2 = x + radius * cos(angle);
	//	y2 = y + radius * sin(angle);
	//	glVertex2f(x2, y2);
	//}
	//glEnd();
	//--

	//-- HALF CIRCLE
	//glBegin(GL_TRIANGLE_FAN);
	//glColor3f(1.0, 0.0, 0.0); //red
	//glVertex2f(x, y);      //origin of circle
	//for (angle = 0; angle <=  PI; angle +=  PI / noOfTri) {              //for (angle = PI; angle <= (2 * PI); angle += (2 * PI)/ noOfTri) bottom half of circle
	//	x2 = x + radius * cos(angle);
	//	y2 = y + radius * sin(angle);
	//	glVertex2f(x2, y2);
	//}
	//glEnd();

	//Flag
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(-0.8, -0.5);
	glVertex2f(-0.8, 0.5);
	glVertex2f(0.8, 0.5);
	glVertex2f(0.8, -0.5);
	glEnd();
}

void emoji() {
	//FACE
	glClearColor(1.0, 1.0, 1.0, 0.0);  //white
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0, 1.0, 0.0); //yellow
	glVertex2f(x, y);      //origin of circle
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + emojiRadius * cos(angle);
		y2 = y + emojiRadius * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	//EYE
	glClearColor(1.0, 1.0, 1.0, 0.0);  //white
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0, 1.0, 0.0); //yellow
	glVertex2f(eX, eY);      //origin of circle
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + radius * cos(angle);
		y2 = y + radius * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
}

void display()
{
	if (qNo == 1)
		pahangFlag();
	else if (qNo == 2)
		n9Flag();
	else if (qNo == 3)
		eng();
	else if (qNo == 4)
		Scotland();
	else if (qNo == 5)
		JapanFlag();
	else if (qNo == 6)
		emoji();
	
	

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