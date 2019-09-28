#include "irc_message_parser.hpp"

namespace bot::lib::irc::parsers
{
    IrcMessage IrcParser::parse_message( std::string const &raw_message )
    {
        IrcMessage message;

        bool result = parse_irc_prefix( raw_message, message.prefix );

        return message;
    }

    bool IrcParser::parse_irc_prefix( std::string const &message, IrcPrefix &prefix )
    {
        // prefix      =  servername / ( nickname [ [ "!" user ] "@" host ] )

        auto first{message.begin()};
        auto const last{message.end()};

        // clang-format off
        bool const r = phrase_parse(
            first,
            last,
            (
                lit(':') >> qi::as_string[lexeme[+~char_(" !@")]][phoenix::ref(prefix.name) = _1] >>
                -(lit('!') >> qi::as_string[lexeme[+~char_(" !@")]][phoenix::ref(prefix.user) = _1]) >>
                -(lit('@') >> qi::as_string[lexeme[+~char_(" !@")]][phoenix::ref(prefix.host) = _1])
            ),
            space );
        // clang-format on

        return r;
    }
} // namespace bot::lib::irc::parsers
