//
//  Util.h
//  GL4Demo
//
//  Created by Saburo Okita on 16/12/13.
//  Copyright (c) 2013 Saburo Okita. All rights reserved.
//

#ifndef __GL4Demo__Util__
#define __GL4Demo__Util__

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

std::string& rtrim( std::string& str );

void print( glm::vec3 vector );

void print( glm::mat4 matrix );
void print( glm::mat3 matrix );

#endif /* defined(__GL4Demo__Util__) */
