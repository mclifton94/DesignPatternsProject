//
//  main.cpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 3/28/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "game.hpp"

auto main(int argc, const char * argv[]) -> int {
    cap::state::game* g = cap::state::game::getInstance();
    g->loop();

    return 0;
}