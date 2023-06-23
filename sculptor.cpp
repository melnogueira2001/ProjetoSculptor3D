#include "sculptor.h" //declarar a classe
#include "voxel.h"    //declarar a classe
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

// implementacao do construtor da classe
Sculptor::Sculptor(int _nx, int _ny, int _nz) {

  int i;
  int j;
  int k;
  // contadores de iteracao
  nx = _nx;
  ny = _ny;
  nz = _nz;
  r = 0;
  g = 0;
  b = 0;
  a = 0;
  // atribui os valores aos metodos protect
  v = new Voxel **[nx]; // 1 dimensao da matriz
  for (i = 0; i < nx; i++) {
    v[i] = new Voxel *[ny]; // 2 dimensao da matriz
  }

  for (i = 0; i < nx; i++) {
    for (j = 0; j < ny; j++) {
      v[i][j] = new Voxel[nz]; // 3 dimensao da matriz
    }
  }

  for (i = 0; i < nx; i++) {
    for (j = 0; j < ny; j++) {
      for (k = 0; k < nz; k++) {
        this->v[i][j][k].r = this->r;
        this->v[i][j][k].g = this->g;
        this->v[i][j][k].b = this->b;
        this->v[i][j][k].a = this->a;
        this->v[i][j][k].show = false;
        // iniciliazao de cada voxel para cada membro da struct
      }
    }
  }
}
// implementação do destrutor de classe
Sculptor::~Sculptor() {
  int i;
  int j;
  // contadores de iteração

  for (i = 0; i < nx; i++) {
    for (j = 0; j < ny; j++) {
      delete[] v[i][j]; // libera a última sequencia alocada
    }
  }
  for (i = 0; i < nx; i++) {
    delete[] v[i]; // libera a penultima sequencia alocada
  }
  delete[] v; // libera a primeira sequencia alocada
}

// implementação de membro de seleção de cor de voxel
void Sculptor::setColor(float r, float g, float b, float alpha) {
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = alpha;
  // atribui cores e transparência de acordo com os parâmetros
}

// implementação de membro de ativação de voxel
void Sculptor::putVoxel(int x, int y, int z) {
  if ((this->nx > x) && (this->ny > y) && (this->nz > z)) {

    this->v[x][y][z].r = this->r;
    this->v[x][y][z].g = this->g;
    this->v[x][y][z].b = this->b;
    this->v[x][y][z].a = this->a;
    // ativa o voxel e atribui a ele a cor atual se a posição for valida
  }
}

// implementação do membro de desativação do voxel
void Sculptor::cutVoxel(int x, int y, int z) {
  if ((this->nx > x) && (this->ny > y) && (this->nz > z)) {
    this->v[x][y][z].show = false;
    // desativa o voxel se a posição for valida
  }
}

// implementação do membro de ativação de bloco de voxels
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
  int i;
  int j;
  int k;
  // contadores de iteração

  if ((this->nx >= x0 && this->nx >= x1) &&
      (this->ny >= y0 && this->ny >= y1) &&
      (this->nz >= z0 && this->nz >= z1)) {
    for (i = x0; i < x1; i++) {
      for (j = y0; j < y1; j++) {
        for (k = 0; k < z1; k++) {
          this->v[i][j][k].show = true;
          this->v[i][j][k].r = this->r;
          this->v[i][j][k].g = this->g;
          this->v[i][j][k].b = this->b;
          this->v[i][j][k].a = this->a;
          // ativa um bloco de voxels e atribui a eles a cor atual
        }
      }
    }
  }
}

// implementação de membro de desativação de bloco de voxels
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
  int i;
  int j;
  int k;
  // contadores de iteração

  if ((this->nx >= x0 && this->nx >= x1) &&
      (this->ny >= y0 && this->ny >= y1) &&
      (this->nz >= z0 && this->nz >= z1)) {
    for (i = x0; i < x1; i++) {
      for (j = y0; j < y1; j++) {
        for (k = z0; k < z1; k++) {
          this->v[i][j][k].show = false;
          // desativa um bloco de voxels se as posições forem válidos
        }
      }
    }
  }
}

// implementação de membro de ativação de esfera
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int r) {
  int i;
  int j;
  int k;
  for (i = 0; i < nx; i++) {
    for (j = 0; j < ny; j++) {
      for (k = 0; k < nz; k++) {
        if ((pow(i - xcenter, 2)) + (pow(j - ycenter, 2)) +
                (pow(k - zcenter, 2)) <=
            (pow(r, 2))) {
          this->v[i][j][k].show = true;
          this->v[i][j][k].r = this -> r;
          this->v[i][j][k].g = this -> g;
          this->v[i][j][k].b = this -> b;
          this->v[i][j][k].a = this -> a;
        }
      }
    }
  }
}

// implementação do membro de desativação da esfera
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int r) {
  int i;
  int j;
  int k;

  for (i = 0; i < nx; i++) {
    for (j = 0; j < ny; j++) {
      for (k = 0; k < nz; k++) {
        if ((pow(i - xcenter, 2)) + (pow(j - ycenter, 2)) +
                (pow(k - zcenter, 2)) <=
            (pow(r, 2))) {
          this->v[i][j][k].show = false;
        }
      }
    }
  }
}

