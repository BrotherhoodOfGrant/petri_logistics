// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <string>
#include <string.h>
#include <vector>
#include "Windows.h"
using namespace std;

#ifndef UNICODE  
typedef std::string String;
typedef std::ostringstream Ostringstream;
#else
typedef std::wstring String;
typedef std::wostringstream Ostringstream;
#endif

#include "Petri_Net.h"
#include "AltStructsSynthesizer.h"
#include "Matrix.h"
#include "InverseTransformer.h"
#include "LbfToPrimitiveSeparator.h"
#include "SrcToLbfSeparator.h"
#include "PetriNetSerializer.h"
#include "EquivalenceChecker.h"
