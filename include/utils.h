#ifndef WIIU_SHELL_UTILS_H
#define WIIU_SHELL_UTILS_H

char *Utils_Basename(const char *filename);
void Utils_GetSizeString(char *string, uint32_t size);
void Utils_SetMax(int *set, int value, int max);
void Utils_SetMin(int *set, int value, int min);
void Utils_AppendArr(char subject[], const char insert[], int pos);

#endif