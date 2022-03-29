#ifndef __PIRAMIDE_H__
#define __PIRAMIDE_H__

/*!
    This is the main function that describe the points of the pyramid. 
    First, we start by drawing the base, and then we go from the base to the top, level by level.
    
    In each level, we make the alfa vary between 0 and 2*pi.
    
    And the levels distance themselves from each other h.
*/
void drawPyramid(float radius, float height, int slices, float stacks, std::string nameFile);

#endif // __PIRAMIDE_H__
