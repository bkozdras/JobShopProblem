#pragma once

// Please comment below phrase in case of Karol's PC
#define IS_BARTEK_PC

#ifdef IS_BARTEK_PC

    #define UT_UTILITIES_FILE_PATH "E:\\Work\\Visual Projects\\JobShopProblem\\Debug\\UT\\Utilities\\ExampleFile.txt"
    #define UT_PROGRAM_TA01_PATH "E:\\Work\\Visual Projects\\JobShopScheduling\\Debug\\UT\\Program\\ta01.txt"

#else

    #define UT_UTILITIES_FILE_PATH "E:\\Work\\Visual Projects\\JobShopProblem\\Debug\\UT\\Utilities\\ExampleFile.txt"
    #define UT_PROGRAM_TA01_PATH "E:\\Work\\Visual Projects\\JobShopScheduling\\Debug\\UT\\Program\\ta01.txt"

#endif

#ifdef IS_BARTEK_PC
    #undef IS_BARTEK_PC
#endif