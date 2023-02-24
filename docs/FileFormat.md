# .kuben File Format

Kuben uses a special file format with the ending ".kuben", and is laid out very linearly. This is the layout:

```
example.kuben

Header
│
Box
│
Box
```

## Header

| Field No. | Length (bytes) | Field | Description |
| --- | --- | --- | --- |
| 1   | 4   | Magic number | The magic number of the .kuben file (KU 0x17 0x01) |
| 2   | 1   | Number of boxes | The number of boxes in the program |

## Box

| Field No. | Length (bytes) | Field | Description |
| --- | --- | --- | --- |
| 1 in box | 1   | Identifier | The identifier of the box (e.g. 0 = first box, 1 = second, e.t.c) |
| 2 in box | 4		 | Frame			| The frame in which the box lies (e.g. 0 = first frame, 1 = second, e.t.c)
| 3 in box | 4   | X coordinate | X coordinate of box (in pixels) offset by image |
| 4 in box | 4   | Y coordinate | Y coordinate of box (in pixels) offset by image |
| 5 in box | 4   | Width of box | Width of box (in pixels) |
| 6 in box | 4   | Height of box | Height of box (in pixels) |
| 7 in box | 16   | Colour | The colour of the box (arranged RGBA8888) |

## Things to take not of

- Because the number of boxes are 1 byte long, only 256 total boxes can be made
- There can be a maximum of  4,294,967,295 frames in the program. (unsigned int)
- Dimensions of the box (X,Y,W,H) are stored in *signed int*s (4 bytes long, negative and positive)
- Alpha channel not used in Kuben rendering

## Loading data from .kuben files

Loading data from a .kuben file is simple; here's an example written in C:

```
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Datatypes found in the file
typedef struct KBN_Header {
	uint8_t magicNum[4];
	uint8_t numBoxes;
} __attribute__((packed)) KBN_Header;

typedef struct KBN_Box {
	uint8_t indentifier;
	uint32_t framePos;
	
	// Box dimensions
	int x;
	int y;
	int w;
	int h;
	
	// Box colours
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} __attribute__((packed)) KBN_Box;

// Generic rect function
typedef struct Rect {
	int x;
	int y;
	int w;
	int h;
} Rect;

void LoadData(char* saveFilename, Rect* rects[200]) {
	FILE* file = fopen(saveFilename, "rb");

	fseek(file, 0l, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0l, SEEK_SET);
	
	char fileBuf[fileSize];
	int locationInFile = 0;
	fread(fileBuf, sizeof(char), fileSize, file);

	if (fileSize <= 0) {
		fprintf(stderr, "Error: The file \"%s\" doesn't exist", saveFilename);
		return;
	}

	KBN_Header header;
	memcpy(&header, fileBuf + locationInFile, sizeof(KBN_Header));
	locationInFile += sizeof(KBN_Header);

	if (
		!(header.magicNum[0] == 'K' 
		&& header.magicNum[1] == 'U'
		&& header.magicNum[2] == 0x17
		&& header.magicNum[3] == 0x1)
	) {
		fprintf(stderr, "Error: The file %s is not a .kuben file", saveFilename);
		return;
	}
	
	
	for (int j = 0; j < header.numBoxes; j++) {
		KBN_Box box;
		memset(&box, 0, sizeof(KBN_Box));
		memcpy(&box, fileBuf + locationInFile, sizeof(KBN_Box));

		rects[j] = malloc(sizeof(Rect));
		Rect* tempRect = &(Rect) {
			box.x,
			box.y,
			box.w,
			box.h
		};

		memcpy(rects[j], tempRect, sizeof(Rect));
		
		locationInFile += sizeof(KBN_Box);
	}
}
```
