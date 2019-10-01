#ifndef LIB_IRC_PARSERS_PARSER_CONTROL_HPP
#define LIB_IRC_PARSERS_PARSER_CONTROL_HPP

namespace bot::lib::irc::parsers
{
    struct ParserControl
    {
        private:
        using StrConstIterator = std::string::const_iterator;

        public:
        ParserControl( std::string const &raw_message )
            : raw_message{raw_message}
            , first{raw_message.begin()}
            , last{raw_message.end()}
        {
        }

        std::string const raw_message;
        StrConstIterator first;
        StrConstIterator const last;
    };
} // namespace bot::lib::irc::parsers
#endif
