//
// Created by cat on 3/29/17.
//

#pragma once
#include "Client.h"

/// Class extends "Client" class with field "cache".
/// For partial cache reallocation needed cache object
///
class AppClass : public Client {
public:
    AppClass();
    ~AppClass();

    ///
    Lru *_cache;

    /// QoS
    double _QoS;
};