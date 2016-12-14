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
const char KEmpty = '-';
typedef struct {
    unsigned posX;
    unsigned posY;
    unsigned sizeX;
    unsigned sizeY;
    char token;
    string color;
} Player;

void Couleur (const string & coul);
void ClearScreen ();
void ShowMatrix (const CMatrix & Mat,Player & player1, Player & player2);
void InitMat (CMatrix & Mat, unsigned NbLine, unsigned NbColumn, Player & player1, Player & player2);
void MoveToken (CMatrix & Mat, char Move, Player & player);
void GetBonus(CMatrix & Mat, Player & player);
void PutBonus(CMatrix & Mat, const char & token, const unsigned & posX, const unsigned & posY);
bool CheckWin(Player & player1, Player & player2);
int ppal();

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

void InitMat (CMatrix & Mat, unsigned NbLine, unsigned NbColumn, Player & player1, Player & player2)
{
    Mat.resize(NbLine);
    for (unsigned i (0); i<NbLine; ++i)
    {
        for (unsigned j (0); j<NbColumn; ++j)
        {
            Mat[i].push_back(KEmpty);
        }
    }
    for (unsigned i (player1.posY); i<player1.posY + player1.sizeY; ++i)
        for (unsigned j (player1.posX); j<player1.posX + player1.sizeX; ++j)
            Mat[i][j] = player1.token;
    for (unsigned i (player2.posY); i<player2.posY + player2.sizeY; ++i)
        for (unsigned j (player2.posX); j<player2.posX + player2.sizeX; ++j)
            Mat[i][j] = player2.token;
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

bool CheckWin(Player & player1, Player & player2)
{
    return !((player1.posX > player2.posX + player2.sizeX - 1) ||
            (player1.posX + player1.sizeX - 1 < player2.posX) ||
            (player2.posY > player1.posY + player1.sizeY - 1)  ||
            (player2.posY + player2.sizeY - 1 < player1.posY));
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
    PutBonus(Map,'B',2,2);
    ShowMatrix(Map,player1,player2);
    cout << player1.token << " commence et chasse " << player2.token << endl;
    for (unsigned i (0); i < NbRnds*2; ++i)
    {

        ShowMatrix(Map,player1,player2);
        cout << "Au tour de " << (i%2 == 0 ? player1.token : player2.token) << endl;
        cin >> Mv;
        MoveToken (Map, Mv, (i%2 == 0 ? player1 : player2) );
        if (CheckWin(player1,player2))
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
