#pragma once
/*

全てのオブジェクトの基底クラス

*/

class ObjectBase {
public:
    ObjectBase();
    virtual ~ObjectBase();

    virtual void Process() = 0;
    virtual void Render() = 0;

    unsigned int GetId() const {
        return _id;
    }

protected:
    unsigned int _id;
};