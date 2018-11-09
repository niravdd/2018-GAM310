/* (c) Copyright 2018, Nirav Doshi */
/* This code is licensed under MIT license. */

#include "generateData.h"


clPlayerRPGameData  *clPlayerRPGameData::ptrSingleInstance = NULL;
unsigned long int    clRPGPlayers::ulRPGPlayerCount = 0UL;
unsigned long int    clRPGPlayers::ulRPGFraudPlayerCount = 0UL;

//------------------------------------------------------------------------------
int main(void)
{
    unsigned long int	ulTotalPlayers;
    unsigned short      usFraudPercentage;

    cout << "--- How many RPG players data to be generated?: ";
    cin  >> ulTotalPlayers;

    cout << "--- Maximum percentage of fraudulent data to be generated? (0 to 100): ";
    cin  >> usFraudPercentage;

    while(ulTotalPlayers-- > 0UL)
    {
    	clRPGPlayers::generateOnePlayer();
    }

    cout << endl << "--- Generated " << clRPGPlayers::ulRPGPlayerCount << " RPG players..." << endl;
    clRPGPlayers::markFraudPlayers(usFraudPercentage);
    cout << "--- Fraud Player Count: " << clRPGPlayers::ulRPGFraudPlayerCount << "..." << endl;

    cout << endl << "--- Dumping players list..." << endl;
    clRPGPlayers::dumpPlayersList();

    cout << endl << "--- Generated " << clRPGPlayers::ulRPGPlayerCount << " RPG players..." << endl;
    cout << "--- Fraud Player Count: " << clRPGPlayers::ulRPGFraudPlayerCount << "(" << fixed << setprecision(2) << static_cast<float>((clRPGPlayers::ulRPGFraudPlayerCount * 100.00f)/clRPGPlayers::ulRPGPlayerCount) << "%)..." << dec << endl;

    clPlayerRPGameData *ptrPlayerRPGameData = clPlayerRPGameData::getInstance(10UL);
    ptrPlayerRPGameData->generatePlayerGamePlayData();

    cout << endl << "--- Cleaning up players list..." << endl;
    clRPGPlayers::dropPlayersList();

    cout << endl << "--- Done. Bye." << endl;

    return 0;
}
