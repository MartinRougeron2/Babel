/*
** EPITECH PROJECT, 2019
** logic.hpp
** File description:
** logic
*/

#ifndef LOGIC_HPP_
    #define LOGIC_HPP_

    // # Lib Imports

    #include <vector>
    #include <string>

    // # Local Imports

    #include "entity.hpp"
    #include "c_handler.hpp"

    enum logicEnum {
        Welcome = 0,
        Connect,
        SuccessConnect,
        FailConnect,
        Call,
        AcceptCall,
        HangUp,
        PendingRequest,
        PendingSuccess,
        PendingFail,
        PendingInfo,
        AcceptPending,
        RefusePending,
        AddContact
    };


#endif /* !LOGIC_HPP_ */

