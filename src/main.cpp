#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>
namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = boost::beast::websocket; // from <boost/beast/websocket.hpp>

class IrcClient
{
    public:
    IrcClient( std::string const &host,
               std::string const &port,
               std::string const &bot_name,
               std::string const &bot_token )
        : resolver_{io_context_}
        , wsocket_{io_context_}
    {
        auto const results = resolver_.resolve( host, port );

        boost::asio::connect( wsocket_.next_layer(), results.begin(), results.end() );
        wsocket_.handshake( host, "/" );

        send_bot_token( bot_token );
        send_bot_name( bot_name );
    }

    ~IrcClient()
    {
        wsocket_.close( websocket::close_code::normal );
    }

    void send_message( std::string const &message )
    {
        wsocket_.write( boost::asio::buffer( message ) );
    }

    std::string read_messages()
    {
        wsocket_.read( buffer_ );

        return string_from_buffer();
    }

    private:
    boost::asio::io_context io_context_;
    tcp::resolver resolver_;
    websocket::stream< tcp::socket > wsocket_;
    beast::flat_buffer buffer_;

    std::string string_from_buffer()
    {
        std::ostringstream ostream;

        ostream << beast::make_printable( buffer_.data() );

        return ostream.str();
    }

    void send_bot_token( std::string const &token )
    {
        std::string const text = std::string( "PASS " ) + token + "\r\n";
        send_message( text );
    }

    void send_bot_name( std::string const &name )
    {
        std::string const text = std::string( "NICK " ) + name + "\r\n";
        send_message( text );
    }
};

int main( int argc, char **argv )
{
    try
    {
        IrcClient client{"irc-ws.chat.twitch.tv",
                         "80",
                         getenv( "TWITCH_BOT_NICK" ),
                         getenv( "TWITCH_BOT_TOKEN" )};

        std::cout << '[' << client.read_messages() << "]\n";

        return 0;
    }
    catch( std::exception const &e )
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
