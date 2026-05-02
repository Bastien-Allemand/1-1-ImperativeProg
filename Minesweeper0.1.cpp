#include <iostream>
#include <cstdlib>
#include <ctime>

struct Display
{
    char Bomb;
    char blank;
    char Flaged;
    char Triggered;
};

struct Case
{
    int BombProxy;
    bool Triggered;
    bool Boombed;
    bool Flagged;
};

struct AllCases
{
    Case* all;
    int lineCount;
    int columnCount;
    int HIT;
    int Nbrdecase;
};

Display build;
AllCases Minesweeper;

void PlayGame();
void Gameplay(AllCases& Minesweeper);
void cheat(AllCases& Minesweeper);

int Get2Dto1D(AllCases allCases, int l, int c);

void Digadg(int x, int l)
{
    for (int x1 = x-1; x1 <= x+1; x1++)
    {
        for (int y1 = l-1; y1 <= l+1; y1++)
        {
            if (y1 > 0 && y1 <= Minesweeper.lineCount && x1 > 0 && x1 <= Minesweeper.columnCount)
            {
                int r = Get2Dto1D(Minesweeper,y1,x1);
                if (!Minesweeper.all[r].Triggered && !Minesweeper.all[r].Boombed && !Minesweeper.all[r].Flagged && r >= 0 && r <= Minesweeper.columnCount * Minesweeper.lineCount)
                {
                    std::cout << r;
                    Minesweeper.all[r].Triggered = true;
                    Gameplay(Minesweeper);
                    if (Minesweeper.all[r].BombProxy == 0)
                    {
                        Digadg(x1, y1);
                    }
                }
            }
        }
    }
}

void Difficulty()
{
    int width = 0, height = 0;
    int difficulty;
    std::cout << "Choose Difficulty: " << std::endl
        << " 0 = easy (9x9) 1 = medium (16x16) 2 = Hard (30x16)" << std::endl << "  :";
    std::cin >> difficulty;
    switch (difficulty)
    {
    case 0: width = 9, height = 9;
        break;

    case 1: height = 16, width = 16;
        break;

    case 2: height = 30, width = 16;
        break;

    default: Difficulty();
    }
    Minesweeper.columnCount = width;
    Minesweeper.lineCount = height;
}

void PlayAgain(bool win)
{
    int Result;
    if (win)
    {
        std::cout << "YOU WIN would you like to play again?" << std::endl;
    }
    else
    {
        std::cout << "YOU LOSE would you like to play again?" << std::endl;
    }
    std::cout << "YES(1)/NO(0)";
    std::cin >> Result;
    if (Result)
    {
        PlayGame();
    }
    else
    {
        std::cout << "have a good day and good bye";
        exit(NULL);
    }
}

int Get2Dto1D(AllCases allCases, int l, int c)
{
    return (l-1)*Minesweeper.columnCount+c-1;
}

void Get1DTo2D(const AllCases* allCases, int index, int* l, int* c)
{
    int N = index / Minesweeper.columnCount;
    int numberofcolumn = (index - (Minesweeper.columnCount * N)) + 1;
    N = N + 1;
    *c = numberofcolumn;
    *l = N;
}

