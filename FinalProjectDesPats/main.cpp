//
//  main.cpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 3/28/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "game.hpp"


using namespace cap;
using namespace state;

auto main(int argc, const char * argv[]) -> int {
    game g = game::getInstance();
    
    g.loop();

    return 0;
}
