#include <iostream>
#include <vector>

using namespace std;

namespace {


typedef vector <char> CVLine;  
typedef vector <CVLine> CMatrix;  
typedef pair   <unsigned, unsigned> CPosition; 

const string KReset   ("0");
const string KNoir    ("30");
const string KRouge   ("31");
const string KVert    ("32");
const string KJaune   ("33");
const string KBleu    ("34");
const string KMAgenta ("35");
const string KCyan    ("36");

const char KTokenPlayer1 = 'X';
const char KTokenPlayer2 = 'O';
const char KEmpty        = '-';
const char KObstacle     = '#';

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

void InitMat (CMatrix & Mat, unsigned NbLine, unsigned NbColumn, CPosition & PosPlayer1, CPosition & PosPlayer2){
    Mat.resize(NbLine);
    for (unsigned i (0); i<NbLine; ++i)
    {
        for (unsigned j (0); j<NbColumn; ++j)
        {
            Mat[i].push_back(KEmpty);
        }
    }
    Mat[PosPlayer1.second][PosPlayer1.first] = KTokenPlayer1;
    Mat[PosPlayer2.second][PosPlayer2.first] = KTokenPlayer2;
}

void MoveToken (CMatrix & Mat, char Move, CPosition & Pos)
{
    switch (Move)
    {
    case 'z':
        if (Pos.second > 0)
        {
        Mat[Pos.second-1][Pos.first] = Mat[Pos.second][Pos.first];
        Mat[Pos.second][Pos.first] = KEmpty;
        Pos.second = Pos.second - 1;
        }
    break;
    case 's':
        if (Pos.second < Mat.size()-1)
        {
        Mat[Pos.second+1][Pos.first] = Mat[Pos.second][Pos.first];
        Mat[Pos.second][Pos.first] = KEmpty;
        Pos.second = Pos.second + 1;

        }
    break;
    case 'q':
        if (Pos.first > 0)
        {
        Mat[Pos.second][Pos.first-1] = Mat[Pos.second][Pos.first];
        Mat[Pos.second][Pos.first] = KEmpty;
        Pos.first = Pos.first - 1;

        }
    break;
    case 'd':
        if (Pos.first < Mat[0].size()-1)
        {
        Mat[Pos.second][Pos.first+1] = Mat[Pos.second][Pos.first];
        Mat[Pos.second][Pos.first] = KEmpty;
        Pos.first = Pos.first + 1;
        }
    break;
    }
}

int intAlea(const int min, const int max){
    return min + (rand() % (int)(max - min + 1));

}

bool isHittingObstacle(CMatrix & Matrice, const CPosition Position1){
    
}

void creeObstacle(CMatrix & Matrice, const char & symboleObstacle, const CPosition & Position ){
    Matrice[Position.second][Position.first] = symboleObstacle;
}

int ppal ()
{
    const unsigned KSizeX (10);
    const unsigned KSizeY (10);
    unsigned NbRnds;
    CPosition pos1, pos2;
    pos1.first = 0;
    pos1.second = 0;
    pos2.first = KSizeX-1;
    pos2.second = KSizeY-1;
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
