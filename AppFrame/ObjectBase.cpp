#include "ObjectBase.h"
#include "ObjectServer.h"

namespace {
    unsigned int objectBaseInstanceCountrt = 0;
}

ObjectBase::ObjectBase() {
    _id = ++objectBaseInstanceCountrt;
    ObjectServer::Add(this);
}

ObjectBase::~ObjectBase() {
    ObjectServer::Delete(this);
}