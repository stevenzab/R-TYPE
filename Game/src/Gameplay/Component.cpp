/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Component
*/

#include "Component.hpp"

//! Destructor of Component
Component::~Component()
{}

//! Constructor of Position. Take the position x and y as parameters
PositionComponent::PositionComponent(float newX, float newY)
{
    vector = Vector2{newX, newY};
}


//! Constructor of Collision. Take the position x and y, the size width and height as parameters
CollisionComponent::CollisionComponent(float x, float y, float width, float height): hitbox({x, y, width, height})
{

}

//! Constructor of Movement. Take the speed and direction as parameters
MovementComponent::MovementComponent(float _speed, float _direction) : speed(_speed), direction(_direction)
{

}

RenderComponent::RenderComponent(std::string const &fileName)
{
    texture = InitTexture(fileName);
}

void RenderComponent::draw(Vector2 position)
{
    texture.draw(position);
}

void RenderComponent::draw(Vector2 position, float scale)
{
    texture.draw(position, scale);
}

SoundComponent::SoundComponent(std::string const & fileName)
{
    sound = InitSound(fileName);
}

void SoundComponent::play()
{
    sound.play();
}

SpawnComponent::SpawnComponent(float time): limit(time)
{
}