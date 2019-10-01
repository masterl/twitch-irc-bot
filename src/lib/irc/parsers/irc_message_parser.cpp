#include "irc_message_parser.hpp"

namespace bot::lib::irc::parsers
{
    IrcMessage IrcParser::parse_message( std::string const &raw_message )
    {
        IrcMessage message;

        ParserControl control{raw_message};

        bool result = parse_irc_prefix( control, message.prefix );

        result &= parse_irc_command( control, message.command );

        return message;
    }

    bool IrcParser::parse_irc_prefix( ParserControl &control, IrcPrefix &prefix )
    {
        // prefix      =  servername / ( nickname [ [ "!" user ] "@" host ] )

        // clang-format off
        bool const r = phrase_parse(
            control.first,
            control.last,
            (
                lit(':') >> qi::as_string[lexeme[+~char_(" !@")]][phoenix::ref(prefix.name) = _1] >>
                -(lit('!') >> qi::as_string[lexeme[+~char_(" !@")]][phoenix::ref(prefix.user) = _1]) >>
                -(lit('@') >> qi::as_string[lexeme[+~char_(" !@")]][phoenix::ref(prefix.host) = _1])
            ),
            space );
        // clang-format on

        return r;
    }

    bool IrcParser::parse_irc_command( ParserControl &control, std::string &command )
    {
        // command     =  1*letter / 3digit

        // clang-format off
        bool const r = phrase_parse(
            control.first,
            control.last,
            (
                qi::as_string[
                    lexeme[+char_("A-Z")] | repeat(3)[digit]
                ]
                [phoenix::ref(command) = _1]
            ),
            space );
        // clang-format on

        return r;
    }
} // namespace bot::lib::irc::parsers
