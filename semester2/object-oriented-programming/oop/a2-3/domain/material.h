#pragma once
#include "date.h"

typedef struct {
    char * name, * supplier;
    int quantity;
    Date expirationDate;
} Material;
