#include "Helper.h"

const int WIDTH = 400;
const int HEIGHT = 400;
static int icolor = 0;
// Image * img_global = NULL;
string filename = "";

void blackWindow() {
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
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

void drawImage(){
  // specify window clear (background) color to be opaque white
  glClearColor(1, 1, 1, 1);

  // clear window to background color
  glClear(GL_COLOR_BUFFER_BIT);
  glRasterPos2i(0,0);

  Image image = readImage(filename);
  // img_global = &image;
  //output image
  writeImage(image);

  cout << "HERE " << image.channels << endl;
  switch (image.channels) {
    case 1:
      glDrawPixels(image.width, image.height, GL_LUMINANCE, GL_UNSIGNED_BYTE, image.pixels);
      break;
    case 2:
      glDrawPixels(image.width, image.height, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, image.pixels);
      break;
    case 3:
      glDrawPixels(image.width, image.height, GL_RGB, GL_UNSIGNED_BYTE, image.pixels);
      break;
    case 4:
      glDrawPixels(image.width, image.height, GL_RGBA, GL_UNSIGNED_BYTE, image.pixels);
      break;
    default:
      break;
  }
  // flush the OpenGL pipeline to the viewport
  glFlush();
}

void handleKey(unsigned char key, int x, int y) {
  switch(key){
    case 'q':		// q - quit
    case 'Q':
    case 27:		// esc - quit
      exit(0);
    case 'r':
    case 'R':
      cout << "Enter the filename: ";
      cin >> filename;
      glutPostRedisplay();
    default:		// not a valid key -- just ignore it
      return;
  }
}

int main (int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("TEST");

  glutDisplayFunc(drawImage);	  // display callback
  glutKeyboardFunc(handleKey);
  glutReshapeFunc(handleReshape); // window resize callback

  if (argc != 2) {
    glutDisplayFunc(blackWindow);
  }
  else {
    filename = argv[1];
  }
  glutMainLoop();
  return 0;
}
