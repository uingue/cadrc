#pragma once
#include"Euler.h"


Solid* makeSolid_1genus();
Solid* makeSolid_cylinderbox(double num = 24.0);

Solid* makeSolid_1genus_sweep(double dx = 0, double dy = 0, double dz = 2);
Solid* makeSolid_2genus_sweep(double dx = 0, double dy = 0, double dz = 2);
