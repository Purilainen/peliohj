#include "MyGameComponentFactory.h"

MyGameComponentFactory::MyGameComponentFactory() : yam2d::DefaultComponentFactory()
{

}

MyGameComponentFactory::~MyGameComponentFactory()
{

}

yam2d::Component* MyGameComponentFactory::createNewComponent(const std::string& type, yam2d::Entity* owner, const yam2d::PropertySet& properties)
{
        //Using default one atm
        return DefaultComponentFactory::createNewComponent(type, owner, properties);
}

yam2d::Entity* MyGameComponentFactory::createNewEntity(ComponentFactory* componentFactory, const std::string& type, yam2d::Entity* parent, const yam2d::PropertySet& properties)
{
    if ("PlayerPad" == type)
    {
        yam2d::GameObject* gameObject = new yam2d::GameObject(parent, properties);
        gameObject->addComponent(componentFactory->createNewComponent("Tile", gameObject, properties));
        PlayerController* pcontroller = new PlayerController(gameObject);
        gameObject->addComponent(pcontroller);
        return gameObject;
    }
    else if ("Ball" == type)
    {
        yam2d::GameObject* gameObject = new yam2d::GameObject(parent, properties);
        gameObject->addComponent(componentFactory->createNewComponent("Tile", gameObject, properties));
        BallController* bcontroller = new BallController(gameObject);
        gameObject->addComponent(bcontroller);
        return gameObject;
    }
    else if ("Brick" == type)
    {
        yam2d::GameObject* gameObject = new yam2d::GameObject(parent, properties);
        gameObject->addComponent(componentFactory->createNewComponent("Tile", gameObject, properties));
        return gameObject;
    }
    else if ("StaticCollider" == type)
    {
        yam2d::GameObject* gameObject = new yam2d::GameObject(parent, properties);
        return gameObject;
    }

    //Default functionality
    yam2d::Entity* res = DefaultComponentFactory::createNewEntity(componentFactory, type, parent, properties);
    assert(res != 0);
    return res;

}
