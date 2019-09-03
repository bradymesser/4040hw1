#include "Helper.h"

const int WIDTH = 400;
const int HEIGHT = 400;
static int icolor = 0;
Image * img_global = NULL;

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

  if (img_global != NULL) {
    cout << "HERE " << img_global->channels << endl;
    switch (img_global->channels) {
      case 1:
        glDrawPixels(img_global->width, img_global->height, GL_LUMINANCE, GL_UNSIGNED_BYTE, img_global->pixels);
        break;
      case 2:
        glDrawPixels(img_global->width, img_global->height, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, img_global->pixels);
        break;
      case 3:
        glDrawPixels(img_global->width, img_global->height, GL_RGB, GL_UNSIGNED_BYTE, img_global->pixels);
        break;
      case 4:
        glDrawPixels(img_global->width, img_global->height, GL_RGBA, GL_UNSIGNED_BYTE, img_global->pixels);
        break;
      default:
        break;
    }
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
    //read in image
    Image image = readImage(argv[1]);
    img_global = &image;
    //output image
    writeImage(image);
  }
  glutMainLoop();
  return 0;
}
