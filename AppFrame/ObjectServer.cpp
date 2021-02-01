#include <unordered_map>
#include "ObjectBase.h"
#include "ObjectServer.h"

namespace {
    std::unordered_map<unsigned int, ObjectBase*> _objectMap;
}

void ObjectServer::Add(ObjectBase* objectBase) {
    _objectMap.emplace(objectBase->GetId(), objectBase);
}

void ObjectServer::Delete(ObjectBase* objectBase) {
    _objectMap.erase(objectBase->GetId());
}

ObjectBase* ObjectServer::Get(unsigned int id) {
    return _objectMap.at(id);
}
