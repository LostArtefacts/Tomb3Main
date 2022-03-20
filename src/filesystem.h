#pragma once

#include <stdbool.h>
#include <stddef.h>

bool File_IsAbsolute(const char *path);

bool File_IsRelative(const char *path);

bool File_Exists(const char *path);

const char *File_GetGameDirectory(void);

// Get the absolute path to the given file, if possible.
// Internaly all operations on files within filesystem.c
// perform this normalization, so calling this function should
// only be necessary when interacting with external libraries.
char *File_GetFullPath(const char *path);
