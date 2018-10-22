#include "generateData.h"

unsigned long int    clPlayers::ulPlayerCount = 0UL;

//------------------------------------------------------------------------------
int main(void)
{
    unsigned long int	nTotalPlayers;

    cout << "--- How many players data to be generated?: ";
    cin  >> nTotalPlayers;

    while(nTotalPlayers-- > 0UL)
    {
    	clPlayers::generateOnePlayer();
    }

    cout << "--- Generated " << clPlayers::ulPlayerCount << " players!" << endl << endl;

    cout << endl << "--- Dumping Player List" << endl;
    clPlayers::dumpPlayersList();

    cout << endl << "--- Cleaning up player's list" << endl;
    clPlayers::dropPlayersList();
    cout << endl << "--- Done. Bye."

    return 0;
}