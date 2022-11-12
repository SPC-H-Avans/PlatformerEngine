#include "Engine/Engine.hpp"
#include "Builder/GameObjectBuilder.hpp"
#include "BehaviourScript.hpp"
#include "RigidBody.hpp"

#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Simple function for debugging and testing collision
void TestCollision() {
    GameObject go1 ("een"); //Dynamic rigidbody
    GameObject go2 ("twee"); //Static rigidbody

    //Set X,Y pos of objects
    go1.SetTransform(Transform {Point {0, 3}, 0, 0});
    go2.SetTransform(Transform {Point {3, 3}, 0, 0});

    //Set Colliders on both objects
    BoxCollider collider;
    collider.Width(3);
    collider.Height(3);
    go1.AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));
    go2.AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));

    //Set Rigidbody on both objects;
    RigidBody body;
    body.BodyType(spic::BodyType::dynamicBody);
    go1.AddComponent<RigidBody>(std::make_shared<RigidBody>(body));
    body.BodyType(spic::BodyType::staticBody);
    go2.AddComponent<RigidBody>(std::make_shared<RigidBody>(body));


    go1.AddComponent<BehaviourScript>(std::make_shared<BehaviourScript>());
    go2.AddComponent<BehaviourScript>(std::make_shared<BehaviourScript>());
}


auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int {
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();

    TestCollision();
    engine.Init(SCREEN_WIDTH, SCREEN_HEIGHT, "Hallo", spic::Color::Green());

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
