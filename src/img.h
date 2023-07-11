#ifndef __IMAGE__
#define __IMAGE__

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <climits>
#include <deque>
#include "font.h"


using namespace std;


class image{
  string id;
  int width, height;
  int rgb;
  unsigned char **red = new unsigned char*[height];
  unsigned char **green = new unsigned char*[height];
  unsigned char **blue = new unsigned char*[height];
  
  public:
  image() {
    id = "P6";
    width = 100;
    height = 100;
    rgb = 255;
  }
  
  image(string identificator, int w, int h, int max): id(identificator), width(w), height(h), rgb(max){}
  
  void init(ifstream &in, int border, int space) {
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

  void init_std(int border, int space) {
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
          cin >> pixel;
          red[i][j] = (unsigned char) pixel;
          cin >> pixel;
          green[i][j] = (unsigned char) pixel;
          cin >> pixel;
          blue[i][j] = (unsigned char) pixel;
          
        }
      }
    }
    else if (id == "P6") {
      for (int i = border; i < height - border - space; i++) {
        for (int j = border; j < width - border; j++) {
          red[i][j] = (unsigned char)getchar();
          green[i][j] = (unsigned char)getchar();
          blue[i][j] = (unsigned char)getchar();
        }
      }
    }
  }

  void print(ofstream &out) {
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

  void enlarge_polaroid(int border,int space) {
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

  void message(const Glyph *character, string msg, int space, int border, int k) {
    int i = height - border - space;
    int j = border + (k * character-> get_device_width_x());
    for (int w = 0; w < character -> get_width(); w++) {
      for (int h = character -> get_height()-1; h >= 0; h--) {
        if (character -> get_bit(w,h)) {
          red[i+h-character->get_y_offset()][j+w-character->get_x_offset()] = 0;
          blue[i+h-character->get_y_offset()][j+w-character->get_x_offset()] = 0;
          green[i+h-character->get_y_offset()][j+w-character->get_x_offset()] = 0;
        }
      }
    }
  }

  int get_width() {return width;}
  int get_height() {return height;}
  string get_id() {return id;}
  int get_max () {return rgb;}
  int get_red (int i, int j) {return red[i][j];}
  int get_green(int i, int j) {return green[i][j];}
  int get_blue(int i, int j) {return blue[i][j];}

  // ~image(){
  //   for (int i = 0; i < height; i++) {
  //     delete[] red[i];
  //     delete[] green[i];
  //     delete[] blue[i];
  //   }
  //   delete[] red;
  //   delete[] green;
  //   delete[] blue;
  // }

};

#endif  // __IMAGE__