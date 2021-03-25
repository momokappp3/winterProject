#pragma once
#include "../../AppFrame/Types.h"
#include <vector>
#include <memory>
#include <functional>

/*
HITの関数
*/

class UI2DBase {
public:
	UI2DBase();
	virtual ~UI2DBase();

	virtual bool Init();
	virtual void Process();
	virtual void Draw();

	Point GetCenter();  ///画像の真ん中を返す

	enum class SelectType {
		Circle = 0,
		Rect,
		Max
	};

	//Set
	int SetDrawInfo(DrawInfo& info) {
		_vDrawInfo.push_back(info);
		return _vDrawInfo.size() - 1;
	}

	void SetStartEnd(Point start, Point end) {
		_start = start;
		_end = end;

		_selectType = SelectType::Rect;
	}

	void SetPoint(int index, Point point) {
		_vDrawInfo[index].xy = point;
	}

	void SetRadius(int radius) {
		_radius = radius;
		_selectType = SelectType::Circle;
	}

	void SetRect() {
		_selectType = SelectType::Rect;
	}

	void SetSelect(int select) {
		_select = select;
	}

	//Get
	bool GetDrawInfo(int index, DrawInfo& info);  //参照なので第二引数に情報が入る

	SelectType GetSelectType() {
		return _selectType;
	}

	int GetHandle(int index) {
		return _vDrawInfo[index].handle;
	}

	Point GetPoint() {
		return _vDrawInfo[0].xy;
	}

	Point GetStart() {
		return _start;
	}
	Point GetEnd() {
		return _end;
	}

	int GetRadius() {
		return _radius;
	}

	int GetSelect() {
		return _select;
	}

protected:

	std::vector<DrawInfo> _vDrawInfo;   //ハンドルとxy描画するための情報を入れている

	SelectType _selectType;

	Point _start;
	Point _end;

	int _radius;
	int _select;

};