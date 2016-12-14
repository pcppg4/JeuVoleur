#include <iostream>
#include <vector>

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

typedef vector <char> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMatrix; // un type représentant la grille
typedef pair   <unsigned, unsigned> CPosition; // un type représentant une coordonnée dans la grille
const char KEmpty = '-';
typedef struct {
    unsigned posX;
    unsigned posY;
    unsigned sizeX;
    unsigned sizeY;
    char token;
    string color;
} Player;

void Couleur (const string & coul)
{
    cout << "\033[" << coul <<"m";
}

void ClearScreen ()
{
    cout << "\033[H\033[2J";
}

void ShowMatrix (const CMatrix & Mat,Player & player1, Player & player2)
{
    ClearScreen();
    Couleur (KReset);
    for (CVLine line : Mat)
    {
        for (char C : line)
        {
            if (C == player1.token) Couleur (player1.color);
            if (C == player2.token) Couleur (player2.color);
            cout << C;
            if ((C == player1.token)||(C == player2.token)) Couleur (KReset);
        }
        cout << endl;
    }
}

void InitMat (CMatrix & Mat, unsigned NbLine, unsigned NbColumn, Player & player1, Player & player2){
    Mat.resize(NbLine);
    for (unsigned i (0); i<NbLine; ++i)
    {
        for (unsigned j (0); j<NbColumn; ++j)
        {
            Mat[i].push_back(KEmpty);
        }
    }
    Mat[player1.posY][player1.posX] = player1.token;
    Mat[player2.posY][player2.posX] = player2.token;
}

void MoveToken (CMatrix & Mat, char Move, Player & player)
{
    switch (Move)
    {
    case 'z':
        if (player.posY > 0)
        {
        Mat[player.posY-1][player.posX] = player.token;
        Mat[player.posY][player.posX] = KEmpty;
        player.posY = player.posY - 1;
        }
    break;
    case 's':
        if (player.posY < Mat.size()-1)
        {
        Mat[player.posY+1][player.posX] = player.token;
        Mat[player.posY][player.posX] = KEmpty;
        player.posY = player.posY + 1;

        }
    break;
    case 'q':
        if (player.posX > 0)
        {
        Mat[player.posY][player.posX-1] = player.token;
        Mat[player.posY][player.posX] = KEmpty;
        player.posX = player.posX - 1;

        }
    break;
    case 'd':
        if (player.posX < Mat[0].size()-1)
        {
        Mat[player.posY][player.posX+1] = player.token;
        Mat[player.posY][player.posX] = KEmpty;
        player.posX = player.posX + 1;
        }
    break;
    }
}

int ppal ()
{
    const unsigned KSizeX (5);
    const unsigned KSizeY (5);
    Player player1, player2;
    player1.posX = 0;
    player1.posY = 0;
    player2.posX = KSizeX-1;
    player2.posY = KSizeY-1;
    player1.sizeX = 1;
    player1.sizeY = 1;
    player2.sizeX = 1;
    player2.sizeY = 1;
    player1.token = 'X';
    player2.token = 'O';
    player1.color = KRouge;
    player2.color = KBleu;
    unsigned NbRnds;
    cout << "Entrez le nombre de rounds" << endl;
    cin >> NbRnds;
    char Mv;
    CMatrix Map;
    InitMat(Map,KSizeX,KSizeY,player1,player2);
    ShowMatrix(Map,player1,player2);
    cout << player1.token << " commence et chasse " << player2.token << endl;
    for (unsigned i (0); i < NbRnds*2; ++i)
    {

        ShowMatrix(Map,player1,player2);
        cout << "Au tour de " << (i%2 == 0 ? player1.token : player2.token) << endl;
        cin >> Mv;
        MoveToken (Map, Mv, (i%2 == 0 ? player1 : player2) );
        if ((player1.posX == player2.posX)&&(player1.posY==player2.posY))
        {
            cout << (i%2 == 0 ? player1.token : player2.token) << " a gagne !" << endl;
            return 0;
        }
    }
    cout << "Egalite !" << endl;
    return 0;
}

}

int main()
{
    ppal ();
    return 0;
} 
