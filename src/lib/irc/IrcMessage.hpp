#ifndef LIB_IRC_IRC_MESSAGE_HPP
#define LIB_IRC_IRC_MESSAGE_HPP

#include <string>
#include <vector>

#include "IrcPrefix.hpp"

namespace bot::lib::irc
{
    using Middle = std::vector< std::string >;

    struct IrcMessage
    {
        IrcPrefix prefix;
        std::string command;
        Middle middle;
    };
} // namespace bot::lib::irc

#endif
