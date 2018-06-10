#pragma once

#define MAX_TURNS 16

class TurningDiscs
{
public:
    TurningDiscs();
    bool FindSolution();
    void PrintSolution();

private:
    bool TurnDiscs( int _turning );
    void PrintCurrentPositions();
    void PrintTurnings();

    int m_Turns[ 4 ][ 4 ] = {
        { 0, 2, 0, -2 },
        { 1, 0, -3, -1 },
        { 0, -1, 1, 0 },
        { -1, 0, 1, 0 }
    };
    int m_StartingPositions[ 4 ] = { -1, 3, 0, 3 };
    int m_CurrentPositions[ 4 ];
    int m_Solution[ 4 ];
};
