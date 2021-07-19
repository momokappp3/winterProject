#include "Utility.h"

int Utility::ImageHitDetection(int x, int y, UI2DBase* ui2DBase) {

	UI2DBase::SelectType type = ui2DBase->GetSelectType();

	if (type == UI2DBase::SelectType::Circle) {

		Point center = ui2DBase->GetCenter();
		int radius = ui2DBase->GetRadius();
		int squareRadius = radius * radius;

		int vX = center.x - x;
		int vY = center.y - y;
		int squareSize = vX * vX + vY * vY;

		return squareSize <= squareRadius ? 1 : 0;

	}
	else if (type == UI2DBase::SelectType::Rect) {

		int w, h;

		GetGraphSize(ui2DBase->GetHandle(0), &w, &h);

		Point leftUp = ui2DBase->GetPoint();
		Point rightUP = {leftUp.x + w ,leftUp.y};
		Point leftDown = { leftUp.x,leftUp.y + h };
		Point righDown = { leftDown.x + w,leftDown.y + h };
		
		if (x > leftUp.x && y > leftUp.y && x < rightUP.x && y > rightUP.y &&
			x > leftDown.x && y < leftDown.y && x < righDown.x && y < righDown.y) {
			return 1;
		}

		return 0;
	}
    return 1;
}

bool Utility::HitRect(int x, int y, Point leftUp, Point rightDown){

	Point dif = { rightDown.x - leftUp.x,rightDown.y - leftUp.y };

	Point rightUp = { leftUp.x + dif.x, leftUp.y };
	Point leftDown = { leftUp.x,rightDown.y };

	if (x > leftUp.x && y > leftUp.y && x < rightUp.x && y > rightUp.y &&
		x > leftDown.x && y < leftDown.y && x < rightDown.x && y < rightDown.y) {
		return true;
	}
	return false;
}