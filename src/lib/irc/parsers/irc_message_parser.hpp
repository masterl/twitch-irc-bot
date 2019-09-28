#ifndef LIB_IRC_PARSERS_IRC_MESSAGE_PARSER_HPP
#define LIB_IRC_PARSERS_IRC_MESSAGE_PARSER_HPP

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi.hpp>

#include "../IrcMessage.hpp"

namespace bot::lib::irc::parsers
{
    namespace spirit = boost::spirit;
    namespace qi = spirit::qi;
    namespace ascii = spirit::ascii;
    namespace phoenix = boost::phoenix;

    using ascii::space;
    using qi::_1;
    using qi::char_;
    using qi::lexeme;
    using qi::lit;
    using qi::phrase_parse;

    // template < typename Iterator >
    // struct prefix_parser : qi::grammar< Iterator, IrcPrefix(), ascii::space_type >
    // {
    //     prefix_parser()
    //         : prefix_parser::base_type( start )
    //     {
    //         using ascii::char_;
    //         using qi::double_;
    //         using qi::int_;
    //         using qi::lexeme;
    //         using qi::lit;
    //
    //         identifier %= qi::as_string[+( ~char_( " !@" ) )];
    //
    //         // clang-format off
    //         start %=
    //             lit(':') >> identifier >>
    //             -(lit('!') >> identifier) >>
    //             -(lit('@') >> identifier)
    //             ;
    //         // clang-format on
    //     }
    //
    //     qi::rule< Iterator, std::string(), ascii::space_type > identifier;
    //     qi::rule< Iterator, IrcPrefix(), ascii::space_type > start;
    // };

    class IrcParser
    {
        public:
        IrcMessage parse_message( std::string const &raw_message );

        private:
        bool parse_irc_prefix( std::string const &message, IrcPrefix &prefix );
    };
} // namespace bot::lib::irc::parsers

#endif
