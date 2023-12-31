#pragma once 

namespace OHE 
{
    class Application
    {
    public:
        Application(int argc, char** argv);
        ~Application();

        bool Update();
        int Run();

        static Application* Get() { return s_Instance; };

    private:
        int m_Argc;
        char** m_Argv;

        static Application* s_Instance;
    };
} // namespace OHE
