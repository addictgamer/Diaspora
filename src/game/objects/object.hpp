/* Copyright Ciprian Ilies */

#pragma once

/*
 * Basically, an object is just a sprite and properties associated with that sprite to constitute an object, be it terrain, a creature, or some item in the world.
 * Now then, objects should be fully programmable. How will this be done? I propose that it all be done in C++.
 * I mean, objects should be programmed in c++. Modules should give base classes, and then the user takes these base classes and extends/configures them as they see fit to create the game that they want.
 * So, here's the base classes I will provide for now:
	 * Terrain. Terrain will have a sprite and then various properties. It's basically the space itself. Now how do I handle layered terrain? I mean...like...a wall and the floor it's on? Hmm. Also, give it functionality to tie into the rule system in use, whatever it may be. The rule system is just the set of loaded modules, after all.
	 * Entities (the player, NPCs, creatures, etc). Sprite, properties, controllable, AI, actions...etc. Should tie into the rule system.
	 * Objects/items. A sword laying on the ground. A door. A table. A pot.
	 * What category would plants/trees fall under? I want to say entities.
*/

/*
 * The base class of all base classes.
 * So for now, let's keep it simple and hardcoded. Later, we can extrapolate, abstract, decentralize, and modularate everything -- and make everything data driven where that's best.
 * For now, objects are going to need...what's it called...a composite sprite? That is to say, their sprite is made up of other sprites? Yes, I think that's what it's called.
 */
class Object
{
public:
	Object() { }
	~Object() { }
};
