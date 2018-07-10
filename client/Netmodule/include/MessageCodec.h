#ifndef MESSAGE_CODEC_H
#define MESSAGE_CODEC_H

#include "Eio.hh"

namespace Netmodule{
/* --------------------------------------------------------------------------------------------------
 *      MessageEncoder
 * -------------------------------------------------------------------------------------------------- */  
    class MessageEncoder : public EProtocolEncoder{
    public:
        void encode(sp<EIoSession>& session, sp<EObject>& message, sp<EProtocolEncoderOutput>& out) THROWS(EException);
        void dispose(sp<EIoSession>& session) THROWS(EException);
    };
/* --------------------------------------------------------------------------------------------------
 *      Messagedecoder
 * -------------------------------------------------------------------------------------------------- */  
    class MessageDecoder : public EProtocolDecoder{
    public:
        void decode(sp<EIoSession>& session, EIoBuffer* in, sp<EProtocolDecoderOutput>& out) THROWS(EException);
        void finishDecode(sp<EIoSession>& session, sp<EProtocolDecoderOutput>& out) THROWS(EException);
	    void dispose(sp<EIoSession>& session) THROWS(EException);
    };
/* --------------------------------------------------------------------------------------------------
 *      MessageCodecFactory
 * -------------------------------------------------------------------------------------------------- */  
    class MessageCodecFactory : public EProtocolCodecFactory{
    private:
        EProtocolEncoder *encoder;
        EProtocolDecoder *decoder;
    public:
        MessageCodecFactory();
        EProtocolEncoder* getEncoder(sp<EIoSession>& session) THROWS(EException);
        EProtocolDecoder* getDecoder(sp<EIoSession>& session) THROWS(EException);
    };

}

#endif // !MESSAGE_CODEC_H