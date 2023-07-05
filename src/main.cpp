#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <climits>
#include <fstream>

#include "glyph.h"
#include "font.h"
#include "img.h"

using namespace std;

void input(image &img) {
    string id;
    int width, height;
    int rgb;

    cin >> id >> width >> height >> rgb;
    cin.ignore(INT_MAX, '\n');
    
    image temp(id,width,height,rgb);

    img.dalloc();

    img = temp;

    img.init();
}

void output(image img) {
    img.print();
}

void enlarge(image &img) {
  image enlarged(img.get_id(),img.get_width()+50, img.get_height()+50, img.get_max());
  enlarged.enlarge_polaroid(img);
  img = enlarged;
  img.transfer(enlarged);

}

int main(int argc, char const *argv[]) {

  // TO DO
  // 1) ler a imagem input_file
  // 2) alterar a imagem lida inserindo o efeito polaroid usando
  //    como border como tamanho da borda e space como espaço de texto.
  // 3) ler a fonte font_name
  // 4) inserir o texto msg na imagem usando a fonte lida
  // 5) salvar a imagem resultante em output_file

  image img;

  input(img);

  enlarge(img);
  
  output(img);

  return 0;
}
