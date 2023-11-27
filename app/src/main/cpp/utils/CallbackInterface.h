//
// Created by harjai on 27-Nov-23.
//

#ifndef NATIVEBOOKSTORE_CALLBACKINTERFACE_H
#define NATIVEBOOKSTORE_CALLBACKINTERFACE_H

class CallbackInterface {
public:
    virtual void onCallbackSuccess(char *message) = 0;

    virtual void onCallbackFailure(char *message) = 0;
};


#endif //NATIVEBOOKSTORE_CALLBACKINTERFACE_H
