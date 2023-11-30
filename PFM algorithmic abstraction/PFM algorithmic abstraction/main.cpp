//
//  main.cpp
//  PFM algorithmic abstraction
//
//  Created by MUC-StarChild-Mercury on 23.11.23.
//

#include <iostream>

using namespace std;

#define TRACE(x) (cout << #x << " = " << x << "\t")

int G = 0;                  // GSR(G) as global signature register

#define MAX_N_OF_CHECKPOINTS ( 0 + 3 )

// The list of vertices unique signatures
#define V_0 0               // Initial condition, the vertex doesn't exist
#define V_1 0x00000011
#define V_2 0x00002200
#define V_3 0x00440000

// Number of vertices having a unique signature
int V[ 2 ][ MAX_N_OF_CHECKPOINTS + 1 ] =
{
    { V_0, V_1, V_2, V_3 },
    {                       // The list of values of D(d) = S(s) ^ S(d)
                            // assigned at compile time, GSR(G) ^= D(d)
        G ^ V_0,
        G ^ V_0 ^ V_1,
        G ^ V_0 ^ V_1 ^ V_2,
        G ^ V_0 ^ V_1 ^ V_2 ^ V_3
    }
};

int ASSERT( int i )         // Return int is kept for debug purpose,
                            // true or false should be returned instead
{
    // Check for index is out of range, optional
    if (( i < 0 ) || ( i > MAX_N_OF_CHECKPOINTS ))
    {
        cout << "Checkpoint index is out of range\t";
        return -1;
    }
    
    if (( G ^= ( V[ 1 ][ i - 1 ] ^ V[ 1 ][ i ] )) != V[ 1 ][ i ])
    {
        cout << "(illegal sequence)\t";
        
        // According to the described approach, the safety function should be
        // triggered on the FIRST invalid state. -1 is an illegal sequence
        // marker, optional.
        G = -1;

        // TRIGGERING OF THE SAFETY FUNCTION ...
    }
    else
    {
        V[ 1 ][ i + 1 ] = G ^ V[ 1 ][ i + 1 ];  // Binding with the next node
                                                // using GSR(G) 
    }
    
    return G;
}

int F1( void ) { return ASSERT( 1 ); }
int F2( void ) { return ASSERT( 2 ); }
int F3( void ) { return ASSERT( 3 ); }

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "PFM algorithmic abstraction\n\n";
    
    cout.flags( ios_base::left | ios_base::hex | ios_base::showbase );
    
    cout << "Vertex signatures that have had updated at compile time" << endl;
    for ( int i = 0; i < 2; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            cout.width( 8 );
            cout << hex << V[ i ][ j ] << "\t";
        }
        cout << endl;
    }
    
    G = 0;                  // Next critical path evaluation, here optional
    
    cout << endl;
    TRACE(F1()); cout << endl;
    TRACE(F2()); cout << endl;
    TRACE(F3()); cout << endl;
    
    cout << endl;
    cout << "Vertex signatures that have had updated at runtime" << endl;
    for ( int i = 0; i < 2; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            cout.width( 8 );
            cout << hex << V[ i ][ j ] << "\t";
        }
        cout << endl;
    }
    
    G = 0;                  // GSR(G) = 0, next critical path evaluation
    
    cout << endl;
    TRACE(F1()); cout << endl;
    TRACE(F1()); cout << endl;
    TRACE(F1()); cout << endl;
    TRACE(F3()); cout << endl;
    TRACE(F3()); cout << endl;
    TRACE(F2()); cout << endl;
    TRACE(F3()); cout << endl;
    
    G = 0;                  // GSR(G) = 0, next critical path evaluation
    
    cout << endl;
    TRACE(F1()); cout << endl;
    TRACE(F2()); cout << endl;
    TRACE(F2()); cout << endl;
    
    G = 0;                  // GSR(G) = 0, next critical path evaluation
    
    cout << endl;
    TRACE(F3()); cout << endl;
    TRACE(F2()); cout << endl;
    TRACE(F1()); cout << endl;
    
    return 0;
}
