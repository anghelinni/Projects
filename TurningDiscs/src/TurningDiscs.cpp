// TurningDiscs.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "TurningDiscs.hpp"

#include <iostream>


TurningDiscs::TurningDiscs()
{
    memcpy( &m_CurrentPositions[ 0 ], &m_StartingPositions[ 0 ], sizeof( m_CurrentPositions ) );
    memset( &m_Solution[ 0 ], 0, sizeof( m_Solution ) );
}

bool TurningDiscs::FindSolution()
{
    PrintCurrentPositions();    
    PrintTurnings();

    int position1[ 4 ];
    int position2[ 4 ];
    int position3[ 4 ];

    for ( int disc1 = 0; disc1 < MAX_TURNS; disc1++ )
    {
        // save current position
        memcpy( &position1[ 0 ], &m_CurrentPositions[ 0 ], sizeof( m_CurrentPositions ) );
        m_Solution[ 0 ] = disc1;

        for ( int disc2 = 0; disc2 < MAX_TURNS; disc2++ )
        {
            // save current position
            memcpy( &position2[ 0 ], &m_CurrentPositions[ 0 ], sizeof( m_CurrentPositions ) );
            m_Solution[ 1 ] = disc2;

            for ( int disc3 = 0; disc3 < MAX_TURNS; disc3++ )
            {
                // save current position
                memcpy( &position3[ 0 ], &m_CurrentPositions[ 0 ], sizeof( m_CurrentPositions ) );
                m_Solution[ 2 ] = disc3;

                for ( int disc4 = 1; disc4 < MAX_TURNS; disc4++ )
                {
                    if ( TurnDiscs( 3 ) )
                    {
                        m_Solution[ 3 ] = disc4;
                        return true;
                    }
                }
                // restore positions
                memcpy( &m_CurrentPositions[ 0 ], &position3[ 0 ], sizeof( m_CurrentPositions ) );
                m_Solution[ 3 ] = 0;

                if ( TurnDiscs( 2 ) )
                {
                    return true;
                }
            }
            // restore positions
            memcpy( &m_CurrentPositions[ 0 ], &position2[ 0 ], sizeof( m_CurrentPositions ) );
            m_Solution[ 2 ] = 0;

            if ( TurnDiscs( 1 ) )
            {
                return true;
            }
        }
        // restore positions
        memcpy( &m_CurrentPositions[ 0 ], &position1[ 0 ], sizeof( m_CurrentPositions ) );
        m_Solution[ 1 ] = 0;

        if ( TurnDiscs( 0 ) )
        {
            return true;
        }
    }

    return false;
}

void TurningDiscs::PrintSolution()
{
    std::cout << "Solution is { " << m_Solution[0] << ", " << m_Solution[ 1 ] << ", " << m_Solution[ 2 ] << ", " << m_Solution[ 3 ] << " }\n";
    PrintCurrentPositions();
}

bool TurningDiscs::TurnDiscs( int _turning )
{
    bool foundSolution = true;

    for ( int i = 0; i < 4; i++ )
    {
        m_CurrentPositions[ i ] += m_Turns[ _turning ][ i ];
        m_CurrentPositions[ i ] += m_CurrentPositions[ i ] < 0 ? 8 : 0;
        m_CurrentPositions[ i ] = m_CurrentPositions[ i ] % 8;
        if ( m_CurrentPositions[ i ] != 0 )
        {
            foundSolution = false;
        }
    }

    //PrintCurrentPositions();

    return foundSolution;
}

void TurningDiscs::PrintCurrentPositions()
{
    std::cout << "Current positions is { " << m_CurrentPositions[ 0 ] << ", " << m_CurrentPositions[ 1 ] << ", " << m_CurrentPositions[ 2 ] << ", " << m_CurrentPositions[ 3 ] << " }\n";
}

void TurningDiscs::PrintTurnings()
{
    std::cout << "Current turnings are:\n"
        << "1: { " << m_Turns[ 0 ][ 0 ] << ", " << m_Turns[ 0 ][ 1 ] << ", " << m_Turns[ 0 ][ 2 ] << ", " << m_Turns[ 0 ][ 3 ] << " }\n"
        << "2: { " << m_Turns[ 1 ][ 0 ] << ", " << m_Turns[ 1 ][ 1 ] << ", " << m_Turns[ 1 ][ 2 ] << ", " << m_Turns[ 1 ][ 3 ] << " }\n"
        << "3: { " << m_Turns[ 2 ][ 0 ] << ", " << m_Turns[ 2 ][ 1 ] << ", " << m_Turns[ 2 ][ 2 ] << ", " << m_Turns[ 2 ][ 3 ] << " }\n"
        << "4: { " << m_Turns[ 3 ][ 0 ] << ", " << m_Turns[ 3 ][ 1 ] << ", " << m_Turns[ 3 ][ 2 ] << ", " << m_Turns[ 3 ][ 3 ] << " }\n";
}

int main()
{
    TurningDiscs t;
    if ( t.FindSolution() )
    {
        t.PrintSolution();
    }
    else
    {
        std::cout << "No solution found :(\n";
    }
    return 0;
}
