/* (c) Copyright 2018, Nirav Doshi */
/* This code is licensed under MIT license. */
/* Compiles on Mac OS X: g++ generateData.cpp -std=c++11 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <random>
// #include "random.h"          // Uncomment, if you want to use the pcg in the markFraudPlayers()
#include <ctime>
#include <chrono>
#include <math.h>
using namespace std;

//------------
#define SIZE_OF_UUID    0x41
#define OFFSET         -0x02

//---
#define _DEBUG_
// #define _DEBUG_DEEP_

#define LEVELS      0x80
#define MINMAXBURST 0x03

#define MIN         0x00
#define MAX         0x01
#define MAXBURST    0x02
//---

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
class clPlayerRPGameData;

class clRPGPlayers
{
    private:                                            // Intentionally explicit
        clRPGPlayers       *ptrPrevPlayer;
        unsigned long int   ulPlayerID;
//      unsigned char       strUUID[SIZE_OF_UUID];
        unsigned int        uLevel;
        unsigned long int   ulScore;
        unsigned int        uUnitsCount;
        unsigned int        uGoldCount;
        unsigned int        uPotionCount;
        unsigned int        uFriendCount;
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
            uUnitsCount = 5;
            uGoldCount = 3;
            uPotionCount = 0;
            uFriendCount = 0;
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

        clRPGPlayers(unsigned long int ulTempPlayerID):ulPlayerID(ulTempPlayerID)
        {
            ptrPrevPlayer = ptrNextPlayer = NULL;               // This constructor is only for an object, not part of our main Dynamic Linked List (DLL)
        }

        void operator+=(const clRPGPlayers& objRightPlayer)
        {
            this->uLevel = objRightPlayer.uLevel;
            this->ulScore += objRightPlayer.ulScore;
            this->uUnitsCount += objRightPlayer.uUnitsCount;
            this->uGoldCount += objRightPlayer.uGoldCount;
            this->uPotionCount += objRightPlayer.uPotionCount;
            this->uFriendCount += objRightPlayer.uFriendCount;
            this->uInventoryItemCount += objRightPlayer.uInventoryItemCount;
            this->isFraudulentPlayer = objRightPlayer.isFraudulentPlayer;
        }

        clRPGPlayers* operator+(const clRPGPlayers *ptrRightPlayer)
        {
            this->uLevel = ptrRightPlayer->uLevel;
            this->ulScore = this->ulScore + ptrRightPlayer->ulScore;
            this->uUnitsCount = this->uUnitsCount + ptrRightPlayer->uUnitsCount;
            this->uGoldCount = this->uGoldCount + ptrRightPlayer->uGoldCount;
            this->uPotionCount = this->uPotionCount + ptrRightPlayer->uPotionCount;
            this->uFriendCount = this->uFriendCount + ptrRightPlayer->uFriendCount;
            this->uInventoryItemCount = this->uInventoryItemCount + ptrRightPlayer->uInventoryItemCount;
            this->isFraudulentPlayer = ptrRightPlayer->isFraudulentPlayer;

            return this;
        }

        clRPGPlayers* operator+=(const clRPGPlayers *ptrRightPlayer)
        {
            this->uLevel = ptrRightPlayer->uLevel;
            this->ulScore += ptrRightPlayer->ulScore;
            this->uUnitsCount += ptrRightPlayer->uUnitsCount;
            this->uGoldCount += ptrRightPlayer->uGoldCount;
            this->uPotionCount += ptrRightPlayer->uPotionCount;
            this->uFriendCount += ptrRightPlayer->uFriendCount;
            this->uInventoryItemCount += ptrRightPlayer->uInventoryItemCount;
            this->isFraudulentPlayer = ptrRightPlayer->isFraudulentPlayer;

            return this;
        }

        void operator =(const clRPGPlayers& objRightPlayer)
        {
            this->ulPlayerID = objRightPlayer.ulPlayerID;
            this->uLevel = objRightPlayer.uLevel;
            this->ulScore = objRightPlayer.ulScore;
            this->uUnitsCount = objRightPlayer.uUnitsCount;
            this->uGoldCount = objRightPlayer.uGoldCount;
            this->uPotionCount = objRightPlayer.uPotionCount;
            this->uFriendCount = objRightPlayer.uFriendCount;
            this->uInventoryItemCount = objRightPlayer.uInventoryItemCount;
            this->isFraudulentPlayer = objRightPlayer.isFraudulentPlayer;
        }

        void dumpPlayerData(ostream& refOutputfile, ostream& refOutputCSVFile)
        {
#ifdef  _DEBUG_DEEP_
            cout << "[" << hex << setfill('0') << setw(0x10) << this << "]: [" << setw(0x10) << ptrPrevPlayer << dec << "], ";  // Debug data
#endif
            refOutputfile << ulPlayerID << " 1:" << uLevel << " 2:" << ulScore << " 3:" << uUnitsCount << " 4:" \
                 << uGoldCount << " 5:" << uPotionCount << " 6:" << uFriendCount << " 7:" \
                 << uInventoryItemCount << " 8:" << isFraudulentPlayer << endl;
            refOutputCSVFile << ulPlayerID << ", " << uLevel << ", " << ulScore << ", " << uUnitsCount << ", " \
                 << uGoldCount << ", " << uPotionCount << ", " << uFriendCount << ", " \
                 << uInventoryItemCount << ", " << isFraudulentPlayer << endl;
            cout << ulPlayerID << ", " << uLevel << ", " << ulScore << ", " << uUnitsCount << ", " \
                 << uGoldCount << ", " << uPotionCount << ", " << uFriendCount << ", " \
                 << uInventoryItemCount << ", " << isFraudulentPlayer;
#ifdef  _DEBUG_DEEP_
            cout << ", [" << hex << setfill('0') << setw(0x10) << ptrNextPlayer << "]";                                                  // Debug data
#endif
            cout << dec << endl;
        }

        void updatePlayerData(unsigned int uNewLevel, unsigned long int ulNewScore, unsigned int uNewUnitsCount, unsigned int uNewGoldCount, unsigned int uNewPotionCount, unsigned int uNewFriendCount, unsigned int uNewInventoryItemCount)
        {
            uLevel = uNewLevel;
            ulScore = ulNewScore;                           // TODO: If the score > max. score for level, level-up
            uUnitsCount = uNewUnitsCount;
            uGoldCount = uNewGoldCount;
            uPotionCount = uNewPotionCount;
            uFriendCount = uNewFriendCount;
            uInventoryItemCount = uNewInventoryItemCount;
        }

        clRPGPlayers* findPlayer(unsigned long int tempPlayerID)
        {
            clRPGPlayers    *ptrTempPlayer = ptrRootPlayer;

            while(ptrTempPlayer != NULL)
            {
                if(ptrTempPlayer->ulPlayerID == tempPlayerID)
                {
#ifdef _DEBUG_DEEP_
                    cout << endl << "Player found: [" << ptrTempPlayer << "]";
#endif
                    break;
                }
                ptrTempPlayer = ptrTempPlayer->ptrNextPlayer;
            }

            return ptrTempPlayer;
        }

        unsigned long int getPlayerID(void)                             { return ulPlayerID; }
        unsigned int getPlayerLevel(void)                               { return uLevel; }
        unsigned long int getPlayerScore(void)                          { return ulScore; }
        unsigned int getUnitsCount(void)                                { return uUnitsCount; }
        unsigned int getGoldCount(void)                                 { return uGoldCount; }
        unsigned int getPotionCount(void)                               { return uPotionCount; }
        unsigned int getFriendcount(void)                               { return uFriendCount; }
        unsigned int getInventoryItemCount(void)                        { return uInventoryItemCount; }
        bool isThisAFraudulentPlayer(void)                              { return isFraudulentPlayer; }
        clRPGPlayers *getPreviousPlayer(void)                           { return ptrPrevPlayer; }
        clRPGPlayers *getNextPlayer(void)                               { return ptrNextPlayer; }

        void setPlayerLevel(unsigned int uNewLevel)                     { uLevel = uNewLevel; }
        void setPlayerScore(unsigned long int ulNewScore)               { ulScore = ulNewScore; }
        void setUnitsCount(unsigned int uNewUnitsCount)                 { uUnitsCount = uNewUnitsCount; }
        void setGoldCount(unsigned int uNewGoldCount)                   { uGoldCount = uNewGoldCount; }
        void setPotionCount(unsigned int uNewPotionCount)               { uPotionCount = uNewPotionCount; }
        void setFriendCount(unsigned int uNewFriendCount)               { uFriendCount = uNewFriendCount; }
        void setInventoryItemCount(unsigned int uNewInventoryItemCount) { uInventoryItemCount = uNewInventoryItemCount; }

        static void generateOnePlayer(void)
        {
            ptrNewPlayer = new clRPGPlayers;
            if(ptrNewPlayer == NULL)
            {
                cout << endl << "ERROR: OOM or some other exception. Aborting... (from clRPGPlayers)" << endl;
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
            uniform_int_distribution<unsigned long int> ulDistro(0, (clRPGPlayers::ulRPGPlayerCount - 1));

            for(unsigned long int ulItr = 0; ulItr < static_cast<unsigned long int>((clRPGPlayers::ulRPGPlayerCount * nPercentage)/100); ulItr++)
            {
                vecFraudPlayers.push_back(ulDistro(random));
            }

/*
#ifdef  _DEBUG_DEEP_
            for(vector<unsigned long int>::iterator vItr = vecFraudPlayers.begin(); vItr != vecFraudPlayers.end(); ++vItr)
            {
                cout << *vItr << " .. ";
            }
            cout << endl;
#endif
*/

            sort(vecFraudPlayers.begin(), vecFraudPlayers.end());

