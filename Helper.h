/*
Brady Messer (wmesser@clemson.edu)
CPSC 4040 HW1 Fall 2019
This file contains the Image object and some helper functions to read and write images
*/

#include <GL/glut.h>
#include <iostream>
#include <OpenImageIO/imageio.h>
#include <string>
using namespace std;
OIIO_NAMESPACE_USING;

// The struct that represents an image, can be converted to a class later and
// the read and write image functions can be encapsulated within the class
struct Image {
  int width;
  int height;
  int channels;
  unsigned char * pixels;
  string ext;
};

// Takes in an image and a file name and writes the image to filename
void writeImage(Image image, string filename) {
  const int xres = image.width, yres = image.height;
  const int channels = image.channels;  // RGB
  ImageOutput *out = ImageOutput::create (filename);
  if (!out)
      exit(1);
  ImageSpec spec (xres, yres, channels, TypeDesc::UINT8);
  out->open (filename, spec);
  out->write_image (TypeDesc::UINT8, image.pixels);
  out->close ();
  ImageOutput::destroy (out);
}


// Reads in an image from the specified file and returns an Image struct
Image readImage(string file) {
  ImageInput *in = ImageInput::open(file);
  if (!in) {
      cout << "Could not open file " << file << " exiting. " << endl;
      exit(1);
  }
  const ImageSpec &spec = in->spec();
  Image image;
  image.width = spec.width;
  image.height = spec.height;
  image.channels = spec.nchannels;
  image.ext = file.substr(file.find("."), file.length());
  image.pixels = new unsigned char[image.width*image.height*image.channels];
  in->read_image (TypeDesc::UINT8, &image.pixels[0]);
  in->close ();
  ImageInput::destroy (in);
  return image;
}
