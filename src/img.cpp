#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <climits>
#include <deque>

#include "glyph.h"
#include "font.h"
#include "img.h"

using namespace std;

image::image() {
  id = "P6";
  width = 100;
  height = 100;
  rgb = 255;
}

image::~image(){
  for (int i = 0; i < height; i++) {
      delete[] red[i];
      delete[] green[i];
      delete[] blue[i];
  }
  delete[] red;
  delete[] green;
  delete[] blue;
}
  
void image::init(ifstream &in, int border, int space) {
  for (int i = 0; i < height; i++) {
    red[i] = new unsigned char[width];
    green[i] = new unsigned char[width];
    blue[i] = new unsigned char[width];
  }

  if (id  == "P3") {
    id = "P6";
    for (int i = border; i < height-border-space; i++) {
      for (int j = border; j < width-border; j++) {
        int pixel;
        in >> pixel;
        red[i][j] = (unsigned char) pixel;
        in >> pixel;
        green[i][j] = (unsigned char) pixel;
        in >> pixel;
        blue[i][j] = (unsigned char) pixel;
      }
    }
  }
  else if (id == "P6") {
    for (int i = border; i < height - border - space; i++) {
      for (int j = border; j < width - border; j++) {
        red[i][j] = (unsigned char)in.get();
        green[i][j] = (unsigned char)in.get();
        blue[i][j] = (unsigned char)in.get();
      }
    }
  }
  in.close();
}

void image::print(ofstream &out) {
  out << id << endl;
  out << width << " " << height << endl;
  out << rgb << endl;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      out << red[i][j] << green[i][j] << blue[i][j];
    }
  }
  out.close();
  }

  void image::enlarge_polaroid(int border,int space) {
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (i < border || i >= height-border-space || j < border || j >= width-border) {
          red[i][j] = 255;
          green[i][j] = 255;
          blue[i][j] = 255;
        }
      }
    }
  }

  void image::message(const Glyph *character, int space, int border, int &j) {
    int i = height - space;
    for (int w = 0; w < character -> get_width(); w++) {
      for (int h = 0; h < character -> get_height(); h++) {
        if (character -> get_bit(w,h)) {
          red[i-character->get_height()+h-character->get_y_offset()][j+w+character->get_x_offset()] = 0;
          blue[i-character->get_height()+h-character->get_y_offset()][j+w+character-> get_x_offset()] = 0;
          green[i-character->get_height()+h-character->get_y_offset()][j+w+character->get_x_offset()] = 0;
        }
      }
    }
    j += character-> get_device_width_x(); 
  }

  void image::gray() {
    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j++) {
          int avg = (red[i][j] + green[i][j] + blue[i][j])/3;
          red[i][j] = avg;
          green[i][j] = avg;
          blue[i][j] = avg; 
        }
    }
  }

/**
 * Aplica efeito sepia na imagem.
 * 
 * Créditos: dyclassroom.com.
*/
void image::sepia(int border, int space) {
  for (int i = border; i < height-space-border; i++) {
    for (int j = border; j < width-border; j++) {
      double tr = 0.393 * red[i][j] + 0.769 * green[i][j] + 0.189 * blue[i][j];
      double tg = 0.348 * red[i][j] + 0.686 * green[i][j] + 0.168 * blue[i][j];
      double tb = 0.272 * red[i][j] + 0.534 * green[i][j] + 0.131 * blue[i][j];
      red[i][j] = tr <= 255? tr : 255;
      green[i][j] = tg <= 255? tg : 255;
      blue[i][j] = tb <= 255? tb : 255;
    }
  }
}

void image::summer(int border, int space) {
  for (int i = border; i < height-space-border; i++) {
    for (int j = border; j < width - border; j++) {
      if (red[i][j] < 205)red[i][j] = 205;
      if (blue[i][j] > 50)blue[i][j] = 50;
    }
  }
}

void image::winter(int border, int space) {
  for (int i = border; i < height-space-border; i++) {
    for (int j = border; j < width-border; j++) {
      if (red[i][j] > 50) red[i][j] = 50;
      if (blue[i][j] < 205) blue[i][j] = 205;
    }
  }
}

void image::inverse(int border, int space) {
  for (int i = border; i < height-space-border; i++) {
    for (int j = border; j < width-border; j++) {
      red[i][j] = 255 - red[i][j];
      green[i][j] = 255 - green[i][j];
      blue[i][j] = 255 - blue[i][j];
    }
  }
}