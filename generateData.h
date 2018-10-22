#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

//------------
#define SIZE_OF_UUID    0x41

//------------ Not used yet, may not be used
unsigned char* genUUID(unsigned char* strUUID, unsigned int uSize)
{
    srand(time(NULL));
    memset(strUUID, 0, uSize);

    sprintf((char*) strUUID, "%x%x-%x-%x-%x-%x%x%x", 
            rand(), rand(),                 // Generates a 64-bit Hex number
            rand(),                         // Generates a 32-bit Hex number
            ((rand() & 0x0fff) | 0x4000),   // Generates a 32-bit Hex number of the form 4xxx (4 indicates the UUID version)
            rand() % 0x3fff + 0x8000,       // Generates a 32-bit Hex number in the range [0x8000, 0xbfff]
            rand(), rand(), rand());        // Generates a 96-bit Hex number

    return strUUID;
}

//------------
bool isPrime(unsigned long int ulNumber)
{
//  cout << "P check: " << ulNumber;
    if(ulNumber != 2UL)
    {
        if(ulNumber < 2UL || (ulNumber % 2UL) == 0)
        {
//          cout << "false" << endl;
            return false;
        }
        for(unsigned long int ulItr = 3UL; (ulItr * ulItr) <= ulNumber; ulItr += 2UL)
        {
            if((ulNumber % ulItr) == 0)
            {
//              cout << "false" << endl;
                return false;
            }
        }
    }

//  cout << "true" << endl;
    return true;
}

//------------
bool isPerfectSquare(unsigned long int ulNumber)
{
    unsigned long int ulTempNumber = sqrt(ulNumber);

    return ((ulTempNumber * ulTempNumber) == ulNumber);
}

//------------
bool isFibonacciSeriesNumber(unsigned long int ulNumber)
{
//  cout << "F Check: " << ulNumber << ", " << (isPerfectSquare(5UL * ulNumber * ulNumber + 4UL) || isPerfectSquare(5UL * ulNumber * ulNumber - 4UL)) << endl;

    return (isPerfectSquare(5UL * ulNumber * ulNumber + 4UL) || isPerfectSquare(5UL * ulNumber * ulNumber - 4UL));
}

//------------------------------------------------------------------------------
class clPlayers;
clPlayers   *ptrRootPlayer, *ptrNewPlayer, *ptrLastPlayer;            // root not required for a DLL, using it to save traversing from top to the bottom

class clPlayers
{
    private:                                            // Intentionally explicit
        clPlayers          *ptrPrevPlayer;
        unsigned long int   ulPlayerID;
//      unsigned char       strUUID[SIZE_OF_UUID];
        unsigned int        uLevel;
        unsigned long int   uScore;
        unsigned int        uCurrentGameID;
        unsigned int        uInventoryItemCount;
        bool                isFraudulentPlayer;
        clPlayers          *ptrNextPlayer;

    public:
        clPlayers(void)
        {
            ptrPrevPlayer = ptrLastPlayer;              // Will be NULL for the first player
            ulPlayerID = 10000UL + clPlayers::ulPlayerCount++;
//          memset(strUUID, 0, SIZE_OF_UUID);
//          ::genUUID(strUUID, SIZE_OF_UUID);
            uLevel = 1;
            uScore = 0UL;
            uCurrentGameID = 0;
            uInventoryItemCount = 0;
            isFraudulentPlayer = (::isFibonacciSeriesNumber(ulPlayerCount - 1) || ::isPrime(ulPlayerCount - 1));
            if(ptrLastPlayer != NULL)
            {
                ptrLastPlayer->ptrNextPlayer = this;
            }
            ptrNextPlayer = NULL;
        }

        static void generateOnePlayer(void)
        {
            ptrNewPlayer = new clPlayers;
            if(ptrNewPlayer == NULL)
            {
                cout << "ERROR: OOM or another exception. Aborting...";
                exit(1);
            }

            if(ptrRootPlayer == NULL)
            {
                ptrRootPlayer = ptrNewPlayer;
            }
            ptrLastPlayer = ptrNewPlayer;
        }

        static void dumpPlayersList(void)
        {
            clPlayers      *ptrTempPlayer = ptrRootPlayer;

            cout << "ptrPrevPlayer, PlayerID, Level, Score, CurrentGameID, InventoryItemCount, isFraudulentPlayer, ptrNextPlayer" << endl;
            while(ptrTempPlayer != NULL)
            {
                cout << ptrTempPlayer->ptrPrevPlayer << ", " << ptrTempPlayer->ulPlayerID << ", " << ptrTempPlayer->uLevel << ", " \
                     << ptrTempPlayer->uScore << ", " << ptrTempPlayer->uCurrentGameID << ", " << ptrTempPlayer->uInventoryItemCount << ", " \
                     << ptrTempPlayer->isFraudulentPlayer << ", " << ptrTempPlayer->ptrNextPlayer << endl;

                ptrTempPlayer = ptrTempPlayer->ptrNextPlayer;
            }
        }

        static void dropPlayersList(void)
        {
            while(ptrRootPlayer != NULL)
            {
                ptrLastPlayer = ptrRootPlayer;
                ptrRootPlayer = ptrRootPlayer->ptrNextPlayer;

                delete  ptrLastPlayer;
            }
        }

        ~clPlayers()
        {
            // Nothing to do at the moment
        }

        static unsigned long int ulPlayerCount;
};
//------------------------------------------------------------------------------