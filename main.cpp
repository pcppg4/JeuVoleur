#include <iostream>
#include <vector>
#include <string>
using namespace std;


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

void InitMat (CMatrix & Mat, unsigned NbLine, unsigned NbColumn, Player & FirstPlayer, Player & SecondPlayer){
    Mat.resize(NbLine);
    for (unsigned i (0); i<NbLine; ++i)
    {
        for (unsigned j (0); j<NbColumn; ++j)
        {
            Mat[i].push_back(KEmpty);
        }
    }
    Mat[FirstPlayer.posY][FirstPlayer.posX] = FirstPlayer.token;
    Mat[SecondPlayer.posY][SecondPlayer.posX] = SecondPlayer.token;
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
void SetPlayerSize( Player & player, const unsigned & largeur, const unsigned & hauteur){
    player.sizeX = largeur;
    player.sizeY = hauteur;
}

void SetPlayerPosition(Player & player, const unsigned & AxeX, const unsigned & AxeY){
    player.posX = AxeX;
    player.posY = AxeY;
}

void SetPlayerToken(Player & player, const char & Token){
    player.token = Token;
}

void SetPlayerColor(Player & player, const string & Color){
    player.color = Color;
}

unsigned AskTourMax(){
    unsigned NbRnds;
    cout << "Entrez le nombre de rounds" << endl;
    cin >> NbRnds;
    return NbRnds;
}


bool CheckIfWin(Player &FirstPlayer, Player &SecondPlayer){
    return ((FirstPlayer.posX == SecondPlayer.posX)&&(FirstPlayer.posY == SecondPlayer.posY)) ;
}

char GetWinner(Player& FirstPlayer, Player &SecondPlayer, const unsigned & NbrTour){
    return (NbrTour%2 == 0 ? FirstPlayer.token : SecondPlayer.token);
}

int ppal ()
{

    const unsigned KSizeX (5);
    const unsigned KSizeY (5);
    unsigned NbRnds = AskTourMax();
    char EnteredKey;

    Player FirstPlayer;
    Player SecondPlayer;
    CMatrix Map;


    SetPlayerPosition(FirstPlayer, 0, 0);
    SetPlayerPosition(SecondPlayer, KSizeX - 1, KSizeY - 1);

    SetPlayerSize(FirstPlayer, 1, 1);
    SetPlayerSize(SecondPlayer, 1, 1);

    SetPlayerToken(FirstPlayer, 'X');
    SetPlayerToken(SecondPlayer, 'Y');

    SetPlayerColor(FirstPlayer, KRouge);
    SetPlayerColor(SecondPlayer, KBleu);


    InitMat(Map, KSizeX, KSizeY, FirstPlayer, SecondPlayer);
    ShowMatrix(Map, FirstPlayer, SecondPlayer);

    cout << FirstPlayer.token << " commeeence et chasse " << SecondPlayer.token << endl;

    for (unsigned i (0); i < NbRnds*2; ++i)
    {

        ShowMatrix(Map, FirstPlayer, SecondPlayer);
        cout << "Au tour de " << (i%2 == 0 ? FirstPlayer.token : SecondPlayer.token) << endl;

        cin >> EnteredKey;

        MoveToken (Map, EnteredKey, (i%2 == 0 ? FirstPlayer : SecondPlayer) );

        if (CheckIfWin(FirstPlayer, SecondPlayer))
        {
            cout << GetWinner(FirstPlayer, SecondPlayer, i) << " a gagne !" << endl;
            return 0;
        }
    }
    cout << "Egalite !" << endl;
    return 0;


}

int main()
{
    ppal ();
    return 0;
}
