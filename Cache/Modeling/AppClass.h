//
// Created by cat on 3/29/17.
//

#pragma once
#include "Client.h"


class AppClass : public Client {
public:
    AppClass(ByteSize capacity);
    ~AppClass();

    ///
    Lru _cache;
};