#ifndef __IMAGE__
#define __IMAGE__

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <climits>
#include <deque>


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
  void init() {
    for (int i = 0; i < height; i++) {
        red[i] = new unsigned char[width];
        green[i] = new unsigned char[width];
        blue[i] = new unsigned char[width];
    }

    if (id  == "P3") {
      id = "P6";
      for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
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
      for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
          red[i][j] = (unsigned char)getchar();
          green[i][j] = (unsigned char)getchar();
          blue[i][j] = (unsigned char)getchar();
        }
      }
    }
  }

  void print() {
    cout << id << "\n";
    cout << width << " " << height << "\n";
    cout << rgb << "\n";
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        cout << red[i][j] << green[i][j] << blue[i][j];
      }
    }
  }

  int get_width() {
    return width;
  }

  int get_height() {
    return height;
  }

  string get_id() {
    return id;
  }

  int get_max () {
    return rgb;
  }

  int get_red (int i, int j) {
    return red[i][j];
  }
  int get_green(int i, int j) {
    return green[i][j];
  }
  int get_blue(int i, int j) {
    return blue[i][j];
  }

  void transfer(image temp) {
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        red[i][j] = temp.get_red(i,j);
        green[i][j] = temp.get_green(i,j);
        blue[i][j] = temp.get_blue(i,j);
      }
    }
  }

  void enlarge_polaroid(image img) {
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (i < 25 || i >= height - 25) {
          red[i][j] = (unsigned char) 255;
          green[i][j] = (unsigned char) 255;
          blue[i][j] = (unsigned char) 255;
        }
        else if (j < 25 || j >= width - 25) {
          red[i][j] = (unsigned char) 255;
          green[i][j] = (unsigned char) 255;
          blue[i][j] = (unsigned char) 255;
        }
        else {
          red[i][j] = ()
        }
      }
    }
  }

  void dalloc() {
    for (int i = 0; i < height; i++) {
      delete[] red[i];
      delete[] green[i];
      delete[] blue[i];
    }
    delete[] red;
    delete[] green;
    delete[] blue;
  }

  // ~image(){
  //   for (int i = 0; i < height; i++) {
  //     delete[] red[i];
  //     delete[] green[i];
  //     delete[] blue[i];
  // }
  //   delete[] red;
  //   delete[] green;
  //   delete[] blue;
  // }

};

#endif  // __IMAGE__
