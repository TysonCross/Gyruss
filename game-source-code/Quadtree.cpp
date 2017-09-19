/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    19/9/17
/// \brief   Implementation of a  quadtree data structure for storing objects
///
/// Similar to a binary tree, buth with four children instead of two.
/// Splits up objects into a structure based on their position on screen
/// for iterating through for collision detection.
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include <
#include "Quadtree.hpp"



Quadtree::Quadtree(int level, sf::Rect bounds) : _level{level},
                                                 _bounds{bounds}
{
    _nodes.reserve(4);
}

void Quadtree::clear()
{
    _objects.clear();
    for (auto i = 0; i< _nodes.size(); i++)
    {
        if (_nodes.at(i) != NULL)
        {
            _nodes.clear();
            _nodes.at(i) = NULL;
        }
    }
}

void Quadtree::insert(sf::Rect rectangle)
{
    if (_nodes[0] != 0)
    {
        int index = getIndex(rectangle);

        if (index != -1)
        {
            _nodes[index].insert(rectangle);
            return;
        }
    }

    _objects.push_back(rectangle);

    if ((_objects.size() > _max_objects) && (_level < _max_levels))
    {
        if (_nodes[0] == 0)
        {
            split();
        }
    }

    auto i = 0;
    while(i < _objects.size())
    {
        int index = getIndex(_objects.get(i));
        if (index != -1)
        {
            nodes[index].insert(_objects.remove(i));
        }
    }

std::vector<Entity> Quadtree::retrieve(std::vector<Entity> returnList,
                                       sf::Rect rect)
{

}

void Quadtree::split()
{
    auto subWidth = int(_bounds.width/2);
    auto subHeight = int(_bounds.height/2);
    auto x = int(_bounds.left);
    auto y = int(_bounds.top);

    nodes[0] = new Quadtree(level+1, new sf::Rect{x + subWidth, y, subWidth, subHeight});
    nodes[1] = new Quadtree(level+1, new sf::Rect{x, y, subWidth, subHeight});
    nodes[2] = new Quadtree(level+1, new sf::Rect{x, y + subHeight, subWidth, subHeight});
    nodes[3] = new Quadtree(level+1, new sf::Rect{x + subWidth, y + subHeight, subWidth, subHeight});
}
}

int Quadtree::getIndex(sf::Rect rectangle)
{
    // -1 means object cannot fit inside child node, so is part of parent node.
    auto index = -1;
    auto verticalMidpoint = _bounds.left + (_bounds.width/2);
    auto horizontalMidpoint = _bounds.top + (_bounds.height/2);

    // Object fits in top quadrants
    bool topQuadrant = ((rectangle.top < horizontalMidpoint) && (rectangle.top + rectangle.height < horizontalMidpoint));
    // Object fits in the bottom quadrants
    bool bottomQuadrant = (rectangle.top > horizontalMidpoint);

    // Object fits in left quadrants
    if ((rectangle.left < verticalMidpoint) && (rectangle.left +rectangle.width < verticalMidpoint))
    {
        if (topQuadrant)
        {
            index = 1;
        }
        else if (bottomQuadrant)
        {
            index = 2;
        }
    }

    // Object fits in the right quadrants
    else if (rectangle.left > verticalMidpoint)
    {
        if (topQuadrant)
        {
            index = 0;
        }
        else if (bottomQuadrant)
        {
            index = 3;
        }
    }
    return index;
}


//const int _max_objects = 10;
//const int _max_depth = 5;
//int _level;
//std::List<Entity> _objects;
//sf::Rect _bounds;
//std::vector<Quadtree> _nodes;