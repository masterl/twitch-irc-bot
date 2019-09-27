#ifndef LIB_PARSERS_IRC_MESSAGE_PARSER_HPP
#define LIB_PARSERS_IRC_MESSAGE_PARSER_HPP

#include "../IrcMessage.hpp"

namespace bot::lib::parsers
{
    IrcMessage parse_irc_message( std::string const &raw_message );
}

#endif
