﻿#ifndef EVENTO_EXCEPTION_H
#define EVENTO_EXCEPTION_H

#include <QString>

enum class EventoExceptionCode : int {
    UnexpectedError = -2,
    Uninitialised = -1,
    Ok = 0,
};

template <EventoExceptionCode code = EventoExceptionCode::UnexpectedError>
struct DefaultMessage;

template <>
struct DefaultMessage<EventoExceptionCode::UnexpectedError> {
    static constexpr char msg[] = "Unexpected Error Encountered!";
};

template <>
struct DefaultMessage<EventoExceptionCode::Uninitialised> {
    static constexpr char msg[] = "Uninitialised or Moved!";
};

template <>
struct DefaultMessage<EventoExceptionCode::Ok> {
    static constexpr char msg[] = "No Error!";
};

class alignas(32) EventoException {
private:
    alignas(8) EventoExceptionCode m_code;
    alignas(8) QString m_message;

public:
    EventoException(EventoExceptionCode code = EventoExceptionCode::Ok, const QString& msg = DefaultMessage<EventoExceptionCode::Ok>::msg) : m_code(code), m_message(msg) {}
    EventoException(const EventoException&) = default;

    inline QString message() {
        return *this ? m_message : QStringLiteral("No Error!");
    }
    inline EventoExceptionCode code() { return m_code; }

    inline operator bool() {
        return m_code != EventoExceptionCode::Ok;
    }
};

#endif
