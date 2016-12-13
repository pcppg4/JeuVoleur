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
/*const char KTokenPlayer1 = 'X';
const char KTokenPlayer2 = 'O';
const char KEmpty        = '-';*/
typedef struct {
    unsigned posX;
    unsigned posY;
    unsigned sizeX (1);
    unsigned sizeY (1);
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

void ShowMatrix (const CMatrix & Mat)
{
    ClearScreen();
    Couleur (KReset);
    for (CVLine line : Mat)
    {
        for (char C : line)
        {
            if (C == KTokenPlayer1) Couleur (KRouge);
            if (C == KTokenPlayer2) Couleur (KBleu);
            cout << C;
            if ((C == KTokenPlayer1)||(C == KTokenPlayer2)) Couleur (KReset);
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

void MoveToken (CMatrix & Mat, char Move, Player player)
{
    switch (Move)
    {
    case 'z':
        if (player.posY > 0)
        {
        Mat[player.posY-1][player.posX] = Mat[player.posY][player.posX];
        Mat[player.posY][player.posX] = KEmpty;
        player.posY = player.posY - 1;
        }
    break;
    case 's':
        if (player.posY < Mat.size()-1)
        {
        Mat[player.posY+1][player.posX] = Mat[player.posY][player.posX];
        Mat[player.posY][player.posX] = KEmpty;
        player.posY = player.posY + 1;

        }
    break;
    case 'q':
        if (player.posX > 0)
        {
        Mat[player.posY][player.posX-1] = Mat[player.posY][player.posX];
        Mat[player.posY][player.posX] = KEmpty;
        player.posX = player.posX - 1;

        }
    break;
    case 'd':
        if (player.posX < Mat[0].size()-1)
        {
        Mat[player.posY][player.posX+1] = Mat[player.posY][player.posX];
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
    Player P1, P2;
    P1.posX = 0;
    P1.posY = 0;
    P2.posX = KSizeX-1;
    P2.posY = KSizeY-1;
    P1.token = 'X';
    P2.token = 'O';
    P1.color = KRouge;
    P2.color = KBleu;

    unsigned NbRnds;
    CPosition pos1, pos2;
    pos1.first = 0;
    pos1.second = 0;
    cout << "Entrez le nombre de rounds" << endl;
    cin >> NbRnds;
    char Mv;
    CMatrix Map;
    InitMat(Map,KSizeX,KSizeY,pos1,pos2);
    ShowMatrix(Map);
    cout << KTokenPlayer1 << " commence et chasse " << KTokenPlayer2 << endl;
    for (unsigned i (0); i < NbRnds*2; ++i)
    {

        ShowMatrix(Map);
        cout << "Au tour de " << (i%2 == 0 ? KTokenPlayer1 : KTokenPlayer2) << endl;
        cin >> Mv;
        MoveToken (Map, Mv, (i%2 == 0 ? pos1 : pos2) );
        if (pos1 == pos2)
        {
            cout << (i%2 == 0 ? KTokenPlayer1 : KTokenPlayer2) << " a gagne !" << endl;
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
