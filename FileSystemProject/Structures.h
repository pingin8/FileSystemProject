#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "Constants.h"

struct Cluster
{
	ushort Offset;
	ushort Next;
	ushort Prev;
	ushort Size;
	uchar Data[MAX_CLUSTER_DATA_SIZE];
};

struct FileInfo 
{
	char Name[MAX_FILENAME_LENGTH];
	uint Size;		// Count of records if dir.
	ushort Cluster; // Offset of first cluster with data.
	ushort Parent;	// Parent id.
	uint Id;		// Id = 1024 * cluster_offset + offset in cluster.
	uchar Type;
};

#endif STRUCTURES_H