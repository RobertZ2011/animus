#ifndef ANIMUS_MESSANGER
#define ANIMUS_MESSANGER

#include "types/types.hpp"
#include "Vector.hpp"
#include "Object.hpp"

namespace Animus {
    class Message_ {
    public:
        typedef uint32_t MessageType;

    protected:
        MessageType type;
    };

    typedef Pointer<Message_> Message;

    class Messanger : public Object {
    public:
        typedef uint32_t MessageType;
        typedef uint32_t ReceiverId;
        typedef Function<void(const Message&)> Receiver;

        Messanger(void) = default;
        ~Messanger(void) = default;

        ReceiverId addReceiver(Message_::MessageType, const Receiver& receiver);
        void remoiveReceiver(ReceiverId id);
        void broadcast(const Message& message);

    private:
        Map<Message_::MessageType, Vector<Receiver>> recivers;
        ReceiverId startId = 1; //meh
    }
}
#endif