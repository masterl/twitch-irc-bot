#ifndef LIB_IRC_IRC_MESSAGE_HPP
#define LIB_IRC_IRC_MESSAGE_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "IrcPrefix.hpp"

namespace bot::lib::irc
{
    using Tags = std::unordered_map< std::string, std::string >;
    using Middle = std::vector< std::string >;

    struct IrcMessage
    {
        Tags tags;
        IrcPrefix prefix;
        std::string command;
        Middle middle;
        std::string trailing;
    };
} // namespace bot::lib::irc

#endif
