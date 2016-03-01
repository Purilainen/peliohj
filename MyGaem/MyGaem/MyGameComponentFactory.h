#ifndef MYGAMECOMPONENTFACTORY_H
#define MYGAMECOMPONENTFACTORY_H

#include "TileComponent.h"
#include "Entity.h"
#include "PlayerController.h"
#include "BallController.h"

class MyGameComponentFactory : public yam2d::DefaultComponentFactory
{
public:

    MyGameComponentFactory();
    ~MyGameComponentFactory();
    virtual yam2d::Component* createNewComponent(const std::string& type, yam2d::Entity* owner, const yam2d::PropertySet& properties);
    virtual yam2d::Entity* createNewEntity(ComponentFactory* componentFactory, const std::string& type, yam2d::Entity* parent, const yam2d::PropertySet& properties);

private:
    yam2d::Ref<yam2d::Map> m_map;
};

#endif