/*
#ifdef  _DEBUG_DEEP_
            for(vector<unsigned long int>::iterator vItr = vecFraudPlayers.begin(); vItr != vecFraudPlayers.end(); ++vItr)
            {
                cout << *vItr << " .. ";
            }
            cout << endl;
#endif
*/
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
                        --vItr;                                                 // Check done. Step back, allow the for() to increment
                        ptrTempPlayer = ptrTempPlayer->ptrNextPlayer;           // Next player

                        break;
                    }
                    else
                    {
                        ptrTempPlayer = ptrTempPlayer->ptrNextPlayer;           // Find the next player
                    }
                }
            }
        }

        static void dumpPlayersList(void)
        {
            clRPGPlayers      *ptrTempPlayer = ptrRootPlayer;

#ifdef  _DEBUG_DEEP_
            cout << "[CurrentLocation]: [ptrPrevPlayer], ";
#endif
            cout << "PlayerID, Level, Score, Units, Gold, Potions, Friends, InventoryItems, isFraudulentPlayer";
#ifdef  _DEBUG_DEEP_
            cout << ", [ptrNextPlayer]";
#endif
            cout << endl;
            while(ptrTempPlayer != NULL)
            {
#ifdef  _DEBUG_DEEP_
                cout << "[" << hex << setfill('0') << setw(0x10) << ptrTempPlayer << "]: [" << setw(0x10) << ptrTempPlayer->ptrPrevPlayer << dec << "], ";  // Debug data
#endif
                cout << ptrTempPlayer->ulPlayerID << ", " << ptrTempPlayer->uLevel << ", " << ptrTempPlayer->ulScore << ", " << ptrTempPlayer->uUnitsCount << ", " \
                     << ptrTempPlayer->uGoldCount << ", " << ptrTempPlayer->uPotionCount << ", " << ptrTempPlayer->uFriendCount << ", " \
                     << ptrTempPlayer->uInventoryItemCount << ", " << ptrTempPlayer->isFraudulentPlayer;
#ifdef  _DEBUG_DEEP_
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
// Will be a singleton class
class clPlayerRPGameData
{
    private:                                            // Intentionally explicit
        unsigned long int           ulRPGPlayerDataRecordCount;
        unsigned long int           ulScores[LEVELS][MINMAXBURST];

        clPlayerRPGameData(unsigned long int ulRecordCount = 1000UL):ulRPGPlayerDataRecordCount(ulRecordCount)
        {
            if(ulRecordCount > 0UL)
            {
                generateGameDesignData();
            }
        }
        clPlayerRPGameData(const clPlayerRPGameData&) = delete;
        clPlayerRPGameData& operator=(const clPlayerRPGameData&) = delete;

    public:
        static clPlayerRPGameData* getInstance(unsigned long int ulRecordCount = 1000UL)
        {
            static clPlayerRPGameData  objTheOnlyInstance(ulRecordCount);

            return &objTheOnlyInstance;
        }

//      void setRPGPlayerDataRecordCount(unsigned long int ulRecordCount = 1000UL) { ulRPGPlayerDataRecordCount = ulRecordCount; }

        unsigned long int getMinScore(unsigned int uPlayerLevel)        { return ulScores[uPlayerLevel][MIN]; }
        unsigned long int getMaxScore(unsigned int uPlayerLevel)        { return ulScores[uPlayerLevel][MAX]; }
        unsigned long int getBurstMaxScore(unsigned int uPlayerLevel)   { return ulScores[uPlayerLevel][MAXBURST]; }

        void generateGameDesignData(void)
        {
            mt19937         randomSeed0(chrono::high_resolution_clock::now().time_since_epoch().count());
            mt19937         randomSeed1(chrono::high_resolution_clock::now().time_since_epoch().count());
            mt19937         randomSeed2(chrono::high_resolution_clock::now().time_since_epoch().count());

#ifdef _DEBUG_DEEP_
            cout << endl << endl;
#endif
            for(int nItr = 0x01; nItr <= LEVELS; nItr++)
            {
                {
                    uniform_int_distribution<unsigned long int> ulMinScores(0, (nItr * 10));
                    uniform_int_distribution<unsigned long int> ulMaxScores((nItr * 100), (nItr * 200));
                    uniform_int_distribution<unsigned long int> ulBurstScores((nItr * 201), (nItr * 800));

                    ulScores[nItr - 1][MIN] = ulMinScores(randomSeed0);
                    ulScores[nItr - 1][MAX] = ulMaxScores(randomSeed1);
                    ulScores[nItr - 1][MAXBURST] = ulBurstScores(randomSeed2);
                }
#ifdef _DEBUG_DEEP_
                cout << nItr << ". => " << ulScores[nItr][MIN] << " .. " << ulScores[nItr][MAX] << " .. " << ulScores[nItr][MAXBURST] << endl;
#endif
            }
        }

        bool checkLevelUp(clRPGPlayers *ptrCurrentPlayer)
        {
            bool    checkResult = false;
//          if(ptrCurrentPlayer->isThisAFraudulentPlayer() == false)
//          {
                if(ptrCurrentPlayer->getPlayerScore() > getMaxScore(ptrCurrentPlayer->getPlayerLevel()))
                {
                    checkResult = true;
                }
//          }

            return checkResult;
        }

        void generatePlayerGamePlayData(void)
        {
            clRPGPlayers   *ptrTempPlayer = NULL;
            unsigned int    uPlayerLevel = 1;
            unsigned long int tempPlayerID = 0UL;

            ofstream         fOutputFile("outputFile", ios::out | ios::trunc);
            ofstream         fOutputCSVFile("outputFile.csv", ios::out | ios::trunc);

            mt19937         randomSeed0(chrono::high_resolution_clock::now().time_since_epoch().count());
            mt19937         randomSeed1(chrono::high_resolution_clock::now().time_since_epoch().count());
            mt19937         randomSeed2(chrono::high_resolution_clock::now().time_since_epoch().count());
            mt19937         randomSeed3(chrono::high_resolution_clock::now().time_since_epoch().count());

            uniform_int_distribution<unsigned long int> ulRandomPlayer(0, (clRPGPlayers::ulRPGPlayerCount - 1));

            discrete_distribution<unsigned int> uUnits({10, 12, 21, 18, 15, 12, 9, 3});         // Weights for: {-2, -1, 0, 1, 2, 3, 4, 5}
            uniform_int_distribution<unsigned int> uBurstUnits(7, 20);
            discrete_distribution<unsigned int> uGold({13, 17, 21, 20, 17, 9, 3});              // Weights for {-2, -1, 0, 1, 2, 3, 4}
            uniform_int_distribution<unsigned int> uBurstGold(6, 400);
            discrete_distribution<unsigned int> uPotions({15, 17, 25, 18, 12, 10, 3});          // Weights for {-2, -1, 0, 1, 2, 3, 4}
            uniform_int_distribution<unsigned int> uBurstPotions(6, 50);
            uniform_int_distribution<unsigned int> uFriends(0, 25);
            discrete_distribution<unsigned int> uInventoryItems({15, 17, 25, 18, 12, 10, 3});   // Weights for {-2, -1, 0, 1, 2, 3, 4}
            uniform_int_distribution<unsigned int> uBurstInventoryItems(6, 25);

            cout << "[NOTE: Starting player gameplay data dump...]" << endl << endl;
#ifdef  _DEBUG_DEEP_
            cout << "[CurrentLocation]: [ptrPrevPlayer], ";
#endif
            fOutputCSVFile << "PlayerID, Level, Score, Units, Gold, Potions, Friends, InventoryItems, isFraudulentPlayer";
            cout << "PlayerID, Level, Score, Units, Gold, Potions, Friends, InventoryItems, isFraudulentPlayer";
#ifdef  _DEBUG_DEEP_
            cout << ", [ptrNextPlayer]";
#endif
            cout << endl;

            while(ulRPGPlayerDataRecordCount-- > 0)
            {
                tempPlayerID = (10000UL + ulRandomPlayer(randomSeed0));
                ptrTempPlayer = ptrRootPlayer->findPlayer(tempPlayerID);

                if(ptrTempPlayer == NULL)
                {
                    cout << "ERROR: Unexpected issue. No such player found: " << tempPlayerID << endl;
                    continue;
                }

                uPlayerLevel = ptrTempPlayer->getPlayerLevel();

                {
                    clRPGPlayers objTempPlayer(ptrTempPlayer->getPlayerID());
                    objTempPlayer = *ptrTempPlayer;

                    if(ptrTempPlayer->isThisAFraudulentPlayer() == false)
                    {
                        uniform_int_distribution<unsigned long int> ulRandomPlayerScores(ulScores[uPlayerLevel][MIN], ulScores[uPlayerLevel][MAX]);

                        objTempPlayer.setPlayerScore(ulRandomPlayerScores(randomSeed1));
                        objTempPlayer.setUnitsCount(uUnits(randomSeed2));
                        objTempPlayer.setGoldCount(uGold(randomSeed3));
                        objTempPlayer.setPotionCount(uPotions(randomSeed1));
                        objTempPlayer.setFriendCount(uFriends(randomSeed2));
                        objTempPlayer.setInventoryItemCount(uInventoryItems(randomSeed3));
                    }
                    else
                    {
                        uniform_int_distribution<unsigned long int> ulRandomPlayerScores((ulScores[uPlayerLevel][MAX] + 1), ulScores[uPlayerLevel][MAXBURST]);

                        objTempPlayer.setUnitsCount(uBurstUnits(randomSeed1));
                        objTempPlayer.setPlayerScore(ulRandomPlayerScores(randomSeed2));
                        objTempPlayer.setGoldCount(uBurstGold(randomSeed3));
                        objTempPlayer.setPotionCount(uBurstPotions(randomSeed1));
                        objTempPlayer.setFriendCount(uFriends(randomSeed2));
                        objTempPlayer.setInventoryItemCount(uBurstInventoryItems(randomSeed3));
                    }

#ifdef _DEBUG_DEEP_
                    cout << "==> Before: ";
                    ptrTempPlayer->dumpPlayerData();
#endif

//                  ptrTempPlayer += &objTempPlayer;
//                  ptrTempPlayer = ptrTempPlayer + &objTempPlayer;

                    ptrTempPlayer->setPlayerLevel(objTempPlayer.getPlayerLevel());
                    ptrTempPlayer->setPlayerScore(ptrTempPlayer->getPlayerScore() + objTempPlayer.getPlayerScore());
                    ptrTempPlayer->setUnitsCount(ptrTempPlayer->getUnitsCount() + objTempPlayer.getUnitsCount() - OFFSET);
                    ptrTempPlayer->setGoldCount(ptrTempPlayer->getGoldCount() + objTempPlayer.getGoldCount() - OFFSET);
                    ptrTempPlayer->setPotionCount(ptrTempPlayer->getPotionCount() + objTempPlayer.getPotionCount() - OFFSET);
                    ptrTempPlayer->setFriendCount(ptrTempPlayer->getFriendcount() + objTempPlayer.getFriendcount());
                    ptrTempPlayer->setInventoryItemCount(ptrTempPlayer->getInventoryItemCount() + objTempPlayer.getInventoryItemCount() - OFFSET);

#ifdef  _DEBUG_DEEP_
                    cout << "==> After: ";
                    ptrTempPlayer->dumpPlayerData();
#endif
                    if(checkLevelUp(ptrTempPlayer) == true)
                    {
#ifdef _DEBUG_DEEP_
                        cout << "==> Leveling up: ";
#endif
                        if(ptrTempPlayer->getPlayerLevel() < LEVELS)
                        {
                            ptrTempPlayer->setPlayerLevel(ptrTempPlayer->getPlayerLevel() + 1);
                        }
                    }
                    ptrTempPlayer->dumpPlayerData(fOutputFile, fOutputCSVFile);
                }
            }

            fOutputFile.close();
            fOutputCSVFile.close();
        }
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
class clPlayerFPSGameData
{
    private:                                            // Intentionally explicit
};
//------------------------------------------------------------------------------
