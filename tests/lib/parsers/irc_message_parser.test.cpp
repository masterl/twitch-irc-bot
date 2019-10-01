#include <catch/catch.hpp>

#include "lib/irc/parsers/irc_message_parser.hpp"

using bot::lib::irc::IrcMessage;
using bot::lib::irc::parsers::IrcParser;

SCENARIO( "Parsing prefix from raw IRC message", "[irc_message_parser][irc_message_prefix]" )
{
    IrcParser irc_parser;

    GIVEN( "A string containing the message \":tmi.twitch.tv 001 bigodationbot :Welcome, GLHF!\"" )
    {
        std::string const raw_irc_message{":tmi.twitch.tv 001 bigodationbot :Welcome, GLHF!\r\n"};

        WHEN( "the parser is invoked" )
        {
            IrcMessage const message = irc_parser.parse_message( raw_irc_message );

            THEN( "returned message.prefix.name should contain the name" )
            {
                REQUIRE( message.prefix.name == "tmi.twitch.tv" );
            }

            THEN( "prefix user should be empty" )
            {
                REQUIRE( message.prefix.user == "" );
            }

            THEN( "prefix host should be empty" )
            {
                REQUIRE( message.prefix.host == "" );
            }

            THEN( "command should contain 001" )
            {
                REQUIRE( message.command == "001" );
            }

            THEN( "middle should contain [\"bigodationbot\"]" )
            {
                REQUIRE( message.middle.size() == 1 );
                REQUIRE( message.middle[0] == "bigodationbot" );
            }

            THEN( "trailing should contain \"Welcome, GLHF!\"" )
            {
                REQUIRE( message.trailing == "Welcome, GLHF!" );
            }
        }
    }

    GIVEN( "A string containing the message \":empix!empix@empix.tmi.twitch.tv PRIVMSG #bigodation "
           ":@bigodation oi\"" )
    {
        std::string const raw_irc_message{
            ":empix!someuser@host.tmi.twitch.tv PRIVMSG #bigodation :@bigodation oi\r\n"};

        WHEN( "the parser is invoked" )
        {
            IrcMessage const message = irc_parser.parse_message( raw_irc_message );

            THEN( "prefix should contain name" )
            {
                REQUIRE( message.prefix.name == "empix" );
            }

            THEN( "prefix should contain the user" )
            {
                REQUIRE( message.prefix.user == "someuser" );
            }

            THEN( "prefix should contain the host" )
            {
                REQUIRE( message.prefix.host == "host.tmi.twitch.tv" );
            }

            THEN( "command should contain PRIVMSG" )
            {
                REQUIRE( message.command == "PRIVMSG" );
            }

            THEN( "middle should contain [\"#bigodation\"]" )
            {
                REQUIRE( message.middle.size() == 1 );
                REQUIRE( message.middle[0] == "#bigodation" );
            }

            THEN( "trailing should contain \"@bigodation oi\"" )
            {
                REQUIRE( message.trailing == "@bigodation oi" );
            }
        }
    }

    GIVEN( "A string containing the message \":empix@empix.tmi.twitch.tv PRIVMSG #bigodation "
           ":@bigodation oi\"" )
    {
        std::string const raw_irc_message{
            ":empix@host.tmi.twitch.tv PRIVMSG #bigodation :@bigodation oi\r\n"};

        WHEN( "the parser is invoked" )
        {
            IrcMessage const message = irc_parser.parse_message( raw_irc_message );

            THEN( "prefix should contain name" )
            {
                REQUIRE( message.prefix.name == "empix" );
            }

            THEN( "prefix should contain the user" )
            {
                REQUIRE( message.prefix.user == "" );
            }

            THEN( "prefix should contain the host" )
            {
                REQUIRE( message.prefix.host == "host.tmi.twitch.tv" );
            }

            THEN( "command should contain PRIVMSG" )
            {
                REQUIRE( message.command == "PRIVMSG" );
            }

            THEN( "middle should contain [\"#bigodation\"]" )
            {
                REQUIRE( message.middle.size() == 1 );
                REQUIRE( message.middle[0] == "#bigodation" );
            }

            THEN( "trailing should contain \"@bigodation oi\"" )
            {
                REQUIRE( message.trailing == "@bigodation oi" );
            }
        }
    }

    GIVEN( "A string containing the message \":bigodationbot.tmi.twitch.tv 353 bigodationbot = "
           "#bigodation :bigodationbot\"" )
    {
        std::string const raw_irc_message{
            ":bigodationbot.tmi.twitch.tv 353 bigodationbot = #bigodation :bigodationbot\r\n"};

        WHEN( "the parser is invoked" )
        {
            IrcMessage const message = irc_parser.parse_message( raw_irc_message );

            THEN( "prefix should contain name" )
            {
                REQUIRE( message.prefix.name == "bigodationbot.tmi.twitch.tv" );
            }

            THEN( "prefix should contain the user" )
            {
                REQUIRE( message.prefix.user == "" );
            }

            THEN( "prefix should contain the host" )
            {
                REQUIRE( message.prefix.host == "" );
            }

            THEN( "command should contain 353" )
            {
                REQUIRE( message.command == "353" );
            }

            THEN( "middle should contain [\"bigodationbot\"]" )
            {
                REQUIRE( message.middle.size() == 3 );
                REQUIRE( message.middle[0] == "bigodationbot" );
                REQUIRE( message.middle[1] == "=" );
                REQUIRE( message.middle[2] == "#bigodation" );
            }

            THEN( "trailing should contain \"bigodationbot\"" )
            {
                REQUIRE( message.trailing == "bigodationbot" );
            }
        }
    }

    GIVEN( "A string containing the message "
           "\"@a2-4a;campo=1;admin;hello=78 353\"" )
    {
        std::string const raw_irc_message{"@a2-4a;campo=1;admin;hello=78 353\r\n"};

        WHEN( "the parser is invoked" )
        {
            IrcMessage const message = irc_parser.parse_message( raw_irc_message );

            auto const not_on_map = message.tags.end();

            THEN( "command should contain 353" )
            {
                REQUIRE( message.command == "353" );
            }

            THEN( "message.tags size should be 4" )
            {
                REQUIRE( message.tags.size() == 4 );
            }

            THEN( "message.tags should contain a2-4a" )
            {
                auto const item = message.tags.find( "a2-4a" );
                REQUIRE( item != not_on_map );

                auto const [key, value] = *item;

                REQUIRE( value == "" );
            }

            THEN( "message.tags should contain campo" )
            {
                auto const item = message.tags.find( "campo" );
                REQUIRE( item != not_on_map );

                auto const [key, value] = *item;

                REQUIRE( value == "1" );
            }

            THEN( "message.tags should contain admin" )
            {
                auto const item = message.tags.find( "admin" );
                REQUIRE( item != not_on_map );

                auto const [key, value] = *item;

                REQUIRE( value == "" );
            }

            THEN( "message.tags should contain hello" )
            {
                auto const item = message.tags.find( "hello" );
                REQUIRE( item != not_on_map );

                auto const [key, value] = *item;

                REQUIRE( value == "78" );
            }
        }
    }
}

