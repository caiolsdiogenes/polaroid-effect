#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <climits>
#include <fstream>
#include <cstring>

#include "glyph.h"
#include "font.h"
#include "img.h"

using namespace std;

void input(image &img, ifstream &in, int border, int space) {
    string id;
    int width, height;
    int rgb;

    in >> id >> width >> height >> rgb;
    in.ignore(INT_MAX, '\n');

    image temp(id,width+(2*border),height+(2*border+space),rgb);

    //img.dalloc();

    img = temp;

    img.init(in,border,space);
}
void input_std(image &img, int border, int space) {
    string id;
    int width, height;
    int rgb;

    cin >> id >> width >> height >> rgb;
    cin.ignore(INT_MAX, '\n');

    image temp(id,width+(2*border),height+(2*border)+space,rgb);

    //img.dalloc();

    img = temp;

    img.init_std(border,space);
}

void output(image img, ofstream &out) {
    img.print(out);
}

void enlarge(image &img, int border, int space) {
  img.enlarge_polaroid(border,space);
}

int main(int argc, char const *argv[]) {

  // TO DO
  // 1) ler a imagem input_file
  // 2) alterar a imagem lida inserindo o efeito polaroid usando
  //    como border como tamanho da borda e space como espaço de texto.
  // 3) ler a fonte font_name
  // 4) inserir o texto msg na imagem usando a fonte lida
  // 5) salvar a imagem resultante em output_file

  ofstream out;
  ifstream in;
  int border = 25;
  int space = 50;
  string filename = "../fonts/ib16x16u.bdf";
  
  string msg;

  cin >> msg;

  if (argc != 1) {
   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-h") == 0) {
        cout << "O usuário poderá passar os seguintes comandos em linha de comando:\n";
        cout << "\n-i (input): para indicar o caminho do arquivo PPM no qual o efeito Polaroid será aplicado.\n";
        cout << "\n-o (output): para indicar o caminho do arquivo no qual a imagem com efeito Polaroid será salva.\n";
        cout << "\n-f (font): para indicar o caminho do arquivo de fonte a ser usado no texto da imagem.\n";
        cout << "\n-b (border): para indicar a largura das bordas a serem acrescentadas ao redor da imagem.\n";
        cout << "\n-s (space): para indicar a largura da base adicional na borda da imagem.\n";
        return 0;
      }
      else if (strcmp(argv[i], "-i") == 0) {
        string ipt = argv[i+1];
        in.open(ipt);
      }
      else if (strcmp(argv[i], "-o") == 0) {
        string otp = argv[i+1];
        out.open(otp);
      }
      else if (strcmp(argv[i], "-f") == 0) {
        filename = argv[i+1];
      }
      else if (strcmp (argv[i], "-b" ) == 0) {
        border = stoi(argv[i+1]);
      }
      else if (strcmp(argv[i], "-s") == 0) {
        space = stoi(argv[i+1]);
      }
   }
  }
  else {
    cerr << "Passe -h em linha de comando para ter informações sobre o uso do programa!\n";
    return 0;
  }
  image img;

  if (in.is_open()) {
    input(img,in,border,space);
  }
  else {
    input_std(img,border,space);
    in.close();
  }
  

  enlarge(img,border,space);

  Font bdf;

  bdf.read_bdf(filename);

  Glyph character;

  character.
  
  if (out.is_open()) {
    output(img,out);
  }
  else {
    out.open("../imgs/image.ppm");
    output(img,out);
  }

  return 0;
}