//
//  gameStates.hpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once

#include <iostream>

#include "gameWindow.hpp"

using namespace cap;
using namespace graphics;

namespace cap { namespace state {

    class gameStates {
    public:
        virtual void loop() = 0;
    };

}}