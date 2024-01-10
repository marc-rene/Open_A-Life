#pragma once
#include <vector>
#include <iostream>

// Modified Stalin Sort - THIS IS A LOSSY SORTING ALGORITHM
// Find the Largest/Smallest value in the given array and place them at opposite ends of the array
// Ascend the array, sending out of order values to "The Gulag" for immediate execu-- *deletion*
std::vector<int> Stalin_Sort(std::vector<int> arr, bool verbose = false)
{
    int largest = INT_MIN;
    int smallest = INT_MAX;

    if (verbose)
    {
        std::cout << "\n\nStalin Sort Starting inits are (" << smallest << ", " << largest << ")" << std::endl;
        std::cout << "Starting array is\t[";

        for (int i = 0; i < arr.size(); i++)
        {
            std::cout << arr[i] << ", ";
        }

        std::cout << "] " << std::endl;
    }

    // Step 1 : Find the Smallest and Largest values, clump them to the ends
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] < smallest)
        {
            smallest = arr[i];
            arr.erase(arr.begin() + i);
            arr.insert(arr.begin(), smallest);

            if (verbose)
            {
                std::cout << smallest << " is the smallest now\n";
            }
            if (verbose)
            {
                std::cout << "Array is now\t[";

                for (int i = 0; i < arr.size(); i++)
                {
                    std::cout << arr[i] << ", ";
                }

                std::cout << "] " << std::endl;
            }
        }

        if (arr[i] > largest && arr[i] != smallest)
        {
            largest = arr[i];
            arr.erase(arr.begin() + i);
            arr.insert(arr.end(), largest);

            if (verbose)
            {
                std::cout << largest << " is the largest now\n";
            }
            if (verbose)
            {
                std::cout << "Array is now\t[";

                for (int i = 0; i < arr.size(); i++)
                {
                    std::cout << arr[i] << ", ";
                }

                std::cout << "] " << std::endl;
            }
        }
    }

    if (verbose)
    {
        std::cout << "Array after shuffle is\t[";

        for (int i = 0; i < arr.size(); i++)
        {
            std::cout << arr[i] << ", ";
        }

        std::cout << "] " << std::endl;
    }

    std::vector<int> the_list;

    int check_offset = 0;

    // Step 2 : Make note of the traitors
    for (int i = 1; i < arr.size(); i++)
    {
        if (!(arr[i - (1 + check_offset)] <= arr[i]))
        {
            the_list.push_back(i);
            check_offset++;
        }
        else
        {
            check_offset = 0;
        }
    }

    int purges_total = 0;
    if (verbose)
    {
        std::cout << "\t\t" << the_list.size() << " elements are to be removed" << std::endl;
    }
    
    // Step 3 : Initiate the purge
    while (the_list.size() > 0)
    {
        arr.erase(arr.begin() + (the_list[0] - purges_total));
        the_list.erase(the_list.begin());
        purges_total++;
    }

    if (verbose)
    {
        std::cout << "Purged array is\t\t[";

        for (int i = 0; i < arr.size(); i++)
        {
            std::cout << arr[i] << ", ";
        }

        std::cout << "] " << std::endl;
    }

    return arr;
}