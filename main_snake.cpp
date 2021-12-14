#include <iostream>
#include <vector>
#include "keyboard-event.h"


const int lines = 10;
const int columns = 20;
const char ground = '.';
const char WALL = '_';
const char WALL_SIDE = '|';
const int ms = 500;



void drawPlayground(const std::vector<std::vector<char>>& playground){
    //affiche la matrice " le playground"
    
    for(int i = 0; i<playground.size(); i++){
        for(int j = 0; j < playground[i].size(); j++){
            std::cout<<playground[i][j];
        }
    std::cout<<std::endl;
    }
}

void playgroundSetup(std::vector<std::vector<char>>& playground){
    int ligne = playground.size();
    int colonne = playground[0].size();
    for(int j = 0 ; j< colonne; j++){
        playground.at(0).at(j)= WALL;
        playground.at(ligne-1).at(j) = WALL;
    }
    for(int i = 1; i<ligne; i++){
        playground.at(i)[0] = WALL_SIDE;
        playground[i][colonne-1] = WALL_SIDE;
    }
}

std::vector<std::vector<int>> snake_init(std::vector<std::vector<char>>& playground){
  int x = playground[0].size()/2;
  int y = playground.size()/2;
  std::vector<int> temp = {y, x};
  std::vector<std::vector<int>> position = {temp};
  playground.at(y).at(x) = 'O';
  for(int i = 1; i < 5; i++){
    playground.at(y).at(x-i) = 'o';
    temp.at(1) = x-i;
    position.push_back(temp);
  }
  return position;
}

void move_snake(std::vector<std::vector<char>>& playground, std::vector<std::vector<int>>& position, char key){
  //la liste des coordonnées de chaque partie du snake est contenue dans un tableau contenant des tableaux de 2 entiers
  playground.at(position.back().at(0)).at(position.back().at(1)) = '.';
  playground.at(position.at(0).at(0)).at(position.at(0).at(1)) = 'o';
  for(int i = 1; i<position.size(); i++){
    position.at(position.size()-i) = position.at(position.size()-i-1);
  }
  if(key == 'z'){
    position.at(0).at(0) = position.at(1).at(0)-1;
  }
  if(key == 'q'){
    position.at(0).at(1) = position.at(1).at(1)-1;
  }
  if(key == 's'){
    position.at(0).at(0) = position.at(1).at(0)+1;
  }
  if(key == 'd'){
    position.at(0).at(1) = position.at(1).at(1)+1;
  }
  playground.at(position.at(0).at(0)).at(position.at(0).at(1)) = 'O';
}



bool END_OF_GAME(std::vector<std::vector<int>>& position, char key){
  // position est un tableau qui a un nombre de ligne égal à la longueur du serpent 
  // et qui à chaque ligne a la position de la n-ieme partie du serpent
  std::vector<int> head = position.at(0);
  if(key == 'z'){
    for (std::vector<int> ij : position){
      if((ij.at(0) == head.at(0)-1)&&(ij.at(1) == head.at(1))){
        return false;
      }
    }
    if(head.at(0)==1){
      return false;
    }

  }
  else if(key == 'q'){
    for (std::vector<int> ij : position){
      if((ij.at(0) == head.at(0))&&(ij.at(1) == head.at(1)-1)){
        return false;
      }
    }
    if(head.at(1) == 1){
      return false;
    }

  }
  else if(key == 's'){
    for (std::vector<int> ij : position){
      if((ij.at(0) == head.at(0)+1)&&(ij.at(1) == head.at(1))){
        return false;
      }
    }
    if(head.at(0)== lines-2){
      return false;
    }

  }
  else if(key == 'd'){
    for (std::vector<int> ij : position){
      if((ij.at(0) == head.at(0))&&(ij.at(1) == head.at(1)+1)){
        return false;
      }
    }
    if(head.at(1)== columns - 2){
      return false;
    }

  }
  return true;
}


void startGame(const int ms, std::vector<std::vector<char>>& bg,std::vector<std::vector<int>>& position){
  char key = 'd';
  while (true){
    // on efface le playground
    backgroundClear();
    // on dessine le playground
    drawPlayground(bg);
    // le jeu est une boucle sans fin
    // qu'on temporise de ms entre deux mouvements du serpent
    // (on règle comme cela la vitesse du serpent)
    sleepOneLap(ms);
    if (keyEvent()) {
      std::cin >> key;
      // une key a été pressée
      if (END_OF_GAME(position, key)) {
      // si ce n'est pas fin de partie on affiche la clé
        std::cout << key;
        move_snake(bg, position, key);
        }
      else {
        // on efface
        backgroundClear();
        std::cout << "END OF GAME" << std::endl;
        exit(2);
        }
      } 
    else {
      if (END_OF_GAME(position, key)) {
        move_snake(bg, position, key);
        std::cout << "wait !"<< std::endl;
      }
      else{
        backgroundClear();
        std::cout << "END OF GAME" << std::endl;
        exit(2);
      }
    }
  }
}


// pour effacer la sortie
void backgroundClear()
{
  int out = system("clear");
  if (out != 0)
  {
    std::cerr << "clear command failed" << std::endl;
    exit(3);
  }
}

int main(){
    std::vector<char> a(columns, ground);
    std::vector<std::vector<char>> playground(lines,a);
    playgroundSetup(playground);
    std::vector<std::vector<int>> position = snake_init(playground);
    startGame(ms, playground, position);
}