// #include <GL/glut.h>
// #include <iostream>
// #include <OpenImageIO/imageio.h>
#include "Helper.h"

// using namespace std;
// OIIO_NAMESPACE_USING;

const int WIDTH = 400;
const int HEIGHT = 400;
static int icolor = 0;

void blackWindow() {
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
  // render();
  glFlush();
}

void handleReshape(int w, int h) {
	// set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// define the drawing coordinate system on the viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);// sets up a 2D orthographic viewing region
}

/*
   Display Callback Routine: clear the screen and draw a square
   This routine is called every time the window on the screen needs
   to be redrawn, like if the window is iconized and then reopened
   by the user, and when the window is first created. It is also
   called whenever the program calls glutPostRedisplay()
*/
void drawSquare(){
  // red, yellow, green, cyan, blue, magenta
  float colors[6][3] = {{1, 0, 0}, {1, 1, 0}, {0, 1, 0},
			{0, 1, 1}, {0, 0, 1}, {1, 0, 1}};

  // specify window clear (background) color to be opaque white
  glClearColor(1, 1, 1, 1);

  // clear window to background color
  glClear(GL_COLOR_BUFFER_BIT);

  // first set the drawing color
  glColor3f(colors[icolor][0], colors[icolor][1], colors[icolor][2]);

  // draw the square
  glBegin(GL_POLYGON);
    glVertex2i(100, 100);
    glVertex2i(100, 500);
    glVertex2i(500, 500);
    glVertex2i(500, 100);
  glEnd();

  // flush the OpenGL pipeline to the viewport
  glFlush();
}

// Image readImage(char * argv[]) {
//   ImageInput *in = ImageInput::open(argv[1]);
//   if (!in) {
//       exit(1);
//   }
//   const ImageSpec &spec = in->spec();
//   // int xres = spec.width;
//   // int yres = spec.height;
//   // int channels = spec.nchannels;
//   Image image;
//   image.width = spec.width;
//   image.height = spec.height;
//   image.channels = spec.nchannels;
//   image.pixels = new unsigned char[image.width*image.height*image.channels];
//   // std::vector<unsigned char> pixels (image.width*image.height*image.channels);
//   in->read_image (TypeDesc::UINT8, &image.pixels[0]);
//   in->close ();
//   ImageInput::destroy (in);
//   return image;
// }

int main (int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("TEST");

  glutDisplayFunc(drawSquare);	  // display callback
  glutReshapeFunc(handleReshape); // window resize callback

  if (argc != 2) {
    glutDisplayFunc(blackWindow);
  }
  else {
    //read in image
    Image image = readImage(argv);
    //output image
    writeImage(image);
  }
  glutMainLoop();
  return 0;
}
