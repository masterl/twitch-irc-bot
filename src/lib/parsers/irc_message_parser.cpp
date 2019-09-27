#include "irc_message_parser.hpp"

#include <boost/spirit/include/qi.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

// clang-format off
BOOST_FUSION_ADAPT_STRUCT(
    bot::lib::IrcMessage,
    ( std::string, prefix )
)
// clang-format on

// template < typename Iterator >
// bool parse_irc_message( Iterator first, Iterator last, std::string &prefix )
// {
//     namespace qi = boost::spirit::qi;
//     namespace ascii = boost::spirit::ascii;
//
//     using ascii::space;
//     using qi::char_;
//     using qi::lit;
//     using qi::phrase_parse;
//
//     // clang-format off
//     bool r = phrase_parse(
//         first,
//         last,
//         lit(":") >> +char_[],
//         space
//     );
//     // clang-format on
//
//     // fail if we did not get a full match
//     if( first != last )
//     {
//         return false;
//     }
//
//     return r;
// }

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

// prefix      =  servername / ( nickname [ [ "!" user ] "@" host ] )

template < typename Iterator >
struct irc_message_parser : qi::grammar< Iterator, bot::lib::IrcMessage(), ascii::space_type >
{
    irc_message_parser()
        : irc_message_parser::base_type( start )
    {
        using ascii::char_;
        using boost::spirit::qi::lexeme;
        using qi::lit;

        identifier = lexeme[+~char_( ' ' )];

        // clang-format off
        start %=
            lit(":")
            >> identifier
            ;
        // clang-format on
    }

    qi::rule< Iterator, std::string(), ascii::space_type > identifier;
    qi::rule< Iterator, bot::lib::IrcMessage(), ascii::space_type > start;
};

// template < typename Iterator >
// bool parse_irc_message( Iterator first, Iterator last, IrcMessage &message )
// {
//     namespace qi = boost::spirit::qi;
//     namespace ascii = boost::spirit::ascii;
//     using qi::phrase_parse;
//
//     using ascii::space;
//
//     irc_message_parser grammar;
//
//     bool const r = phrase_parse( first, last, grammar, space, message );
//
//     // fail if we did not get a full match
//     if( first != last )
//     {
//         return false;
//     }
//
//     return r;
// }

namespace bot::lib::parsers
{
    IrcMessage parse_irc_message( std::string const &raw_message )
    {
        IrcMessage message;

        // parse_irc_message( raw_message.begin(), raw_message.end(), message );

        // namespace qi = boost::spirit::qi;
        // namespace ascii = boost::spirit::ascii;
        using qi::phrase_parse;

        using ascii::space;

        typedef std::string::const_iterator iterator_type;
        typedef ::irc_message_parser< iterator_type > message_parser;

        message_parser g;

        auto first = raw_message.begin();
        auto const last = raw_message.end();

        bool const r = phrase_parse( first, last, g, space, message );

        // fail if we did not get a full match
        if( first != last )
        {
            // throw exception!!
            // return false;
        }

        // return r;

        return message;
    }
} // namespace bot::lib::parsers
