#pragma once

//
//	This is to make a bridge btw the code and the grapgic API
//	In this file we are using the OpenGL API, but can be easily changed without changing the main code
//


#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/freeglut.h"

class Color {
    public:
    int r;
    int g;
    int b;
};

namespace RenderAPI{

	typedef GLuint VertexBuffer;


	inline void StartRenderAPI(int argc, char **argv, int width, int height)
	{
		// init glut:
		glutInit(&argc, argv);
		
		// specify the display mode to be RGB and mutiple buffering:
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
		// specify the initial window position:
		glutInitWindowPosition(500, 100);
		// specify the initial window size:
		glutInitWindowSize(width, height);
		// create the window and set title:
		glutCreateWindow("CG");
		
		//disable some opengl functions that will not be used
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);

		//set the opengl background color
		glClearColor(0.0, 1.0, 0.0, 0.0);
		glMatrixMode(GL_PROJECTION);
		//tell what will be the type and size of the view
		//in this case we are using a 2d ortho with size width by heigth because we want to every pixel be a point
		gluOrtho2D(0.0, width, 0.0, height);

		//init glew to handle with the buffers
		glewInit();
		if (!glewIsSupported("GL_VERSION_2_0 ")) {
			exit(0);
		}
	}

	inline void Reshape(int width, int height) {
		glViewport(0, 0, width, height);
		
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0.0, width, 0.0, height);
	}


	//clear the buffer 
	inline void BufferClear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//start the API render lood
	inline void RenderLoop()
	{
		glutMainLoop();
	}

	//Create a vertex buffer
	inline void CreateVBO(VertexBuffer *_vbo, int width, int height)
	{
		if (!_vbo)return;
		//Create vertex buffer object
		glGenBuffers(1, _vbo);
		glBindBuffer(GL_ARRAY_BUFFER, *_vbo);

		//Initialize VBO
		//set the size of the buffer
		//look that we multiply by 5 because we want 2 floats to be the pixel position and 3 to be the pixel color
		unsigned int size = width * height * sizeof(float) * 5;
		glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	inline void DeleteVBO(VertexBuffer* _vbo)
	{
		glDeleteBuffers(1, _vbo);
	}

	//bind the buffer with a cpu vertex buffer that can be changed by the user
	inline void BufferBind(const VertexBuffer &vbo){
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}

	//TODO: Use your color struct here
	//Map the buffer data to the graphics card 
	inline void MapBuffer(Color *color_buffer, int width, int height){
		//get the graphics card actual buffer
		float *buffer = (float*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		if (!buffer)return;
		Color *c_buff = color_buffer;
		
		
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++, c_buff++) {
				//set the pix position 
				buffer[(y*width + x) * 5 + 0] = (float) x;
				buffer[(y*width + x) * 5 + 1] = (float) y;
				//set the pix rgb values
				buffer[(y*width + x) * 5 + 2] = c_buff->r;
				buffer[(y*width + x) * 5 + 3] = c_buff->g;
				buffer[(y*width + x) * 5 + 4] = c_buff->b;
			}
		}
		//Unmap the buffer, this tell the GC (graphics card) that we have finished our cahnges
		glUnmapBuffer(GL_ARRAY_BUFFER);

		//here we tell the GC how our data is organized
		//here we tell taht we are using 2 floats for position, the total pixel size in floats is 20 and the position is in the posi 0 (the start)
		glVertexPointer(2, GL_FLOAT, 20, 0);
		//here we tell that we are using 3 floats for color, the total pixel size in floats is 20 and the color is in the posi 8
		//(because the position occupied the 8 first bytes)
		glColorPointer(3, GL_FLOAT, 20, (GLvoid*)8);

		//tell the CG to draw our data
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		//will draw our pixels where every one is a point, he will start at posi 0 of our buffer and will draw width * height pixels
		glDrawArrays(GL_POINTS, 0, width * height);
		glDisableClientState(GL_VERTEX_ARRAY);
	}


	inline void SwapBuffers(){
		glutSwapBuffers();
	}

	inline void ReDisplay() {
		glutPostRedisplay();
	}
	//Event handlers
	inline void KeyboardFunc(void(*callback)(unsigned char, int, int))		{ glutKeyboardFunc(callback); }
	inline void ReshapeFunc(void(*callback)(int, int))						{ glutReshapeFunc(callback); }
	inline void DisplayFunc(void(*callback)(void))							{ glutDisplayFunc(callback); }
	inline void MouseFunc(void(*callback)(int, int, int, int))				{ glutMouseFunc(callback); }
	inline void MotionFunc(void(*callback)(int, int))						{ glutMotionFunc(callback); }
	
}