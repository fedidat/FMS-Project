#pragma once
#include <iostream>
#include "Block.h"

/************************************************************************
* FUNCTION																*
*	PhysicalBlock														*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Default constructor for the Physical Block. Fills the block with	*
*		zeros.															*
* SEE ALSO																*
************************************************************************/
PhysicalBlock::PhysicalBlock()
{
	BlockNr = 0;
	for (int i = 0; i < 20; i++) 
		Filler[i] = NULL;
	for (int i = 0; i < 1000; i++) 
		Data[i] = NULL;
}

//Temporary functions for the main
char* CurrentBlock::getCurData()
{
	return Buffer->Data;
}
void CurrentBlock::setCurData(string data, int num)
{
	for(unsigned int i = 0; i < data.length() ; i++)
		Buffer->Data[i]=data[i];
	Buffer->BlockNr=num;
}
