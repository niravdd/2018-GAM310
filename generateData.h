/* (c) Copyright 2018, Nirav Doshi */
/* This code is licensed under MIT license. */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <random>
// #include "random.h"          // Uncomment, if you want to use the pcg in the markFraudPlayers()
#include <ctime>
#include <math.h>
using namespace std;

//------------
#define SIZE_OF_UUID    0x41
#define _DEBUG_
// #define _DEBUG_DEEP_

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
#ifdef  _DEBUG_DEEP_
    cout << "--- P check: " << ulNumber;
#endif
    if(ulNumber != 2UL)
    {
        if(ulNumber < 2UL || (ulNumber % 2UL) == 0)
        {
#ifdef  _DEBUG_DEEP_
            cout << "false" << endl;
#endif
            return false;
        }
        for(unsigned long int ulItr = 3UL; (ulItr * ulItr) <= ulNumber; ulItr += 2UL)
        {
            if((ulNumber % ulItr) == 0)
            {
#ifdef  _DEBUG_DEEP_
                cout << "false" << endl;
#endif
                return false;
            }
        }
    }

#ifdef  _DEBUG_DEEP_
    cout << "true" << endl;
#endif
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
#ifdef  _DEBUG_DEEP_
    cout << "--- F Check: " << ulNumber << ", " << (isPerfectSquare(5UL * ulNumber * ulNumber + 4UL) || isPerfectSquare(5UL * ulNumber * ulNumber - 4UL)) << endl;
#endif

    return (isPerfectSquare(5UL * ulNumber * ulNumber + 4UL) || isPerfectSquare(5UL * ulNumber * ulNumber - 4UL));
}

//------------------------------------------------------------------------------
class clRPGPlayers;
clRPGPlayers   *ptrRootPlayer, *ptrNewPlayer, *ptrLastPlayer;            // root not required for a DLL, using it to save traversing from top to the bottom

class clRPGPlayers
{
    private:                                            // Intentionally explicit
        clRPGPlayers       *ptrPrevPlayer;
        unsigned long int   ulPlayerID;
//      unsigned char       strUUID[SIZE_OF_UUID];
        unsigned int        uLevel;
        unsigned long int   ulScore;
        unsigned int        uCurrentGameID;
        unsigned int        uInventoryItemCount;
        bool                isFraudulentPlayer;
        clRPGPlayers       *ptrNextPlayer;

    public:
        clRPGPlayers(void)
        {
            ptrPrevPlayer = ptrLastPlayer;              // Will be NULL for the first player
            ulPlayerID = 10000UL + clRPGPlayers::ulRPGPlayerCount++;
//          memset(strUUID, 0, SIZE_OF_UUID);
//          ::genUUID(strUUID, SIZE_OF_UUID);
            uLevel = 1;
            ulScore = 0UL;
            uCurrentGameID = 0;
            uInventoryItemCount = 0;
            isFraudulentPlayer = false;
/*
            isFraudulentPlayer = (::isFibonacciSeriesNumber(ulRPGPlayerCount - 1) || ::isPrime(ulRPGPlayerCount - 1));
            if(isFraudulentPlayer == true)
            {
                clRPGPlayers::ulRPGFraudPlayerCount++;
            }
*/
            if(ptrLastPlayer != NULL)
            {
                ptrLastPlayer->ptrNextPlayer = this;
            }
            ptrNextPlayer = NULL;
        }

        void updatePlayerData(unsigned int uNewLevel, unsigned long int ulNewScore, unsigned int uNewCurrentGameID, unsigned int uNewInventoryItemCount)
        {
            uLevel = uNewLevel;
            ulScore = ulNewScore;
            uCurrentGameID = uNewCurrentGameID;
            uInventoryItemCount = uNewInventoryItemCount;
        }

        unsigned int getPlayerLevel(void)                               { return uLevel; }
        unsigned long int getPlayerScore(void)                          { return ulScore; }
        unsigned int getCurrentGameID(void)                             { return uCurrentGameID; }
        unsigned int getInventoryItemCount(void)                        { return uInventoryItemCount; }

        void setPlayerLevel(unsigned int uNewLevel)                     { uLevel = uNewLevel; }
        void setPlayerScore(unsigned long int ulNewScore)               { ulScore = ulNewScore; }
        void setCurrentGameID(unsigned int uNewCurrentGameID)           { uCurrentGameID = uNewCurrentGameID; }
        void setInventoryItemCount(unsigned int uNewInventoryItemCount) { uInventoryItemCount = uNewInventoryItemCount; }

