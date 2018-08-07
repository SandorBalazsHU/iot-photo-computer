#include "Time.h"
#include <virtuabotixRTC.h>

Time::Time()
{

}

void Time::add_sec(int sec)
{
	if( ( 60 - this->s ) <= sec )
	{
        sec -= 60 - this->s;
        this->s = sec%60;
        if( ( 60 - this->m ) <= ( sec/60 ) + 1 )
        {
            sec -= (60 - this->m)*60;
            this->m = sec/60;
            if(this->h + 1 == 24)
            {
                this->h =0;
            }
            else
            {
                this->h +=1;
            }
        }
        else
        {
            this->m += 1 + (sec/60);
        }

    }
    else
    {
        this->s += sec;
    }

}

void Time::set(virtuabotixRTC time)
{
    time.updateTime();
    this->s = time.seconds;
    this->m = time.minutes;
    this->h = time.hours;
}

double Time::getInt()
{
    return 0.0 + (this->s + (this->m * 100.0) + (this->h * 10000.0));
}
