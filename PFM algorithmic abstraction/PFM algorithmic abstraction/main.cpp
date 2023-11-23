//
//  main.cpp
//  PFM algorithmic abstraction
//
//  Created by MUC-StarChild-Mercury on 23.11.23.
//

#include <iostream>

int G = 0;          // GSR(G) as global signature register

// The list of vertices unique signatures
#define V_0 0       // Initial condition, the vertex doesn't exist
#define V_1 0
#define V_2 0
#define V_3 0

int V[ 2 ][ 4 ] =   // Number of vertices having a unique signature
{
    { 0, 1, 2, 3 },
    {               // The list of D(d) = S(s) ^ S(d)
        0,
        0,
        0,
        0
    }
};

void F1( void )
{
//    int d = V[ 0 ][ 0 ] ^ V[ 0 ][ 1 ];
}

void F2( void )
{
    
}

void F3( void )
{
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "PFM algorithmic abstraction\n";
    
    F1();
    F2();
    F3();
    
    return 0;
}
