#pragma once
/*

‘S‚Ä‚Ì ObjectBase ‚ğŠÇ—‚·‚é

*/

class ObjectBase;

class ObjectServer {
public:
    static void Add(ObjectBase* objectBase);
    static void Delete(ObjectBase* objectBase);
    static ObjectBase* Get(unsigned int id);
};