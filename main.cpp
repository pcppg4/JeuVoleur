#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

namespace {
const string KReset   ("0");
const string KNoir    ("30");
const string KRouge   ("31");
const string KVert    ("32");
const string KJaune   ("33");
const string KBleu    ("34");
const string KMAgenta ("35");
const string KCyan    ("36");
const char KEmpty = '-';

typedef vector <char> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMatrix; // un type représentant la grille

typedef struct {
    unsigned posX;
    unsigned posY;
    unsigned sizeX;
    unsigned sizeY;
    char token;
    string color;
} Player;

typedef struct {
    unsigned posX;
    unsigned posY;
    char token;
    string color;
} Obstacle;

void Couleur (const string & coul);
void ClearScreen ();
void ShowMatrix (const CMatrix & Mat,Player & FirstPlayer, Player & SecondPlayer);
void InitMat (CMatrix & Mat, unsigned NbLine, unsigned NbColumn, Player & FirstPlayer, Player & SecondPlayer);
void MoveToken (CMatrix & Mat, char Move, Player & player);
void GetBonus(CMatrix & Mat, Player & player);
void PutBonus(CMatrix & Mat, const char & token, const unsigned & posX, const unsigned & posY);
bool CheckWin(Player & FirstPlayer, Player & SecondPlayer);
int ppal();

void Couleur (const string & coul)
{
    cout << "\033[" << coul <<"m";

}

void ClearScreen ()
{
    cout << "\033[H\033[2J";
}

void ShowMatrix (const CMatrix & Mat,Player & FirstPlayer, Player & SecondPlayer)
{
    ClearScreen();
    Couleur (KReset);
    for (CVLine line : Mat)
    {
        for (char C : line)
        {
            if (C == FirstPlayer.token) Couleur (FirstPlayer.color);
            if (C == SecondPlayer.token) Couleur (SecondPlayer.color);
            cout << C;
            if ((C == FirstPlayer.token)||(C == SecondPlayer.token)) Couleur (KReset);
        }
        cout << endl;
    }
}

void InitMat (CMatrix & Mat, unsigned NbLine, unsigned NbColumn, Player & FirstPlayer, Player & SecondPlayer)
{
    Mat.resize(NbLine);
    for (unsigned i (0); i<NbLine; ++i)
    {
        for (unsigned j (0); j<NbColumn; ++j)
        {
            Mat[i].push_back(KEmpty);
        }
    }
    for (unsigned i (FirstPlayer.posY); i<FirstPlayer.posY + FirstPlayer.sizeY; ++i)
        for (unsigned j (FirstPlayer.posX); j<FirstPlayer.posX + FirstPlayer.sizeX; ++j)
            Mat[i][j] = FirstPlayer.token;
    for (unsigned i (SecondPlayer.posY); i<SecondPlayer.posY + SecondPlayer.sizeY; ++i)
        for (unsigned j (SecondPlayer.posX); j<SecondPlayer.posX + SecondPlayer.sizeX; ++j)
            Mat[i][j] = SecondPlayer.token;
}

void MoveToken (CMatrix & Mat, char Move, Player & player)
{
    switch (Move)
    {
    case 'z':
        if (player.posY > 0)
        {
            player.posY = player.posY - 1;
            GetBonus(Mat, player);
            for (unsigned i (player.posX); i < player.posX + player.sizeX; ++i)
                Mat[player.posY + player.sizeY][i] = KEmpty;
            for (unsigned i (player.posX); i < player.posX + player.sizeX; ++i)
                Mat[player.posY][i] = player.token;
        }
        break;
    case 's':
        if (player.posY + player.sizeY < Mat.size())
        {
            player.posY = player.posY + 1;
            GetBonus(Mat, player);
            for (unsigned i (player.posX); i < player.posX + player.sizeX; ++i)
                Mat[player.posY - 1][i] = KEmpty;
            for (unsigned i (player.posX); i < player.posX + player.sizeX; ++i)
                Mat[player.posY + player.sizeY - 1][i] = player.token;

        }
        break;
    case 'q':
        if (player.posX > 0)
        {
            player.posX = player.posX - 1;
            GetBonus(Mat, player);
            for (unsigned i (player.posY); i < player.posY + player.sizeY; ++i)
                Mat[i][player.posX + player.sizeX] = KEmpty;
            for (unsigned i (player.posY); i < player.posY + player.sizeY; ++i)
                Mat[i][player.posX] = player.token;
        }
        break;
    case 'd':
        if (player.posX + player.sizeX < Mat[0].size())
        {
            player.posX = player.posX + 1;
            GetBonus(Mat, player);
            for (unsigned i (player.posY); i < player.posY + player.sizeY; ++i)
                Mat[i][player.posX - 1] = KEmpty;
            for (unsigned i (player.posY); i < player.posY + player.sizeY; ++i)
                Mat[i][player.posX + player.sizeX - 1] = player.token;
        }
        break;
    }
}

void PutBonus(CMatrix & Mat, const char & token, const unsigned & posX, const unsigned & posY)
{
    Mat[posY][posX] = token;
}

void GetBonus(CMatrix & Mat, Player & player)
{
    for (unsigned i (player.posY); i<player.posY + player.sizeY; ++i)
    {
        for (unsigned j (player.posX); j<player.posX + player.sizeX; ++j)
        {
            if (Mat[i][j] == 'B')
            {
                ++player.sizeX;
                ++player.sizeY;
                for (unsigned i (player.posY); i<player.posY + player.sizeY; ++i)
                    for (unsigned j (player.posX); j<player.posX + player.sizeX; ++j)
                        Mat[i][j] = player.token;
            }
        }
    }
}

bool CheckIfWin(Player & FirstPlayer, Player & SecondPlayer)
{
    return !((FirstPlayer.posX > SecondPlayer.posX + SecondPlayer.sizeX - 1) ||
             (FirstPlayer.posX + FirstPlayer.sizeX - 1 < SecondPlayer.posX) ||
             (SecondPlayer.posY > FirstPlayer.posY + FirstPlayer.sizeY - 1)  ||
             (SecondPlayer.posY + SecondPlayer.sizeY - 1 < FirstPlayer.posY));
}

char GetWinner(Player& FirstPlayer, Player &SecondPlayer, const unsigned & NbrTour){
    return (NbrTour%2 == 0 ? FirstPlayer.token : SecondPlayer.token);
}

Player InitPlayer(const unsigned  largeur, const unsigned  hauteur, const unsigned  AxeX, const unsigned  AxeY, const char  Token,  const string  Color){
    
    Player tmpPlayer;

    tmpPlayer.sizeX = largeur;
    tmpPlayer.sizeY = hauteur;
    tmpPlayer.posX = AxeX;
    tmpPlayer.posY = AxeY;
    tmpPlayer.token = Token;
    tmpPlayer.color = Color;

    return tmpPlayer;
}

int Randomize(int Min, int Max){
    return rand()%(Max-Min) +Min;
}

Obstacle CreateObstacle(const unsigned AxeX, const unsigned AxeY, const char Token, const string Color){

    Obstacle tmpObstacle;
    
    tmpObstacle.posX = AxeX;
    tmpObstacle.posY = AxeY;
    tmpObstacle.token = Token;
    tmpObstacle.color = Color;


    return tmpObstacle;

}
/* TODO ?
bool CanMove(Player Joueur){

}
*/
void PutObstacle(CMatrix & Matrice, Obstacle & obstacle){
    Matrice[obstacle.posY][obstacle.posX] = obstacle.token;
}
/*
void GenerateRandomObstacle(CMatrix & Matrice,  Obstacle & obstacle,  int TailleMax){
    
    Obstacle tmpObstacle = CreateObstacle(obstacle.posX, obstacle.posY, obstacle.token, obstacle.color);
    for(unsigned i(0); i < TailleMax; ++i){
        PutObstacle(Matrice, tmpObstacle);
        tmpObstacle.posX += 1;
        tmpObstacle.posY += 1;

    }
}
*/

void GenerateRandomObstacles(CMatrix & Mat, const char & token, const string & coul,const unsigned & Nb)
{
    Obstacle obs;
    obs.color = coul;
    obs.token = token;
    obs.posX = (unsigned) rand() % Mat[0].size();
    obs.posY = (unsigned) rand() % Mat.size();
    for (unsigned i (0); i<Nb; ++i)
    {
        do
        {
            obs.posX = (unsigned) rand() % Mat[0].size();
            obs.posY = (unsigned) rand() % Mat.size();
        } while (Mat[obs.posY][obs.posY] != KEmpty);
        PutObstacle(Mat,obs);
    }
}

unsigned AskTourMax(){
    unsigned NbRnds;
    cout << "Entrez le nombre de rounds" << endl;
    cin >> NbRnds;
    return NbRnds;
}

int ppal ()
{
    srand(time(0));
    // Taille matrice
    const unsigned KSizeX (10);
    const unsigned KSizeY (10);

    unsigned NbRnds (AskTourMax());
    char EnteredKey;

    //Joueurs & Matrice & Obstacles
    CMatrix Map;

    Player FirstPlayer = InitPlayer( 1, 1, 0, 0, 'X', KRouge);
    Player SecondPlayer = InitPlayer(1, 1, KSizeX - 1, KSizeY - 1, 'Y', KBleu);
    
 //   Obstacle FirstObstacle = CreateObstacle(5, 5, '|', KMAgenta);


    //Création de la matrice
    InitMat(Map, KSizeX, KSizeY, FirstPlayer, SecondPlayer);

    //Création des bonus
    PutBonus(Map,'B',2,2);

    GenerateRandomObstacles(Map,'|',KMAgenta,10);
    ShowMatrix(Map, FirstPlayer, SecondPlayer);

    for (unsigned i (0); i < NbRnds*2; ++i)
    {

        ShowMatrix(Map, FirstPlayer, SecondPlayer);
        Player & actualPlayer = (i%2 == 0 ? FirstPlayer : SecondPlayer);

        cout << "Au tour de " << actualPlayer.token << endl;
        cin >> EnteredKey;


        //if(CanMove(actualPlayer))
        MoveToken(Map, EnteredKey, actualPlayer);

        if (CheckIfWin(FirstPlayer, SecondPlayer))
        {
            cout << GetWinner(FirstPlayer, SecondPlayer, i) << " a gagné !" << endl;
            return 0;
        }
    }
    cout << "Egalité !" << endl;
    return 0;

}
}

int main()
{
    ppal ();
    return 0;
}
