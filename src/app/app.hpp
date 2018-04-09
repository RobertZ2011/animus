//
#ifndef ANIMUS_APP

extern "C" {
    Animus::Application *create_animus_application(void);
    void destroy_animus_application(Animus::Application *app);
}

#endif
