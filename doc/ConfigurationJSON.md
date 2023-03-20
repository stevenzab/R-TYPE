# What is the JSON ?

JSON stands for JavaScript Object Notation. It is a lightweight and flexible data format used to store and exchange data. The JSON format is similar to JavaScript objects and is often used to pass data between applications written in different languages.

JSON data is organized into key-value pairs, called JSON objects. JSON objects are surrounded by braces ({}) and each key-value pair is separated by a comma. Keys are strings and values can be strings, numbers, booleans, arrays or other JSON objects.

Example :

```Json
{
  "name": "Jean",
  "age": 25,
  "city": "Paris"
}
```

JSON arrays are enclosed in square brackets ([]) and array elements are separated by commas. Array elements can be any JSON value type, including JSON objects.

Example :

```Json
[  "rouge",  "vert",  "bleu"]
```

Example of use :

```Json
{
  "utilisateurs": [
    {
      "name": "Jean",
      "age": 25,
      "city": "Paris"
    },
    {
      "name": "Sophie",
      "age": 30,
      "city": "Lyon"
    },
    {
      "name": "Pierre",
      "age": 45,
      "city": "Marseille"
    }
  ]
}

```

# JSON File Configuration for Game Entities

The Game folder includes a program that can read a JSON file and create an Entity with all the necessary components. The [Configuration.cpp](../Game/src/Gameplay/Configuration.cpp) file contains this program

# JSON File Format

The JSON file must follow this format:

```Json
{
  "entities": [
    {
      "id" : 1,
      "components": [
        {
            "type": "Position",
            "x": 500,
            "y": 800
        },
        {
            "type": "Render",
            "filename": "texture.png"
        },
        {
            "type": "Movement",
            "speed": 5,
            "direction": 0
        },
        {
            "type": "Collision",
            "x" : 400,
            "y" : 700,
            "width" : 200,
            "height" : 200
        }
      ]
    }
  ]
}
```

# Creating Entities

To create a new Entity, start by initializing "entities" in the JSON file. Next, assign an id number to differentiate it from other entities. Then, create a group of "components" with their respective characteristics.

# Functions

There are two functions that you can use depending on the type of use case.

If you want to create a group of Entities (a vector of Entity) and they are the same, use this function:

```cpp
std::vector<Entity*> Configuration::createEntitiesFromJsonFile(const std::string& filename)
```

On the other hand, if you want to create a single Entity, use this function:

```cpp
Entity *createEntityFromJson(const std::string& filename)
```

# List of component

Here the list of functionnal component. The list can be updating soon :

 Class name         | Name        |  Parameter                                  |Purpose/Function
 -------------------|-------------|---------------------------------------------|--------------------------------------------------------------------------------
 Component          |             |                                             | Base class for all components. It defines the variable "id" and the pure virtual destructor. (Don't use in the json)
 CollisionComponent | Collision   | x = int, y = int, width = int, height = int | Manages collision detection and stores the object's hitbox.
 PositionComponent  | Position    | x = int, y = int                            | Manages object position and velocity.
 MovementComponent	| Movement    | speed = int, direction = int                | Manages object movement speed and direction.
 LifeComponent      | Life        | life = int                                  | Manages the object's health and tracks its state of being alive or dead.
 RenderComponent    | Render      | filename = string                           | Manages rendering the object's texture.
 SoundComponent	    | Sound       | filename = string                           | Manages the object's sound.

# How to create a new Component

To create a new component, you need to inherit from the base Component class. The base Component class contains a virtual destructor and an id variable, which is inherited by all components. When creating a new component, you should define the functionality of the component based on its purpose. Above are some existing components as examples.

As an example, to create a JumpComponent, you could define its functionality as handling the object's ability to jump. You could implement the necessary functionality in a new class that inherits from the base Component class.


When defining the new component, you should also consider what data it needs to store and what methods it needs to implement. This will depend on the functionality of the component. In the case of the JumpComponent, it may need to store variables such as the jump height and the jump speed. It may also need to implement methods for jumping and checking if the object is currently jumping.

Once you have defined the new component class, you can add it to your game object by creating an instance of the component and adding it to the game object's component list. This will allow you to access the functionality of the component and use it in your game.

Example :

```cpp
class JumpComponent : public Component {
    public :
        JumpComponent(int speed, int fall, int max);
        int _speed;
        int _fall;
        int _max;
};
```