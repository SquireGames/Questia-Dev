#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <map>

#include "SFML/Window.hpp"

namespace ctr
{
///keys
enum class Input : int
{
    A = sf::Keyboard::A,
    B = sf::Keyboard::B,
    C = sf::Keyboard::C,
    D = sf::Keyboard::D,
    E = sf::Keyboard::E,
    F = sf::Keyboard::F,
    G = sf::Keyboard::G,
    H = sf::Keyboard::H,
    I = sf::Keyboard::I,
    J = sf::Keyboard::J,
    K = sf::Keyboard::K,
    L = sf::Keyboard::L,
    M = sf::Keyboard::M,
    N = sf::Keyboard::N,
    O = sf::Keyboard::O,
    P = sf::Keyboard::P,
    Q = sf::Keyboard::Q,
    R = sf::Keyboard::R,
    S = sf::Keyboard::S,
    T = sf::Keyboard::T,
    U = sf::Keyboard::U,
    V = sf::Keyboard::V,
    W = sf::Keyboard::W,
    X = sf::Keyboard::X,
    Y = sf::Keyboard::Y,
    Z = sf::Keyboard::Z,
    Num0 = sf::Keyboard::Num0,
    Num1 = sf::Keyboard::Num1,
    Num2 = sf::Keyboard::Num2,
    Num3 = sf::Keyboard::Num3,
    Num4 = sf::Keyboard::Num4,
    Num5 = sf::Keyboard::Num5,
    Num6 = sf::Keyboard::Num6,
    Num7 = sf::Keyboard::Num7,
    Num8 = sf::Keyboard::Num8,
    Num9 = sf::Keyboard::Num9,
    Tilde     = sf::Keyboard::Tilde,
    Dash      = sf::Keyboard::Dash,
    Add       = sf::Keyboard::Add,
    BackSpace = sf::Keyboard::BackSpace,
    Tab       = sf::Keyboard::Tab,
    LBracket  = sf::Keyboard::LBracket,
    RBracket  = sf::Keyboard::RBracket,
    BackSlash = sf::Keyboard::BackSlash,
    SemiColon = sf::Keyboard::SemiColon,
    Quote     = sf::Keyboard::Quote,
    Return    = sf::Keyboard::Return,
    LShift    = sf::Keyboard::LShift,
    Comma     = sf::Keyboard::Comma,
    Period    = sf::Keyboard::Period,
    Slash     = sf::Keyboard::Slash,
    RShift    = sf::Keyboard::RShift,
    LControl  = sf::Keyboard::LControl,
    LAlt      = sf::Keyboard::LAlt,
    Space     = sf::Keyboard::Space,
    RAlt      = sf::Keyboard::RAlt,
    RControl  = sf::Keyboard::RControl,
    Up        = sf::Keyboard::Up,
    Down      = sf::Keyboard::Down,
    Left      = sf::Keyboard::Left,
    Right     = sf::Keyboard::Right,
    Insert    = sf::Keyboard::Insert,
    Home      = sf::Keyboard::Home,
    Delete    = sf::Keyboard::Delete,
    End       = sf::Keyboard::End,
    PageUp    = sf::Keyboard::PageUp,
    PageDown  = sf::Keyboard::PageDown,
    LMouse    = 1 + sf::Keyboard::KeyCount,
    RMouse    = 1 + Input::LMouse,
    MMouse    = 1 + Input::RMouse,
    Macro1    = 1 + Input::MMouse,
    Macro2    = 1 + Input::Macro1,
	None      = 1 + Input::Macro2,
    InputCount = 1 + Input::None
};

//returns name of input
std::string getInputName(const sf::Keyboard::Key input);
std::string getInputName(const int input);
std::string getInputName(const ctr::Input input);

bool checkInput(const ctr::Input input);
}
#endif // KEYBOARD_H
