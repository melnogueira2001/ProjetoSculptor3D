#include <iostream>
#include <fstream>
#include <string>
#include "sculptor.h"

int main(void) {

  Sculptor exemplo(50, 50, 50);//geracao de matriz

  exemplo.setColor(0.02, 0.3467, 0.02, 0.9); 
  exemplo.putBox(0, 50, 0, 1, 0, 50); //base
  
  //implementacao do cubo
  exemplo.setColor(0.950, 0.02, 0.01, 0.9); //vermelho
  exemplo.putBox(0, 7, 1, 7, 0, 7);

  exemplo.cutBox(4, 7, 4, 7, 0, 7); //cortar cubo

  //implementacao de esfera
  exemplo.setColor(0.745, 0.245, 0.035, 0.9);
  exemplo.putSphere(15, 15, 15, 7);

  exemplo.cutSphere(12, 15, 12, 4); //cortar esfera

  //implementacao de elipsoide
  exemplo.setColor(0.02, 0.02, 0.940, 0.9);
  exemplo.putEllipsoid(30, 15, 30, 7, 3, 10);

  exemplo.cutEllipsoid(30, 15, 25, 5, 2, 14); //cortar elipsoide

  std::cout << "O ARQUIVO exemplo.off FOI CRIADO!" << std::endl;
  
  exemplo.writeOFF("exemplo.off"); } //geracao do arquivo
