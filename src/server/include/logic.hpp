/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** logic.hpp
*/

#ifndef LOGIC_HPP_
    #define LOGIC_HPP_

    #include <vector>
    #include <string>

    #include "entry.hpp"
    #include "connection.hpp"

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

