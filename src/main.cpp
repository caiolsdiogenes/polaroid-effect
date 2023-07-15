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
#include "img.cpp"

using namespace std;
/**
 * Lê a imagem do arquivo passado pelo usuário em linha de comando. 
 * Retorna um objeto da classe image.
 * 
 * @param in Arquivo que contém os dados da imagem e será usado para a leitura da imagem.
 * @param border Tamanho da borda branca a ser adicionada na imagem.
 * @param space Tamanho da borda extra a ser adicionada na base da imagem.
*/
image input(ifstream &in, int border, int space) {
    string id;
    int width, height;
    int rgb;

    in >> id >> width >> height >> rgb;
    in.ignore(INT_MAX, '\n');

    image img(id,width+(2*border),height+(2*border+space),rgb);

    img.init(in,border,space);

    return img;
}

/**
 * Escreve na imagem cada caractere da mensagem passada pelo usuário.
 * 
 * @param bdf A fonte que contém os caracteres que vão ser escritos.
 * @param img A imagem na qual os caracteres vão ser escritos.
 * @param border Tamanho da borda branca adicionada na imagem.
 * @param space Tamanho da borda extra adicionada na base da imagem.
*/
void write(Font &bdf, image &img, int border, int space, string msg) {
  int j;
  for (int k = 0; k < (int)msg.size(); k++) {
    const Glyph *character = bdf.get_glyph((int)msg[k]);
    if (k == 0) j = border;
    img.message(character,space,border,j);
  }
}

/**
 * Imprime a imagem no arquivo passado pelo usuário em linha de comando.
 * Caso o usuário não tenha passado nenhum arquivo de saída, um arquivo será assumido como default.
 * 
 * @param img Imagem a ser imprimida.
 * @param out Arquivo de saída de dados.
*/
void output(image &img, ofstream &out) {
  img.print(out);
}

/**
 * Adiciona à imagem uma borda branca + uma borda adicional na base da imagem.
 * 
 * @param img Imagem na qual vão ser adicionadas as bordas.
 * @param border Tamanho da borda branca a ser adicionada na imagem.
 * @param space Tamanho da borda extra a ser adicionada na base da imagem. 
*/
void enlarge(image &img, int border, int space) {
  img.enlarge_polaroid(border,space);
}

/**
 * Lê e interpreta os argumentos passados em linha de comando pelo usuário.
 * 
 * @param argc Número de argumentos passados em linha de comando.
 * @param argv Vetor de string que armazena os argumentos passados em linha de comando.
 * @param out Arquivo de saída de dados.
 * @param in Arquivo de entrada de dados.
 * @param border Tamanho da borda branca a ser adicionada na imagem.
 * @param space Tamanho da borda extra a ser adicionada na base da imagem.
 * @param filename Arquivo no qual vai ser lido a fonte.
 * @param ipt Nome do arquivo de entrada de dados.
 * @param otp Nome do arquivo de saída de dados.
 * @param help Booleano que indica se vai ser necessário imprimir o help na saída padrão.
 * @param effect Efeito a ser aplicado na imagem.
 * @param noArg Booleano que indica se o programa foi chamado sem passar nenhum argumento em linha de comando.
*/
void arg(int argc, char const *argv[], ofstream &out, ifstream &in, int &border, int &space, string &filename, string &ipt, string &otp, bool &help, string &effect, bool &noArg) {
  if (argc != 1) {
   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-h") == 0) {
        cout << "O usuário poderá passar os seguintes comandos em linha de comando:\n";
        cout << "\n-i (input): para indicar o caminho do arquivo PPM no qual o efeito Polaroid será aplicado.\n";
        cout << "\n-o (output): para indicar o caminho do arquivo no qual a imagem com efeito Polaroid será salva.\n";
        cout << "\n-f (font): para indicar o caminho do arquivo de fonte a ser usado no texto da imagem.\n";
        cout << "\n-b (border): para indicar a largura das bordas a serem acrescentadas ao redor da imagem.\n";
        cout << "\n-s (space): para indicar a largura da base adicional na borda da imagem.\n";
        cout << "\n-e (effect): para selecionar um efeito adicional (gray, sepia, summer, winter, inverse) para ser aplicado na imagem.\n";
        help = true;
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
      else if (strcmp(argv[i], "-e") == 0) {
        effect = argv[i+1];
      }
   }
  }
  else {
    cerr << "O usuário deverá passar argumentos em linha de comando para que o programa possa funcionar!\n\n-h(help): informa sobre o funcionamento do programa.\n";
    noArg = true;
  }
}

/**
 * Aplica um efeito na imagem.
 * 
 * @param img Imagem na qual o efeito será aplicado.
 * @param effect Efeito a ser aplicado na imagem.
 * @param border Tamanho da borda branca a ser adicionada da imagem.
 * @param space Tamanho da borda extra a ser adicionada na base da imagem.
*/
void applie(image &img, string effect, int border, int space) {
  if (effect == "default") return;
  else if (effect == "gray") img.gray();
  else if (effect == "sepia") img.sepia(border,space);
  else if (effect == "summer") img.summer(border,space);
  else if (effect == "winter") img.winter(border,space);
  else if (effect == "inverse") img.inverse(border,space);
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
  string ipt;
  string otp;
  string effect = "default";
  bool help = false;
  bool noArg = false;

  arg(argc,argv,out,in,border,space,filename,ipt,otp,help,effect,noArg);

  if (help || noArg) return 0;

  string msg;
  getline(cin, msg);
  
  image img = input(in,border,space);
  
  enlarge(img,border,space);

  applie(img,effect,border,space);

  Font bdf;

  bdf.read_bdf(filename);

  write(bdf,img,border,space,msg);

  if (out.is_open()) {
    output(img,out);
  }
  else {
    out.open("../imgs/image.ppm");
    output(img,out);
  }

  return 0;
}