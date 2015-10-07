//------------------------------------------------------------------------------
// 
//     
//
//------------------------------------------------------------------------------

#ifndef _BARRIER_INCLUDED_
#define _BARRIER_INCLUDED_

#include <atomic>
#include <iostream>

class ThreadBarrier 
{
public:
    ThreadBarrier(unsigned numThread)
        : m_numThread(numThread)
        //, m_arrived(0)
    { m_arrived.store(0);}

    void Wait()
    {
        //m_arrived++;
        //MAY READ FROM UNINITIALIZED ATOMIC
        m_arrived.fetch_add(1);

        while(m_arrived.load() < m_numThread);
    }

private:
    unsigned m_numThread;
    std::atomic<unsigned> m_arrived;
};

#endif //_BARRIER_INCLUDED_
