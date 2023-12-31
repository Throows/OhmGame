#include <OhmEngine/Core/Application.hpp>

namespace OHE
{
    Application::Application(int argc, char** argv)
        : m_Argc(argc), m_Argv(argv)
    {
        s_Instance = this;
    }

    Application::~Application()
    {
    }

    bool Application::Update()
    {
        return true;
    }

    int Application::Run()
    {

        while (1)
        {
        }
    }

    Application *Application::s_Instance = nullptr;
}