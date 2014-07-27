#include "stdafx.h"
#include <string>
#include "Stats.h"
#include "json/json.h"

/* 
 * File:   JsonReader.h
 * Author: Gusor
 *
 * Created on 26. heinäkuuta 2014, 22:37
 */

#ifndef JSONREADER_H
#define	JSONREADER_H

class JsonReader{
    
protected:
    Json::Value dataRoot;
    
    
public:
    JsonReader(int itemId);
    void readItemStats(Stats* championStats);
    float gold;
    
};



#endif	/* JSONREADER_H */

