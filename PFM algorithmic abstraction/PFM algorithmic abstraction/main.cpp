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

// Number of vertices having a unique signature.
// Since V[1][n] changes at runtime, it should not be a constant type.
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

bool ASSERT( int i )
{
    if (( G ^= ( V[ 1 ][ i - 1 ] ^ V[ 1 ][ i ] )) != V[ 1 ][ i ])
    {
        cout << "(illegal sequence)\t";
        
        // According to the described approach, the safety function should be
        // triggered on the FIRST invalid state. -1 is an illegal sequence
        // marker, optional.
        G = -1;
        
        // TRIGGERING OF THE SAFETY FUNCTION ...
        
        // Never be reached, or to be used concept dependent,
        // left for debugging purpose only.
        return false;
    }
    else
    {
        // Binding with the next node using GSR(G)
        if ( i + 1 <= MAX_N_OF_CHECKPOINTS ) V[ 1 ][ i + 1 ] ^= G;
    }
    
    return true;
}

// The ASSERT(n) n parameter must match the sequence of calls. Otherwise, it is
// interpreted as a programming error (or additional index checking is
// required).
int F1( void ) { return ASSERT( 1 ); }
int F2( void ) { return ASSERT( 2 ); }
int F3( void ) { return ASSERT( 3 ); }

void TRACE_VSTAT( void )
{
    cout << endl;
    cout << "Vertex signatures that have been updated at runtime" << endl;
    for ( int i = 0; i < 2; i++ ) {
        for ( int j = 0; j <= MAX_N_OF_CHECKPOINTS; j++ ) {
            cout.width( 8 );
            cout << hex << V[ i ][ j ] << "\t";
        }
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "PFM algorithmic abstraction\n\n";
    
    cout.flags( ios_base::left | ios_base::hex | ios_base::showbase );
    
    cout << "Vertex signatures that have been updated at compile time" << endl;
    for ( int i = 0; i < 2; i++ ) {
        for ( int j = 0; j <= MAX_N_OF_CHECKPOINTS; j++ ) {
            cout.width( 8 );
            cout << hex << V[ i ][ j ] << "\t";
        }
        cout << endl;
    }
    
    // The GSR(R) register must be reset before the critical path is taken.
    
    G = 0;                  // Next critical path evaluation, here optional
    
    cout << endl;
    TRACE(F1()); cout << endl;
    TRACE(F2()); cout << endl;
    TRACE(F3()); cout << endl;
    TRACE_VSTAT();
    
    G = 0;                  // GSR(G) = 0, next critical path evaluation
    
    cout << endl;
    TRACE(F1()); cout << endl;
    TRACE(F1()); cout << endl;
    TRACE(F1()); cout << endl;
    TRACE(F3()); cout << endl;
    TRACE(F3()); cout << endl;
    TRACE(F2()); cout << endl;
    TRACE(F3()); cout << endl;
    TRACE_VSTAT();
    
    G = 0;                  // GSR(G) = 0, next critical path evaluation
    
    cout << endl;
    TRACE(F1()); cout << endl;
    TRACE(F2()); cout << endl;
    TRACE(F2()); cout << endl;
    TRACE_VSTAT();
    
    G = 0;                  // GSR(G) = 0, next critical path evaluation
    
    cout << endl;
    TRACE(F3()); cout << endl;
    TRACE(F2()); cout << endl;
    TRACE(F1()); cout << endl;
    TRACE(F2()); cout << endl;
    TRACE_VSTAT();
    
    G = 0;                  // Next critical path evaluation, here optional
    
    cout << endl;
    TRACE(F1()); cout << endl;
    TRACE(F2()); cout << endl;
    TRACE(F3()); cout << endl;
    TRACE(F1()); cout << endl;
    TRACE_VSTAT();
    
    return 0;
}