/*
IRC doc: https://modern.ircdocs.horse/


  message     =  [ "@" tags SPACE ] [ ":" prefix SPACE ] command
                 [ params ] crlf

  tags        =  tag *[ ";" tag ]
  tag         =  key [ "=" value ]
  key         =  [ vendor "/" ] 1*( ALPHA / DIGIT / "-" )
  value       =  *valuechar
  valuechar   =  <any octet except NUL, BELL, CR, LF, semicolon (`;`) and SPACE>
  vendor      =  hostname

 => prefix      =  servername / ( nickname [ [ "!" user ] "@" host ] )

  command     =  1*letter / 3digit

  params      =  *( SPACE middle ) [ SPACE ":" trailing ]
  nospcrlfcl  =  <any octet except NUL, CR, LF, colon (`:`) and SPACE>
  middle      =  nospcrlfcl *( ":" / nospcrlfcl )
  trailing    =  *( ":" / " " / nospcrlfcl )


  SPACE       =  %x20 *( %x20 )   ; space character(s)
  crlf        =  %x0D %x0A        ; "carriage return" "linefeed"
*/

/*
:tmi.twitch.tv 001 bigodationbot :Welcome, GLHF!
:tmi.twitch.tv 002 bigodationbot :Your host is tmi.twitch.tv
:tmi.twitch.tv 003 bigodationbot :This server is rather new
:tmi.twitch.tv 004 bigodationbot :-
:tmi.twitch.tv 375 bigodationbot :-
:tmi.twitch.tv 372 bigodationbot :You are in a maze of twisty passages, all alike.
:tmi.twitch.tv 376 bigodationbot :>

:bigodationbot!bigodationbot@bigodationbot.tmi.twitch.tv JOIN #bigodation
:bigodationbot.tmi.twitch.tv 353 bigodationbot = #bigodation :bigodationbot
:bigodationbot.tmi.twitch.tv 366 bigodationbot #bigodation :End of /NAMES list
:bigodationbot.tmi.twitch.tv 353 bigodationbot = #bigodation
:empix!empix@empix.tmi.twitch.tv PRIVMSG #bigodation :@bigodation oi


[:tmi.twitch.tv 001 bigodationbot :Welcome, GLHF!
:tmi.twitch.tv 002 bigodationbot :Your host is tmi.twitch.tv
:tmi.twitch.tv 003 bigodationbot :This server is rather new
:tmi.twitch.tv 004 bigodationbot :-
:tmi.twitch.tv 375 bigodationbot :-
:tmi.twitch.tv 372 bigodationbot :You are in a maze of twisty passages, all alike.
:tmi.twitch.tv 376 bigodationbot :>
]
[:bigodationbot!bigodationbot@bigodationbot.tmi.twitch.tv JOIN #bigodation
]
FECHANDO!
[:bigodationbot.tmi.twitch.tv 353 bigodationbot = #bigodation :bigodationbot
:bigodationbot.tmi.twitch.tv 366 bigodationbot #bigodation :End of /NAMES list
]
[:bigodation!bigodation@bigodation.tmi.twitch.tv PRIVMSG #bigodation :oi
]

*/