void CaseIding(AllCases& checkers)
{
    int length = Minesweeper.columnCount * Minesweeper.lineCount;
    int maxbomb = (length) * 0.15f;
    checkers.Nbrdecase = length - maxbomb;
    int* listdecase = (int*)malloc(sizeof(int) * length);

    for (int i = 0; i < length; i++)
    {
        checkers.all[i].Flagged = false;
        checkers.all[i].BombProxy = 0;
        checkers.all[i].Triggered = false;
        checkers.all[i].Boombed = false;
        listdecase[i] = i;
    }
    int size = length;
    for (int i = 0; i < maxbomb; i++)
    {
        int B = rand() % (size+1);
        int Num = listdecase[B];
        checkers.all[Num].Boombed = true;
        listdecase[B] = listdecase[size - 1];
        size--;
        int bombX = 0, bombY = 0;
        Get1DTo2D(&checkers, Num, &bombY, &bombX);

        /*if ((Num - 1) - Minesweeper.columnCount >= 0 && (Num - 1) - Minesweeper.columnCount <= Minesweeper.columnCount * Minesweeper.lineCount)Minesweeper.all[(Num - 1) - Minesweeper.columnCount].BombProxy++;
        if ((Num + 1) - Minesweeper.columnCount >= 0 && (Num + 1) - Minesweeper.columnCount <= Minesweeper.columnCount * Minesweeper.lineCount)Minesweeper.all[(Num + 1) - Minesweeper.columnCount].BombProxy++;
        if ((Num) - Minesweeper.columnCount >= 0 && (Num) - Minesweeper.columnCount <= Minesweeper.columnCount * Minesweeper.lineCount)Minesweeper.all[(Num) - Minesweeper.columnCount].BombProxy++;
        if ((Num - 1) + Minesweeper.columnCount >= 0 && (Num - 1) + Minesweeper.columnCount <= Minesweeper.columnCount * Minesweeper.lineCount)Minesweeper.all[(Num - 1) + Minesweeper.columnCount].BombProxy++;
        if ((Num + 1) + Minesweeper.columnCount >= 0 && (Num + 1) + Minesweeper.columnCount <= Minesweeper.columnCount * Minesweeper.lineCount)Minesweeper.all[(Num + 1) + Minesweeper.columnCount].BombProxy++;
        
        if ((Num - 1) >= 0 && (Num - 1) <= Minesweeper.columnCount * Minesweeper.lineCount)Minesweeper.all[(Num - 1)].BombProxy++;
        if ((Num + 1) >= 0 && (Num + 1) <= Minesweeper.columnCount * Minesweeper.lineCount)Minesweeper.all[(Num + 1)].BombProxy++;*/

        //if (bombY >= 2 && bombY <= Minesweeper.lineCount-1 && bombX >= 2 && bombX <= Minesweeper.columnCount)
        //{
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {

                    if (x == 0 && y == 0) continue;
                    int coterX, coterY;
                    coterX = bombX - x;
                    coterY = bombY - y;
                    if (coterX >= 0 && coterX <= Minesweeper.columnCount && coterY >= 0 && coterY <= Minesweeper.lineCount)
                    {
                        int Nbr = Get2Dto1D(checkers,coterY,coterX);
                        checkers.all[Nbr].BombProxy++;
                    }
                    
                }
                cheat(Minesweeper);
            }
        
        
        
    }
    /*for (int j = 0; j < length; j++)
    {
        for (int x = -1; x <= 1 ; x++)
        {
            for (int y = -1; y <= 1; y++)
            {
                int N = j + (y * Minesweeper.columnCount) + x;
                if (Minesweeper.all[N].Boombed)
                {
                    Minesweeper.all[j].BombProxy++;
                }
            }
        }
    }*/
}


char Place(int x, int y, AllCases& Cased)
{
    int Id = x + y * Cased.lineCount;
    if (Cased.all[Id].Flagged)
    {
        return build.Flaged;
    }
    else if (Cased.all[Id].Triggered)
    {
        if (Cased.all[Id].Boombed)
        {
            return build.Bomb;
        }
        else 
        {
            if (Cased.all[Id].BombProxy == 0)
            {
                return build.Triggered;
                if (Cased.HIT != Cased.Nbrdecase)
                {
                    Cased.HIT++;
                }
                else
                {
                    PlayAgain(true);
                }
            }
            else
            {
                return (char)(Cased.all[Id].BombProxy + 48);
            }
        }
    }
    else
    {
        return build.blank;
    }
}

void GetPlayerGuess(AllCases& Cased)
{
    int x, y,F;

    std::cout << "voulez vous flag ou retirer un flag? (0 = oui,1 = non) :";
    std::cin >> F;

    std::cout << "Enter coordinates x (1-" << Cased.columnCount << "): ";
    std::cin >> x;

    std::cout << "Enter coordinates y (1-" << Cased.lineCount << "): ";
    std::cin >> y;

    int Num = Get2Dto1D(Cased, x, y);
    if (F == 0)
    {
        if (Cased.all[Num].Flagged == true)
        {
            std::cout << "checked";
            Cased.all[Num].Flagged = false;
        }
        else 
        {
            Cased.all[Num].Flagged = true;
        }
    }
    else
    {
        Cased.all[Num].Triggered = true;
        Digadg(x, y);
    }
}

