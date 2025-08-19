// status.h

#pragma once


enum class Status : int {
    Failure = -1,
    Success = 0,

    InsertionFailure = Failure,
    IndexNotFound = Failure
};