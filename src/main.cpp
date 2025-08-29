#include "rock/rock.h"
#include "string"
#include <iostream>

int main()
{
    rock::vec2 vec(10, 10);
    rock::list<rock::list<rock::vec2>> grid (10, rock::list<rock::vec2> (10, vec));

    for (auto l : grid)
    {
        for (auto v : l)
        {
            std::cout << v.x << std::endl;
        }
    }
}