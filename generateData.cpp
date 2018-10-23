#include "generateData.h"

unsigned long int   clRPGPlayers::ulRPGPlayerCount = 0UL;
unsigned long int   clRPGPlayers::ulRPGFraudPlayerCount = 0UL;

//------------------------------------------------------------------------------
int main(void)
{
    unsigned long int	nTotalPlayers;

    cout << "--- How many RPG players data to be generated?: ";
    cin  >> nTotalPlayers;

    while(nTotalPlayers-- > 0UL)
    {
    	clRPGPlayers::generateOnePlayer();
    }

    cout << endl << "--- Generated " << clRPGPlayers::ulRPGPlayerCount << " RPG players..." << endl;
    cout << "--- Fraud Player Count: " << clRPGPlayers::ulRPGFraudPlayerCount << "..." << endl;

    cout << endl << "--- Dumping players list..." << endl;
    clRPGPlayers::dumpPlayersList();

    cout << endl << "--- Cleaning up players list..." << endl;
    clRPGPlayers::dropPlayersList();

    cout << endl << "--- Done. Bye." << endl;

    return 0;
}