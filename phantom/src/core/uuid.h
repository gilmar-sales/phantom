//
// Created by gilma on 31/03/2022.
//

#ifndef PHANTOM_ENGINE_UUID_H
#define PHANTOM_ENGINE_UUID_H

PH_NAMESPACE_BEGIN

class UUID {

public:
    UUID();
    UUID(ulong uuid);
    UUID(const UUID& other);

    operator ulong () { return m_UUID; }
    operator const ulong () const { return m_UUID; }
private:
    ulong m_UUID;
};

PH_NAMESPACE_END

#endif //PHANTOM_ENGINE_UUID_H
