/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    19/9/17
/// \brief   A quadtree data structure for storing objects
///
/// Similar to a binary tree, buth with four children instead of two.
/// Splits up objects into a structure based on their position on screen
/// for iterating through for collision detection.
///
/// Adapted from Steven Lambert https://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374
/////////////////////////////////////////////////////////////////////


#ifndef PROJECT_QUADTREE_HPP
#define PROJECT_QUADTREE_HPP

#include <SFML/Graphics/Rect.hpp>
#include "Entity.hpp"
#include <list>

class Quadtree
{
public:
    Quadtree(int level, sf::Rect bounds);
    void clear();
    void insert(sf::Rect rect);
    std::vector<Entity> retrieve(std::vector<Entity> returnList, sf::Rect rect);

private:
    void split();
    int getIndex(sf::Rect);

    const int _max_objects = 10;
    const int _max_levels = 5;

    int _level;
    std::list<Entity> _objects;
    sf::Rect _bounds;
    std::vector<Quadtree> _nodes;
};

#endif //PROJECT_QUADTREE_HPP
