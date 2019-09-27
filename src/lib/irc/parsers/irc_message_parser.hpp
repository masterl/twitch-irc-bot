#ifndef LIB_IRC_PARSERS_IRC_MESSAGE_PARSER_HPP
#define LIB_IRC_PARSERS_IRC_MESSAGE_PARSER_HPP

#include "../IrcMessage.hpp"

namespace bot::lib::irc::parsers
{
    IrcMessage parse_irc_message( std::string const &raw_message );
}

#endif
