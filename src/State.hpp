#ifndef STATE_HPP
#define STATE_HPP

struct SDL_Renderer;
union SDL_Event;

enum class StateType
{
    Menu = 0,
    Singleplayer,
    WaitingRoom,
    Multiplayer,
    Settings,
    Login,
    Exit,

    None,
    Count
};

class State
{
    public:
        virtual ~State() {}

        virtual void init(struct SDL_Window* win) = 0;
        virtual void quit() = 0;

        virtual void processEvent(const SDL_Event& event) {}
        virtual void update(float deltaTime) = 0;
        virtual void draw() = 0;

        virtual StateType getType() const
        {
            return StateType::None;
        }

        virtual StateType nextState() = 0;

    protected:
        SDL_Window* Window = nullptr;
};

#endif /* STATE_HPP */

