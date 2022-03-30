#pragma once
#include "../src/core/application.h"
#include "../src/core/log.h"

int main(int argc, char const *argv[])
{
    ph::Application::run();

    return 0;
}

#define PH_SET_APPLICATION(app)                                     \
ph::Application* ph::Application::get()                             \
{                                                                   \
    static Application* instance = (ph::Application*) new app();    \
                                                                    \
    return instance;                                                \
}
