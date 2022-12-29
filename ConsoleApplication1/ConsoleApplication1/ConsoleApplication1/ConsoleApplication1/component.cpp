#include "component.h"

bool TextButton::isIn(int point_x, int point_y)
{
	if (point_x >= x && point_x <= x + textwidth(str) + 2 * left && point_y >= y && point_y <= y + textheight(str) + 2 * top)
		return true;
	else
		return false;
}

void TextButton::draw()
{
	auto pstyle = std::make_shared<LINESTYLE>();
	getlinestyle(pstyle.get());
	setlinestyle(PS_SOLID, 1);
	COLORREF tempColor = getfillcolor();
	setfillcolor(background_color);         // Ìî³äÑÕÉ«ÉèÖÃ
	fillroundrect(x, y, x + textwidth(str) + 2 * left, y + textheight(str) + 2 * top, roundRadius, roundRadius);
	setfillcolor(tempColor);
	setlinestyle(pstyle.get());
	outtextxy(x + left, y + top, str);
}
bool Radio::isIn(int point_x, int point_y)
{
	if (point_x >= x - radius && point_x <= x + radius && point_y >= y - radius && point_y <= y + radius)
		return true;
	else
		return false;
}

void Radio::draw(int groupValue)
{
	auto pstyle = std::make_shared<LINESTYLE>();
	getlinestyle(pstyle.get());
	setlinestyle(PS_SOLID, 1);
	setfillcolor(WHITE);
	fillcircle(x, y, radius);
	setlinestyle(pstyle.get());

	if (value == groupValue) {
		COLORREF tempColor = getfillcolor();
		setfillcolor(GREEN);
		fillcircle(x, y, radius / 3);
		setfillcolor(tempColor);
	}
}