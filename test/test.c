#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "../src/LibPwgen/libgen.h"
#include "../thirdparty/ctest.h"

int remfile()
{
    if (remove("Results-passwords/Results.txt") == 0) {
        printf("File deleted successfully.\n");
    } else {
        printf("Failed to delete the file.\n");
    }
    return 0;
}

CTEST(Getrand, returns_random_number_within_range)
{
    int min = 0;
    int max = 10;
    double time = 12345.0;
    double pusk = 6789.0;
    int result = Getrand(min, max, time, pusk);

    ASSERT_TRUE(result >= min && result <= max);
}

CTEST(wtime, returns_current_wall_time_in_seconds)
{
    double result1 = wtime();
    double result2 = wtime();

    ASSERT_TRUE(result1 <= result2);
}

CTEST(getrand_suite, test_getrand)
{
    int rand_num = Getrand(1, 10, 0.5, 0.2);
    ASSERT_GE(rand_num, 1);
    ASSERT_LE(rand_num, 10);
}

CTEST(generation_suite, test_generation)
{
    remfile();
    // Create the libgen structure
    libgen* t = malloc(sizeof(libgen));
    t->dlin = 8;
    t->up = 1;
    t->down = 1;
    t->spets = 0;
    t->kolvo = 5;

    // Create an array good and fill it
    int good[123] = {0};
    for (int i = 48; i <= 57; i++) {
        good[i] = 1; // numbers from 0 to 9
    }
    for (int i = 65; i <= 90; i++) {
        good[i] = 1; // capital letters
    }
    for (int i = 97; i <= 122; i++) {
        good[i] = 1; // lower case
    }

    // Execute the Generation function
    Generation(t, good);

    // Checking for the existence of a file with the results of generating
    // passwords
    FILE* file = fopen("Results-passwords/Results.txt", "r+");
    ASSERT_NOT_NULL(file);

    // Checking the number of generated passwords
    char buffer[1024];
    int cnt = 0;
    while (fgets(buffer, 1024, file) != NULL) {
        if (strstr(buffer, "Password")) {
            cnt++;
        }
    }
    ASSERT_EQUAL(cnt, t->kolvo);

    fclose(file);
    free(t);
}

CTEST(Good, modifies_array_of_good_characters_according_to_libgen_structure)
{
    remfile();
    libgen t = {8, 1, 0, 1, 5};

    int good[123];
    for (int i = 33; i <= 122; i++) {
        good[i] = 1;
    }

    Good(&t);
    ASSERT_TRUE(good['a']);
    ASSERT_TRUE(good['!']);
    ASSERT_TRUE(good['@']);
    ASSERT_TRUE(good['#']);
    ASSERT_TRUE(good['$']);
    ASSERT_TRUE(good['%']);
    ASSERT_TRUE(good['^']);
    ASSERT_TRUE(good['&']);
    ASSERT_TRUE(good['*']);

    // Other characters must not be changed
    ASSERT_TRUE(good['B']);
    ASSERT_TRUE(good['z']);
    ASSERT_TRUE(good['~']);
}