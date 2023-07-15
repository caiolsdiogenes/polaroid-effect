#ifndef __IMAGE__
#define __IMAGE__

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <climits>
#include "font.h"
#include "glyph.h"

using namespace std;

/**
 * Classe que representa uma imagem.
*/
class image{
  string id;                                          /// Identificador da imagem;
  int width;                                          /// Largura da imagem;
  int height;                                         /// Altura da imagem;
  int rgb;                                            /// Valor máximo de cada pixel;
  unsigned char **red = new unsigned char*[height];   /// Valor de vermelho dos pixels imagem;
  unsigned char **green = new unsigned char*[height]; /// Valor de verde dos pixels da imagem;
  unsigned char **blue = new unsigned char*[height];  /// Valor de azul dos pixels da imagem;
  
  public:
  image();
  image(string identificator, int w, int h, int max): id(identificator), width(w), height(h), rgb(max){}
  
  ~image();
  
  /**
   * Lê a imagem pixel por pixel do arquivo de entrada passado pelo usuário em linha de comando.
   * 
   * @param in Arquivo de entrada de dados.
   * @param border Tamanho da borda branca a ser adicionada na imagem.
   * @param space Tamanho da borda extra a ser adicionada na base da imagem.
  */
  void init(ifstream &in, int border, int space);

  /**
   * Imprime a imagem no arquivo de sáida de dados passado pelo usuário em linha de comando.
   * Caso o usuário não tenha passado nenhum arquivo de sáida, um arquivo será assumido como default.
   * 
   * @param out Arquivo de saída de dados.
  */
  void print(ofstream &out);

  /**
   * Adiciona a imagem uma borda branca + uma borda adicional na base da imagem.
   * 
   * @param border Tamanho da borda branca a ser adicionada na imagem.
   * @param space Tamanho da borda extra a ser adicionada na base da imagem.
  */
  void enlarge_polaroid(int border,int space);


  /**
   * Escreve um glifo na imagem.
   * 
   * @param character Glifo de um caractere da mensagem.
   * @param space Tamanho da borda extra adicionada na base da imagem.
   * @param border Tamanho da borda branca adicionada na imagem.
   * @param j Posição relativa à largura da imagem usada como parâmetro para a escrita do glifo.
  */
  void message(const Glyph *character, int space, int border, int &j);


  /**
   * Aplica na imagem o efeito de cinza.
  */
  void gray();

  /**
   * Aplica na imagem o efeito sépia.
   * 
   * @param border Tamanho da borda branca adicionada na imagem.
   * @param space Tamanho da borda extra adicionada na base da imagem.
  */
  void sepia(int border, int space);

  /**
   * Aplica na imagem o efeito verão.
   * 
   * @param border Tamanho da borda branca adicionada na imagem.
   * @param space Tamanho da borda extra adicionada na base da imagem.
  */
  void summer(int border, int space);

  /**
   * Aplica na imagem o efeito inverno.
   * 
   * @param border Tamanho da borda branca adicionada na imagem.
   * @param space Tamanho da borda extra adicionada na base da imagem.
  */
  void winter(int border, int space);
  /**
   * Aplica na imagem o efeito inverso.
   * 
   * @param border Tamanho da borda branca adicionada na imagem.
   * @param space Tamanho da borda extra adicionada na base da imagem.
  */
  void inverse(int border, int space);

  /**
  * Consulta a largura da imagem. 
  */
  int get_width() {return width;}

  /**
   * Consulta a altura da imagem.
  */
  int get_height() {return height;}

  /**
   * Consulta o identificador da imagem.
  */
  string get_id() {return id;}

  /**
   * Consulta o valor máximo de um pixel na imagem.
  */
  int get_max () {return rgb;}

  /**
   * Consulta o valor de vermelho de um pixel da imagem.
   * 
   * @param i Posição relativa à altura em que o pixel está localizado.
   * @param j Posição relativa à largura em que o pixel está localizado.
  */
  int get_red (int i, int j) {return red[i][j];}

  /**
   * Consulta o valor de verde de um pixel da imagem.
   * 
   * @param i Posição relativa à altura em que o pixel está localizado.
   * @param j Posição relativa à largura em que o pixel está localizado.
  */
  int get_green(int i, int j) {return green[i][j];}

  /**
   * Consulta o valor de azul de um pixel da imagem.
   * 
   * @param i Posição relativa à altura em que o pixel está localizado.
   * @param j Posição relativa à largura em que o pixel está localizado.
  */
  int get_blue(int i, int j) {return blue[i][j];}
};

#endif  // __IMAGE__