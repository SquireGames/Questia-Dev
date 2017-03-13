#ifndef DRAWLAYER_H
#define DRAWLAYER_H

enum class DrawLayer
{
    //floors, trees
    Tile_Bottom    = 0,
    //regular entities
    Entity_Regular = Tile_Bottom + 1,
    //doorways
    Tile_Top       = Entity_Regular + 1,
    //roofs
    Entity_Top     = Tile_Top + 1
	
};

#endif // DRAWLAYER_H
