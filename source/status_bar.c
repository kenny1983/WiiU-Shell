#include <time.h>
#include <stdbool.h>
#include <coreinit/time.h>

#include "common.h"
#include "SDL_helper.h"
#include "status_bar.h"
#include "textures.h"
#include "input_helper.h"

static char *Clock_GetCurrentTime(void)
{
	static char buffer[10];

	OSCalendarTime calTime;
	OSTicksToCalendarTime(OSGetTime(), &calTime);
	int hours = (calTime.tm_hour);
	int minutes = calTime.tm_min;
	
	bool amOrPm = false;
	
	if (hours < 12)
		amOrPm = true;
	if (hours == 0)
		hours = 12;
	else if (hours > 12)
		hours = hours - 12;

	if ((hours >= 1) && (hours < 10))
		snprintf(buffer, 10, "%2i:%02i %s", hours, minutes, amOrPm ? "AM" : "PM");
	else
		snprintf(buffer, 10, "%2i:%02i %s", hours, minutes, amOrPm ? "AM" : "PM");

	return buffer;
}

static void StatusBar_GetBatteryStatus(int x, int y)
{
	int percent = 50;
	int width = 0;
	char buf[5];

	switch(Input_BatteryStatus())
	{
		case 0:
			SDL_DrawImage(RENDERER, battery_50_charging, x, 3);
			percent = -1;
			break;
		case 1:
			SDL_DrawImage(RENDERER, battery_low, x, 3);
			percent = 0;
			break;
		case 2:
			SDL_DrawImage(RENDERER, battery_20, x, 3);
			percent = 20;
			break;
		case 3:
			SDL_DrawImage(RENDERER, battery_30, x, 3);
			percent = 30;
			break;
		case 4:
			SDL_DrawImage(RENDERER, battery_50, x, 3);
			percent = 50;
			break;
		case 5:
			SDL_DrawImage(RENDERER, battery_80, x, 3);
			percent = 80;
			break;
		case 6:
			SDL_DrawImage(RENDERER, battery_full, x, 3);
			percent = 100;
			break;
		default:
			SDL_DrawImage(RENDERER, battery_unknown, x, 3);
			percent = -2;
			break;
	}

	if (percent >= 0)
		snprintf(buf, 5, "%d%%", percent);
	else if (percent == -1)
		snprintf(buf, 5, "CHRG");
	else if (percent == -2)
		snprintf(buf, 5, "UNKN");

	TTF_SizeText(Roboto, buf, &width, NULL);
	SDL_DrawText(RENDERER, Roboto, (x - width - 10), y, WHITE, buf);
}

void StatusBar_DisplayTime(void)
{
	int width = 0, height = 0;
	TTF_SizeText(Roboto, Clock_GetCurrentTime(), &width, &height);

	StatusBar_GetBatteryStatus(1260 - width - 44, (40 - height) / 2);
	SDL_DrawText(RENDERER, Roboto, 1260 - width, (40 - height) / 2, WHITE, Clock_GetCurrentTime());
}