#include "generateData.h"

unsigned long int    clPlayers::ulPlayerCount = 0UL;

//------------------------------------------------------------------------------
int main(void)
{

    unsigned long int	nTotalPlayers;

    cout << "How many players data to be generated?: ";
    cin  >> nTotalPlayers;

    while(nTotalPlayers-- > 0UL)
    {
    	clPlayers::generateOnePlayer();
    }

    cout << "Generated " << clPlayers::ulPlayerCount << " players!" << endl;
    cout << "---------------------------------" << endl << endl;

    clPlayers::dumpPlayersList();
    clPlayers::dropPlayersList();

    return 0;
}