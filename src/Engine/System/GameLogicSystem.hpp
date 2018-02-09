#pragma once
#ifndef _GAME_LOGIC_SYSTEM_HPP_
#define _GAME_LOGIC_SYSTEM_HPP_

#include "System.hpp"

class GameLogicSystem : public System {

    public:

    constexpr static Type type = GAMELOGIC;

    public:

    GameLogicSystem(std::vector<Component *> & components);

};

#endif