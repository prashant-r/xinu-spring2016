/* send.c - send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  sendbt  -  Pass a message to a process and start recipient if waiting
 *  		   block on timer specified in arguments as maxwait upper bound.
 *------------------------------------------------------------------------
 */
syscall	sendbt(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg,		/* Contents of message		*/
	  int32 maxwait /* upper bound on blocking wait time */
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	struct  procent *prsmgptr; /* Ptr to sending messsage process */

	mask = disable();

	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	prsmgptr = &proctab[currpid];
	if ((prptr->prstate == PR_FREE) || maxwait <0) {
		restore(mask);
		return SYSERR;
	}
	// receiver's send buffer is full
	if(prptr->prhasmsg)
	{
		prsmgptr->sndmsg = msg;
		prsmgptr->sndflag = TRUE;
		// if dealing with maxwait =0 then continue to normal blocking
		// algorithm that won't wake up due to clock timer.
		if(maxwait > 0)
			if (insertd(currpid,sleepq,maxwait) == SYSERR)
			{
					restore(mask);
					return SYSERR;
			}
		myenqueue(currpid, prptr->senderq);
		prsmgptr->prstate = PR_SEND;
		resched();
		if(prptr->prhasmsg)// receiver's send buffer is still full so must have woken up by sleep
		{
			if(maxwait > 0) // check is not necessary but do it anyway
			{
				kprintf(" Send request timed out must drop message for %d \n", currpid);
				// send request timed out must drop the message
				mygetitem(currpid);
				prsmgptr->sndflag = FALSE;
				restore(mask);
				return TIMEOUT;
			}
		}
		else
		{
			kprintf(" Request buffer cleared up for %d ! \n", currpid);
		}
	}
	// receiver's send buffer is empty
	prptr->prmsg = msg;		/* Deliver message		*/
	prptr->prhasmsg = TRUE;		/* Indicate message is waiting	*/

	/* If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECV) {
		ready(pid);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid);
	}
	restore(mask);		/* Restore interrupts */
	return OK;
}
