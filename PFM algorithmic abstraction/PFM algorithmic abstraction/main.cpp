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

// The list of vertices unique signatures
#define V_0 0               // Initial condition, the vertex doesn't exist
#define V_1 0x00000011
#define V_2 0x00002200
#define V_3 0x00440000

const int V[ 2 ][ 4 ] =     // Number of vertices having a unique signature
{
    { V_0, V_1, V_2, V_3 },
    {                       // The list of values of D(d) = S(s) ^ S(d)
                            // assigned at compile time, GSR(G) += D(d)
        G ^ V_0,
        G ^ V_0 ^ V_1,
        G ^ V_0 ^ V_1 ^ V_2,
        G ^ V_0 ^ V_1 ^ V_2 ^ V_3
    }
};

int F1( void )
{
    int d = V[ 1 ][ 0 ] ^ V[ 1 ][ 1 ];
    
    if (( G += d ) != V[ 1 ][ 1 ]) cout << "(illegal sequence)\t";
    
    return G;
}

int F2( void )
{
    int d = V[ 1 ][ 1 ] ^ V[ 1 ][ 2 ];
    
    if (( G += d ) != V[ 1 ][ 2 ]) cout << "(illegal sequence)\t";
    
    return G;
}

int F3( void )
{
    int d = V[ 1 ][ 2 ] ^ V[ 1 ][ 3 ];
    
    if (( G += d ) != V[ 1 ][ 3 ]) cout << "(illegal sequence)\t";
    
    return G;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "PFM algorithmic abstraction\n\n";
    
    cout.flags( ios_base::left | ios_base::hex | ios_base::showbase );
    
    cout << "A vertex signatures assigned at compile time" << endl;
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
    
    G = 0;                  // GSR(G) = 0, next critical path evaluation
    
    cout << endl;
    TRACE(F1()); cout << endl;
    TRACE(F1()); cout << endl;
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
