#include "MessageCodec.h"
#include "Message.h"

namespace Netmodule{
/* --------------------------------------------------------------------------------------------------
 *      MessageEncoder
 * -------------------------------------------------------------------------------------------------- */  
    void MessageEncoder::encode(sp<EIoSession>& session, sp<EObject>& message, sp<EProtocolEncoderOutput>& out) THROWS(EException){
        Message *msg = static_cast<Message*>(message.dismiss());
        out->write(msg->getEncodedMessage());
    }
    void MessageEncoder::dispose(sp<EIoSession>& session) THROWS(EException) {}
/* --------------------------------------------------------------------------------------------------
 *      Messagedecoder
 * -------------------------------------------------------------------------------------------------- */  
    void MessageDecoder::decode(sp<EIoSession>& session, EIoBuffer* in, sp<EProtocolDecoderOutput>& out) THROWS(EException){
        out->write(Message::decodeBytesToMessage(in));
    }
    void MessageDecoder::finishDecode(sp<EIoSession>& session, sp<EProtocolDecoderOutput>& out) THROWS(EException) {}
    void MessageDecoder::dispose(sp<EIoSession>& session) THROWS(EException) {}
/* --------------------------------------------------------------------------------------------------
 *      MessageCodecFactory
 * -------------------------------------------------------------------------------------------------- */  
    MessageCodecFactory::MessageCodecFactory() {
        this->encoder = new MessageEncoder();
        this->decoder = new MessageDecoder();
    }

    EProtocolEncoder* MessageCodecFactory::getEncoder(sp<EIoSession>& session) THROWS(EException){
        return encoder;
    }

    EProtocolDecoder* MessageCodecFactory::getDecoder(sp<EIoSession>& session) THROWS(EException){
        return decoder;
    }

}