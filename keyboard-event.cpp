#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <cstdio>
#include <ctime>

static const int STDIN = 0;
static bool initialized = false;

int keyEvent()
{
  // lit des caractÃ¨res dans un terminal pour faire bouger le serpent

  if (!initialized)
  {
    // en premier (et une seule fois par exÃ©cution) on inialise un
    // terminal

    // termios est une API qui permet de manipuler dans votre
    // programme, des entrÃ©es/sorties faites dans un terminal

    // crÃ©ation d'un terminal
    termios term;

    // la fonction tcgetattr permet d'initialiser des paramÃ¨tres de cette API

    // lÃ  on demande que l'entrÃ©e standard STDIN (on est en c) soit
    // notre terminal i.e. quand on va taper un caractÃ¨re sur notre
    // terminal STDIN recevra ce caractÃ¨re
    tcgetattr(STDIN, &term);

    // lÃ  on met Ã  faux le mode ICANON pour le terminal term (Input
    // CANnonical mode ON)

    // en gros on demande de ne pas lire une ligne de caractÃ¨re (qui se
    // terminerait donc au retour-Ã -la-ligne) mais un seul caractÃ¨re
    // (pour faire bouger le serpent)
    term.c_lflag &= ~ICANON;

    // on demande Ã  ce que la configuration soit prise en compte
    // innmÃ©diatement pour le terminal
    tcsetattr(STDIN, TCSANOW, &term);

    // les entrÃ©es ne seront pas bufferisÃ©es
    setbuf(stdin, NULL);

    // on a fini d'initialiser, au prochain appel de cette fonction,
    // on ne refera plus cette initialisation
    initialized = true;
  }
  int bytesWaiting;
  // int bytesWaiting;

  // la requÃªte pour lire sur notre terminal dÃ©sormais notre STDIN
  // et stocker le caractÃ¨re lu dans la mÃ©moire bytesWaiting
  ioctl(STDIN, FIONREAD, &bytesWaiting);
  return bytesWaiting;
}

void sleepOneLap(const int ms)
{
  clock_t end;
  // on initialise la quantitÃ© de temps Ã  attendre
  end = clock() + ms * CLOCKS_PER_SEC / 1000;
  while (clock() < end)
  {
    // wait i.e. do nothing
  }
}