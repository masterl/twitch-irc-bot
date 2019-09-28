#include "irc_message_parser.hpp"

#include <regex>
#include <stdexcept>

#include <iostream>

namespace bot::lib::irc::parsers
{
    IrcMessage parse_irc_message( std::string const &raw_message )
    {
        IrcMessage message;

        // std::string data = raw_message;

        std::smatch matches;
        std::regex regex( "^:([^ !@]+)((!([^ !@]+))?@([^ !@]+))?" );

        // prefix      =  servername / ( nickname [ [ "!" user ] "@" host ] )

        if( !std::regex_search( raw_message, matches, regex ) )
        {
            throw std::domain_error( "Couldn't parse prefix!" );
        }

        if( matches[5].length() > 0 )
        {
            message.prefix.host = matches[5];

            if( matches[4].length() > 0 )
            {
                message.prefix.user = matches[4];
            }
        }

        message.prefix.name = matches[1];

        return message;
    }
} // namespace bot::lib::irc::parsers
