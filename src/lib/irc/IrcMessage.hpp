#ifndef LIB_IRC_IRC_MESSAGE_HPP
#define LIB_IRC_IRC_MESSAGE_HPP

#include <string>

#include "IrcPrefix.hpp"

namespace bot::lib::irc
{
    struct IrcMessage
    {
        IrcPrefix prefix;
    };
} // namespace bot::lib::irc

#endif
