#pragma once

#include <string>
#include "user.h"

typedef struct player
{
    user_t user;
    int clientSocket;
} player_t;