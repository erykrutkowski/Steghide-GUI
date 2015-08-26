#ifndef STD_REDIRECTOR
#define STD_REDIRECTOR
#include <cstdlib>
#include <cstdio>
#include <streambuf>

template< class Elem = char, class Tr = std::char_traits< Elem > >
  class StdRedirector : public std::basic_streambuf< Elem, Tr >
  {
      /**
        * Callback Function.
        */
    typedef void (*pfncb) ( const Elem*, std::streamsize _Count, void* pUsrData );

  public:
      /**
        * Constructor.
        * @param a_Stream the stream to redirect
        * @param a_Cb the callback function
        * @param a_pUsrData user data passed to callback
        */
    StdRedirector( std::ostream& a_Stream, pfncb a_Cb, void* a_pUsrData ) :
      m_Stream( a_Stream ),
      m_pCbFunc( a_Cb ),
      m_pUserData( a_pUsrData )
    {
        //redirect stream
      m_pBuf = m_Stream.rdbuf( this );
    };

      /**
        * Destructor.
        * Restores the original stream.
        */
    ~StdRedirector()
    {
      m_Stream.rdbuf( m_pBuf );
    }

      /**
        * Override xsputn and make it forward data to the callback function.
        */
    std::streamsize xsputn( const Elem* _Ptr, std::streamsize _Count )
    {
      m_pCbFunc( _Ptr, _Count, m_pUserData );
      return _Count;
    }

      /**
        * Override overflow and make it forward data to the callback function.
        */
    typename Tr::int_type overflow( typename Tr::int_type v )
    {
      Elem ch = Tr::to_char_type( v );
      m_pCbFunc( &ch, 1, m_pUserData );
      return Tr::not_eof( v );
    }

 protected:
    std::basic_ostream<Elem, Tr>& m_Stream;
    std::streambuf*               m_pBuf;
    pfncb                         m_pCbFunc;
    void*                         m_pUserData;
  };
#endif
