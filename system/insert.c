/* insert.c - insert */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  insert  -  Insert a process into a queue in descending key order
 *------------------------------------------------------------------------
 */
status	insert(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q,		/* ID of queue to use		*/
	  int32		key		/* Key for the inserted process	*/
	)
{
	int16	curr;			/* Runs through items in a queue*/
	int16	prev;			/* Holds previous node index	*/

	if(isbadpid(pid))
	{
		kprintf("\n Somehting went wrong BAD PID \n");
		return SYSERR;
	}
	if (isbadqid(q)) {
		kprintf("\n Somehting went wrong BAD QID \n");
		return SYSERR;
	}

	curr = firstid(q);

		while (queuetab[curr].qkey >= key) {
				curr = queuetab[curr].qnext;
			}

	/* Insert process between curr node and previous node */

	prev = queuetab[curr].qprev;	/* Get index of previous node	*/
	queuetab[pid].qnext = curr;
	queuetab[pid].qprev = prev;
	queuetab[pid].qkey = key;
	queuetab[prev].qnext = pid;
	queuetab[curr].qprev = pid;
	return OK;
}