        static void generateOnePlayer(void)
        {
            ptrNewPlayer = new clRPGPlayers;
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

        static void markFraudPlayers(unsigned int nPercentage)
        {
            clRPGPlayers               *ptrTempPlayer = ptrRootPlayer;
            vector<unsigned long int>   vecFraudPlayers;
            random_device               rd;
            mt19937                     random(rd());
        //  pcg random(rd);                                     // Needs the random.h, uncomment it if this is used
            uniform_int_distribution<unsigned long int> ulDistro(1, clRPGPlayers::ulRPGPlayerCount);

            for(unsigned long int ulItr = 0; ulItr < static_cast<unsigned long int>((clRPGPlayers::ulRPGPlayerCount * nPercentage)/100); ulItr++)
            {
                vecFraudPlayers.push_back(ulDistro(random));
            }

#ifdef  _DEBUG_DEEP_
            for(vector<unsigned long int>::iterator vItr = vecFraudPlayers.begin(); vItr != vecFraudPlayers.end(); ++vItr)
            {
                cout << *vItr << " .. ";
            }
            cout << endl;
#endif

            sort(vecFraudPlayers.begin(), vecFraudPlayers.end());

#ifdef  _DEBUG_DEEP_
            for(vector<unsigned long int>::iterator vItr = vecFraudPlayers.begin(); vItr != vecFraudPlayers.end(); ++vItr)
            {
                cout << *vItr << " .. ";
            }
            cout << endl;
#endif

            for(vector<unsigned long int>::iterator vItr = vecFraudPlayers.begin(); vItr != vecFraudPlayers.end(); ++vItr)
            {
                while(ptrTempPlayer != NULL)
                {
                    if((ptrTempPlayer->ulPlayerID - 10000UL) == *vItr)
                    {
                        ptrTempPlayer->isFraudulentPlayer = true;
                        clRPGPlayers::ulRPGFraudPlayerCount++;

                        ++vItr;                                                 // Checking the next number in the vector
                        while(*vItr == (ptrTempPlayer->ulPlayerID - 10000UL))   // Skip duplicate PlayerIDs in the vector
                        {
                            ++vItr;
                        }
                        --vItr;                                             // Check done. Step back, allow the for() to increment
                        ptrTempPlayer = ptrTempPlayer->ptrNextPlayer;       // Next player

                        break;
                    }
                    else
                    {
                        ptrTempPlayer = ptrTempPlayer->ptrNextPlayer;       // Find the next player
                    }
                }
            }
        }

        static void dumpPlayersList(void)
        {
            clRPGPlayers      *ptrTempPlayer = ptrRootPlayer;

#ifdef  _DEBUG_
            cout << "[CurrentLocation]: [ptrPrevPlayer], ";
#endif
            cout << "PlayerID, Level, Score, CurrentGameID, InventoryItemCount, isFraudulentPlayer";
#ifdef  _DEBUG_
            cout << ", [ptrNextPlayer]";
#endif
            cout << endl;
            while(ptrTempPlayer != NULL)
            {
#ifdef  _DEBUG_
                cout << "[" << hex << setfill('0') << setw(0x10) << ptrTempPlayer << "]: [" << setw(0x10) << ptrTempPlayer->ptrPrevPlayer << dec << "], ";  // Debug data
#endif
                cout << ptrTempPlayer->ulPlayerID << ", " << ptrTempPlayer->uLevel << ", " << ptrTempPlayer->ulScore << ", " << ptrTempPlayer->uCurrentGameID << ", " \
                     << ptrTempPlayer->uInventoryItemCount << ", " << ptrTempPlayer->isFraudulentPlayer;
#ifdef  _DEBUG_
                cout << ", [" << hex << setfill('0') << setw(0x10) << ptrTempPlayer->ptrNextPlayer << "]";                                                  // Debug data
#endif
                cout << dec << endl;

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

        ~clRPGPlayers()
        {
            // Nothing to do, yet
        }

        static unsigned long int ulRPGPlayerCount;
        static unsigned long int ulRPGFraudPlayerCount;
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
class clPlayerRPGameData
{
    private:                                            // Intentionally explicit
        unsigned long int       ulRPGPlayerDataRecordCount;
        unsigned int            uLevels[80][4][3];      // { [Level] => [Score], [GameID], [ItemCount] => [Min], [Max], [BurstMax] }

    public:
        clPlayerRPGameData(unsigned long int ulRecordCount) : ulRPGPlayerDataRecordCount(ulRecordCount)
        {
        }

        void setRPGPlayerDataRecordCount(unsigned long int ulRecordCount) { ulRPGPlayerDataRecordCount = ulRecordCount; }

        void generatePlayerGamePlayData(void)
        {
            while(ulRPGPlayerDataRecordCount-- > 0)
            {
                // ToDo
            }
        }
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
class clPlayerFPSGameData
{
    private:                                            // Intentionally explicit
};
//------------------------------------------------------------------------------