#include <catch/catch.hpp>

#include "lib/irc/parsers/irc_message_parser.hpp"

using bot::lib::irc::IrcMessage;
using bot::lib::irc::parsers::parse_irc_message;

SCENARIO( "Parsing raw IRC message", "[irc_message_parser]" )
{
    GIVEN( "A string containing a message like \":a 001 b :c\"" )
    {
        std::string const raw_irc_message{":tmi.twitch.tv 001 bigodationbot :Welcome, GLHF!\r\n"};

        WHEN( "the parser is invoked" )
        {
            IrcMessage const message = parse_irc_message( raw_irc_message );

            THEN( "returned message should contain a prefix" )
            {
                REQUIRE( message.prefix == "tmi.twitch.tv" );
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

  prefix      =  servername / ( nickname [ [ "!" user ] "@" host ] )

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
