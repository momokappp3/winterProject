#pragma once
/*

全ての ObjectBase を管理する

*/

class ObjectBase;

class ObjectServer {
public:
    static void Add(ObjectBase* objectBase);
    static void Delete(ObjectBase* objectBase);
    static ObjectBase* Get(unsigned int id);
};