//
// Created by cat on 5/17/17.
//

#include <algorithm>
#include "RandomValue.h"
#include "../Utils/Types.h"

typedef std::list<Lba> AddressList;
#define LOW_ADDRESS_BOUND 5000
#define UP_ADDRESS_BOUND 500000

class LbaGen : RandomValue{
public:
    LbaGen();
    Lba GetRandomValue(StackDist stack_dist);

private:
    /// Current size of using addresses
    ByteSize curr_buffer_size;

    /// Full address list
    AddressList _address_buffer;

    /// \brief Checks if required logical block address
    ///         located in address map
    /// \param address  Logical block address
    /// \return
    bool IsInBuffer(Lba address);

    /// \brief Function moves address from position @pos
    ///         to the beginning of the address map
    /// \param pos Current address position
    void MoveForward(StackDist pos);

    /// \brief
    /// \param address
    void InsertToFront(Lba address);
    ByteSize GetBufferSize();

    /// \brief  Function get first address in map
    /// \return Returns address value
    Lba GetFirst();
};