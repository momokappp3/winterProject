#pragma once
/*

�S�Ă� ObjectBase ���Ǘ�����

*/

class ObjectBase;

class ObjectServer {
public:
    static void Add(ObjectBase* objectBase);
    static void Delete(ObjectBase* objectBase);
    static ObjectBase* Get(unsigned int id);
};