//
// Created by cat on 5/23/17.
//

#pragma once

enum DivisionType {
    EQUAL = 0,
    BY_QOS,
    STATISTICAL
};

enum StorageType {
    SHARED = 0,
    PARTIAL,
    DYNAMIC
};

enum FlowType {
    FFILE = 0,
    FGENERATOR
};

enum Limit{
    TIME = 0,
    REQUEST_NUMBER
};