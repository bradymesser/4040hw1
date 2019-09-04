#include "Helper.h"

const int WIDTH = 500;
const int HEIGHT = 500;
static int icolor = 0;
string filename = "";
Image img_global;

void handleReshape(int w, int h) {
	// set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// define the drawing coordinate system on the viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  glOrtho( 0, w, 0, h, 0.1, 1 );
  // flip the image to the correct orientation
  glPixelZoom( 1, -1 );
  glRasterPos3f(0, h - 1, -0.3);
}

void drawImage(){
  // specify window clear (background) color to be opaque white
  glClearColor(1,1,1,1);

  // clear window to background color
  glClear(GL_COLOR_BUFFER_BIT);

  if (filename == "") {
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    return;
  }

  Image image = readImage(filename);
  img_global = image;
	// Set window to be the same size as the image
  glutReshapeWindow(image.width, image.height);
  glutPostRedisplay();

  switch (image.channels) {
    case 1:
			// set unpack alignment to 1 so that rows aren't skipped in the pixmap
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glDrawPixels(image.width, image.height, GL_LUMINANCE, GL_UNSIGNED_BYTE, image.pixels);
			break;
    case 2:
			// I'm not sure if 2 channels is a case but I implemented it anyways
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
      break;
    case 'w':
    case 'W': {
      string temp;
      cout << "Enter the name of the output file: ";
      cin >> temp;
      writeImage(img_global, temp);
      break;
    }
    default:		// not a valid key -- just ignore it
      return;
  }
}

int main (int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("IMGVIEW");

  glutDisplayFunc(drawImage);	  // display callback
  glutKeyboardFunc(handleKey);
  glutReshapeFunc(handleReshape); // window resize callback

  if (argc == 2) {
		filename = argv[1];
  }

  glutMainLoop();
  return 0;
}
