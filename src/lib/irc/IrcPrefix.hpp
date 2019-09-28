#ifndef LIB_IRC_IRC_PREFIX_HPP
#define LIB_IRC_IRC_PREFIX_HPP

#include <string>

namespace bot::lib::irc
{
    struct IrcPrefix
    {
        std::string name;
        std::string user;
        std::string host;
    };
} // namespace bot::lib::irc

#endif
