#include <iostream>

int main()
{
    int count = 0;
    for (int large_chicken_count = 0; large_chicken_count < 20; large_chicken_count++)
    {
        for (int medium_chicken_count = 0; medium_chicken_count < (100 - large_chicken_count * 5) / 3; medium_chicken_count++)
        {
            count++;
            int little_chicken_count = 100 - large_chicken_count - medium_chicken_count;
            if (little_chicken_count % 3 == 0 && large_chicken_count * 5 + medium_chicken_count * 3 + little_chicken_count / 3 == 100)
            {
                std::cout << "large_chicken_count: " << large_chicken_count << std::endl;
                std::cout << "medium_chicken_count: " << medium_chicken_count << std::endl;
                std::cout << "little_chicken_count: " << little_chicken_count << std::endl;
            }
        }
    }
    std::cout << "count: " << count << std::endl;
}