#include <GL/glut.h>
#include <iostream>
#include <OpenImageIO/imageio.h>
using namespace std;
OIIO_NAMESPACE_USING;

struct Image {
  int width;
  int height;
  int channels;
  unsigned char * pixels;
};

void writeImage(Image image) {
  const char *filename = "output.jpg";
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


Image readImage(char * argv[]) {
  ImageInput *in = ImageInput::open(argv[1]);
  if (!in) {
      exit(1);
  }
  const ImageSpec &spec = in->spec();
  // int xres = spec.width;
  // int yres = spec.height;
  // int channels = spec.nchannels;
  Image image;
  image.width = spec.width;
  image.height = spec.height;
  image.channels = spec.nchannels;
  image.pixels = new unsigned char[image.width*image.height*image.channels];
  // std::vector<unsigned char> pixels (image.width*image.height*image.channels);
  in->read_image (TypeDesc::UINT8, &image.pixels[0]);
  in->close ();
  ImageInput::destroy (in);
  return image;
}