void Gameplay(AllCases& Minesweeper)
{
    system("cls");
    std::cout << "   ";
    for (int i = 0; i < Minesweeper.columnCount; i++)
    {
        if (i+1 >= 10)
        {
            std::cout << " " << i+1 << " ";
        }
        else
        {
            std::cout << "  " << i+1 << " ";
        }
    }
    std::cout << std::endl;

    for (int i = 0; i < Minesweeper.lineCount; i++)
    {
        std::cout << "   ";
        for (int K = 0; K < Minesweeper.columnCount; K++)
        {
            std::cout << "+---";
        }
        std::cout << "+" << std::endl;
        
        if (i+1 >= 10)
        {
            std::cout << i+1 << " ";
        }
        else
        {
            std::cout << i+1 << "  ";
        }
        for (int l = 0; l < Minesweeper.columnCount; l++)
        {
            std::cout << "| " << Place(i, l, Minesweeper) << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "   ";
    for (int K = 0; K < Minesweeper.columnCount; K++)
    {
        std::cout << "+---";
    }
    std::cout << "+" << std::endl;
}

char cheated(int x, int y, AllCases& Cased)
{
    int Id = x + y * Cased.lineCount;
    if (Cased.all[Id].Flagged)
    {
        return build.Flaged;
    }
    if (Cased.all[Id].Boombed)
    {
       return build.Bomb;
    }
    else
    {
            return (Cased.all[Id].BombProxy + 48);
    }
}

void cheat(AllCases& Minesweeper)
{
    system("cls");
    std::cout << "   ";
    for (int i = 0; i < Minesweeper.columnCount; i++)
    {
        if (i + 1 >= 10)
        {
            std::cout << " " << i + 1 << " ";
        }
        else
        {
            std::cout << "  " << i + 1 << " ";
        }
    }
    std::cout << std::endl;

    for (int i = 0; i < Minesweeper.lineCount; i++)
    {
        std::cout << "   ";
        for (int K = 0; K < Minesweeper.columnCount; K++)
        {
            std::cout << "+---";
        }
        std::cout << "+" << std::endl;

        if (i + 1 >= 10)
        {
            std::cout << i + 1 << " ";
        }
        else
        {
            std::cout << i + 1 << "  ";
        }
        for (int l = 0; l < Minesweeper.columnCount; l++)
        {
            std::cout << "| " << cheated(i, l, Minesweeper) << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "   ";
    for (int K = 0; K < Minesweeper.columnCount; K++)
    {
        std::cout << "+---";
    }
    std::cout << "+" << std::endl;
}

int testguess(bool FirstGuess)
{
    for (int i = 0; i < Minesweeper.columnCount*Minesweeper.lineCount; i++)
    {
        if(Minesweeper.all[i].Boombed)
        {
            if (Minesweeper.all[i].Triggered)
            {
                if (FirstGuess)
                {
                    for (int i = 0; i < Minesweeper.columnCount * Minesweeper.lineCount; i++)
                    {
                        Minesweeper.all[i].Triggered = true;
                    }
                    Gameplay(Minesweeper);
                    PlayAgain(false);
                }
                else
                {
                    CaseIding(Minesweeper);
                    Minesweeper.all[i].Triggered = true;
                    testguess(FirstGuess);
                }
                
            }
        }
    }
    return 0;
}

void PlayGame() 
{
    Difficulty();
    bool Firstguess = false;
    Minesweeper.HIT = 0;
    Minesweeper.all = (Case*)malloc(sizeof(Case) * Minesweeper.columnCount * Minesweeper.lineCount);
    CaseIding(Minesweeper);

    Gameplay(Minesweeper);

    cheat(Minesweeper);
    std::cout << std::endl;

    while (true) 
    {
        GetPlayerGuess(Minesweeper);
        testguess(Firstguess);
        Gameplay(Minesweeper);

        Firstguess = true;
    }
    free(Minesweeper.all);
}

int main()  
{
    build.Bomb = '*';
    build.blank = ' ';
    build.Flaged = 'F';
    build.Triggered = 'H';
    srand(time(nullptr));
    PlayGame();
    return 0;
}
