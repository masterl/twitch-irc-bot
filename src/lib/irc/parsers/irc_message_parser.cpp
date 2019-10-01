#include "irc_message_parser.hpp"

#include <boost/spirit/include/phoenix_stl.hpp>

namespace bot::lib::irc::parsers
{
    IrcMessage IrcParser::parse_message( std::string const &raw_message )
    {
        IrcMessage message;

        ParserControl control{raw_message};

        bool result = parse_irc_prefix( control, message.prefix );

        result &= parse_irc_command( control, message.command );

        // necessary until we can no-skip spaces!
        --control.first;

        result &= parse_irc_middle( control, message.middle );

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

    bool IrcParser::parse_irc_middle( ParserControl &control, Middle &middle )
    {
        // params      =  *( SPACE middle ) [ SPACE ":" trailing ]
        // nospcrlfcl  =  <any octet except NUL, CR, LF, colon (`:`) and SPACE>
        // middle      =  nospcrlfcl *( ":" / nospcrlfcl )

        using phoenix::push_back;
        using qi::no_skip;
        // using qi::parse;

        // clang-format off
        bool const r = phrase_parse(
            control.first,
            control.last,
            (
                -*(
                    no_skip[lit(' ')] >>
                    qi::as_string[
                        no_skip[
                            ~char_("\r\n: ") >>
                            *(lit(':') | ~char_("\r\n: "))
                        ]
                    ][push_back(phoenix::ref(middle), _1)]
                )
            ),
            space);
        // clang-format on

        return r;
    }
} // namespace bot::lib::irc::parsers
