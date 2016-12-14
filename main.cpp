#include <iostream>
#include <vector>

using namespace std;


const string KReset   ("0");
const string KNoir    ("30");
const string KRouge   ("31");
const string KVert    ("32");
const string KJaune   ("33");
const string KBleu    ("34");
const string KMAgenta ("35");
const string KCyan    ("36");
const char KEmpty = '-';

typedef vector <char> CVLine; 
typedef vector <CVLine> CMatrix; 
typedef pair   <unsigned, unsigned> CPosition; 
typedef pair   <unsigned, unsigned> CTaille; 

typedef struct {

    CPosition position;
    CTaille size;
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
    Mat[FirstPlayer.position.second][FirstPlayer.position.first] = FirstPlayer.token;
    Mat[SecondPlayer.position.second][SecondPlayer.position.first] = SecondPlayer.token;
}

void MoveToken (CMatrix & Mat, char Move, Player & player)
{
    switch (Move)
    {
    case 'z':
        if (player.position.first > 0)
        {
        Mat[player.position.first-1][player.position.second] = player.token;
        Mat[player.position.first][player.position.second] = KEmpty;
        player.position.first = player.position.first - 1;
        }
    break;
    case 's':
        if (player.position.first < Mat.size()-1)
        {
        Mat[player.position.first+1][player.position.second] = player.token;
        Mat[player.position.first][player.position.second] = KEmpty;
        player.position.first = player.position.first + 1;

        }
    break;
    case 'q':
        if (player.position.second > 0)
        {
        Mat[player.position.first][player.position.second-1] = player.token;
        Mat[player.position.first][player.position.second] = KEmpty;
        player.position.second = player.position.second - 1;

        }
    break;
    case 'd':
        if (player.position.second < Mat[0].size()-1)
        {
        Mat[player.position.first][player.position.second+1] = player.token;
        Mat[player.position.first][player.position.second] = KEmpty;
        player.position.second = player.position.second + 1;
        }
    break;
    }
}

void setPlayerPosition(Player & player, const unsigned KSizeX, const unsigned KSizeY) {
	player.position = make_pair(KSizeX - 1, KSizeY - 1);
}

void setPlayerSize(Player & player, const unsigned X, const unsigned Y) {
	player.size = make_pair(X, Y);
}

void setPlayerToken(Player & player, const char Token) {
	player.token = Token;
}

void setPlayerColor(Player & player, const string Color) {
	player.color = Color;
}
int ppal ()
{
    const unsigned KSizeX (5);
    const unsigned KSizeY (5);
    Player FirstPlayer, SecondPlayer;
 
	setPlayerPosition(FirstPlayer, 1, 1);
	setPlayerPosition(SecondPlayer, KSizeX - 1, KSizeY - 1);
	 
	setPlayerSize(FirstPlayer, 1, 1);
	setPlayerSize(SecondPlayer, 1, 1);

	setPlayerToken(FirstPlayer, 'X');
	setPlayerToken(SecondPlayer, 'Y');
	 
	setPlayerColor(FirstPlayer, KRouge);
	setPlayerColor(SecondPlayer, KBleu);
	 
    unsigned NbRnds;
    cout << "Entrez le nombre de rounds" << endl;
    cin >> NbRnds;
    char Mv;
    CMatrix Map;
    InitMat(Map,KSizeX,KSizeY, FirstPlayer, SecondPlayer);
    ShowMatrix(Map, FirstPlayer, SecondPlayer);
    cout << FirstPlayer.token << " commence et chasse " << SecondPlayer.token << endl;
    for (unsigned i (0); i < NbRnds*2; ++i)
    {

        ShowMatrix(Map, FirstPlayer, SecondPlayer);
        cout << "Au tour de " << (i%2 == 0 ? FirstPlayer.token : SecondPlayer.token) << endl;
        cin >> Mv;
        MoveToken (Map, Mv, (i%2 == 0 ? FirstPlayer : SecondPlayer) );
        if ((FirstPlayer.position.second == SecondPlayer.position.second)&&(FirstPlayer.position.first== SecondPlayer.position.first))
        {
            cout << (i%2 == 0 ? FirstPlayer.token : SecondPlayer.token) << " a gagne !" << endl;
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