// implementação de membro de ativação do elipsoide
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx,
                            int ry, int rz) {
  int i;
  int j;
  int k;

  for (i = 0; i < nx; i++) {
    for (j = 0; j < ny; j++) {
      for (k = 0; k < nz; k++) {
        if ((pow(i - xcenter, 2) / pow(rx, 2)) +
                (pow(j - ycenter, 2) / pow(ry, 2)) +
                (pow(k - zcenter, 2) / pow(rz, 2)) <=
            1) {

          this->v[i][j][k].show = true;

          this->v[i][j][k].r = this->r;
          this->v[i][j][k].g = this->g;
          this->v[i][j][k].b = this->b;
          this->v[i][j][k].a = this->a;
          // ativa um bloco de voxels e atribui a eles a cor atual se a condição
          // for satisfeita
        }
      }
    }
  }
}

// implementação do membro de desativação do elipsoide
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx,
                            int ry, int rz) {
  int i, j, k;

  for (i = 0; i < nx; i++) {
    for (j = 0; j < ny; j++) {
      for (k = 0; k < nz; k++) {
        if ((pow(i - xcenter, 2) / pow(rx, 2)) +
                (pow(j - ycenter, 2) / pow(ry, 2)) +
                (pow(k - zcenter, 2) / pow(rz, 2)) <=
            1) {

          this->v[i][j][k].show = false;
          // desativa um bloco de voxels e atribui a eles a cor atual
        }
      }
    }
  }
}

// implementação do membro de gravação de arquivo
void Sculptor::writeOFF(const char *filename) {
  int i, j, k;
  int n_voxels;
  int n_vertices;

  n_voxels = 0;

  std::ofstream fout;  // objeto para fluxo de saída
  fout.open(filename); // abertura de fluxo para arquivo

  if (!fout.is_open()) {
    std::cout << "O arquivo não pode ser aberto!" << std::endl;

    exit(1);
  } // verifica a abertura do fluxo

  for (i = 0; i < nx; i++) {
    for (j = 0; j < ny; j++) {
      for (k = 0; k < nz; k++) {
        if (v[i][j][k].show == true) {
          n_voxels = n_voxels + 1; // guarda o numero de voxels ativos
        }
      }
    }
  }
  fout << "OFF" << std::endl; // escreve o tipo do arquivo no arquivo
  fout << n_voxels * 8 << " " << n_voxels * 6 << " " << n_voxels * 0
       << std::endl;

  for (i = 0; i < nx; i++) {
    for (j = 0; j < ny; j++) {
      for (k = 0; k < nz; k++) {
        if (v[i][j][k].show == true) {

          fout << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl; // P0
          fout << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl; // P1
          fout << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl; // P2
          fout << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl; // P3
          fout << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl; // P4
          fout << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl; // P5
          fout << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl; // P6
          fout << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl; // P7
        }
      }
    }
  }
  // define as coordenadas do vertice do cubo

  n_voxels = 0; // torna a variavel para valor nulo
  fout << std::fixed;
  fout << std::setprecision(2);

  for (i = 0; i < nx; i++) {
    for (j = 0; j < ny; j++) {
      for (k = 0; k < nz; k++) {
        if (v[i][j][k].show == true) {
          n_vertices = n_voxels * 8;

          fout << "4"
               << " " << n_vertices + 0 << " " << n_vertices + 1 << " "
               << n_vertices + 2 << " " << n_vertices + 3 << " " << v[i][j][k].r
               << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
               << v[i][j][k].a << std::endl;
          fout << "4"
               << " " << n_vertices + 0 << " " << n_vertices + 3 << " "
               << n_vertices + 5 << " " << n_vertices + 4 << " " << v[i][j][k].r
               << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
               << v[i][j][k].a << std::endl;
          fout << "4"
               << " " << n_vertices + 4 << " " << n_vertices + 5 << " "
               << n_vertices + 7 << " " << n_vertices + 6 << " " << v[i][j][k].r
               << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
               << v[i][j][k].a << std::endl;
          fout << "4"
               << " " << n_vertices + 1 << " " << n_vertices + 6 << " "
               << n_vertices + 7 << " " << n_vertices + 2 << " " << v[i][j][k].r
               << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
               << v[i][j][k].a << std::endl;
          fout << "4"
               << " " << n_vertices + 0 << " " << n_vertices + 4 << " "
               << n_vertices + 6 << " " << n_vertices + 1 << " " << v[i][j][k].r
               << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
               << v[i][j][k].a << std::endl;
          fout << "4"
               << " " << n_vertices + 2 << " " << n_vertices + 7 << " "
               << n_vertices + 5 << " " << n_vertices + 3 << " " << v[i][j][k].r
               << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
               << v[i][j][k].a << std::endl;

          n_voxels = n_voxels + 1;
        }
      }
    }
  } // define o numero de vertices, referencias dos vertices, cor e
    // transparencia

  fout.close(); // fecha o fluxo
}
