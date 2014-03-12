//
//  Util.cpp
//  GL4Demo
//
//  Created by Saburo Okita on 16/12/13.
//  Copyright (c) 2013 Saburo Okita. All rights reserved.
//

#include "Util.hpp"
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace std;

string& rtrim( string& s ) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

void print( glm::vec3 vector ) {
    cout << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")" << endl;
}

void print( glm::mat4 matrix ) {
    for( int j = 0; j < 4; j++ ) {
        for( int i = 0; i < 4; i++ )
            printf( "%+02.2f ", matrix[i][j] );
        printf( "\n" );
    }
}

void print( glm::mat3 matrix ) {
    for( int j = 0; j < 3; j++ ) {
        for( int i = 0; i < 3; i++ )
            printf( "%02.2f ", matrix[i][j] );
        printf( "\n" );
    }
}