/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/* global variable */

int lab2flag=5;
process	main(void)
{

	if(lab2flag == 3){
	//LAB 2.3
	resume(create(lab2q3t1, 1024, 51, "clockmstest", 0, NULL));
	sleepms(6000);
	resume(create(lab2q3t2,1024,52, "cputimetest1",0, NULL));
	sleepms(6000);
	resume(create(lab2q3t3,1024,52, "cputimetest2",0, NULL));
	sleepms(6000);
	resume(create(lab2q3t4,1024,52, "cputimetest3",0, NULL));
	sleepms(3000);
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	}
	else if(lab2flag == 4)
	{
	//LAB 2.4.2
	kprintf("\n -- LAB 2.4.2 --- \n");
	resume(create(lab2q4t1,1024,52, "cputimetest1",0, NULL));
	sleepms(3000);
	resume(create(lab2q4t2,1024,52, "cputimetest2",0, NULL));
	sleepms(3000);
	resume(create(lab2q4t3,1024,52, "cputimetest3",0, NULL));
	sleepms(3000);
	//LAB 2.4.3.1
	/*kprintf("\n -- LAB 2.4.3 --- \n");
	resume(create(iobound, 1024, 1, "iobound 4", 2, 60, 20));
	resume(create(iobound, 1024, 1, "iobound 5", 2, 70, 30));
	resume(create(iobound, 1024, 1, "iobound 6", 2, 80, 40));
	resume(create(cpubound, 1024, 1, "cpubound 4", 2, 1, 75500));
	resume(create(cpubound, 1024, 1, "cpubound 5", 2, 1, 75500));
	resume(create(cpubound, 1024, 1, "cpubound 6", 2, 1, 75500));
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	sleepms(23000);
*/
	}
	else if(lab2flag == 5)
	{
			kprintf("\n -- LAB 2.5 --- \n");
			pid32 a,b,c,d,e,f;
			resume(a=create(cpubound, 1024, 1, "cpubound 1", 2, 1, 75500));
			sleepms(100);
			resume(b=create(cpubound, 1024, 1, "cpubound 2", 2, 1, 75500));
			sleepms(500);
			resume(c=create(cpubound, 1024, 1, "cpubound 3", 2, 1, 75500));
			sleepms(50);
			resume(d=create(cpubound, 1024, 1, "cpubound 4", 2, 1, 75500));
			sleepms(2000);
			resume(e=create(cpubound, 1024, 1, "cpubound 5", 2, 1, 75500));
			sleepms(100);
			resume(f=create(cpubound, 1024, 1, "cpubound 6", 2, 1, 75500));
			struct procent * prptr;
			int counter = 0;
			while(!(prptr = &proctab[a])->prstate == PR_FREE ||!(prptr = &proctab[b])->prstate == PR_FREE ||
		!(prptr = &proctab[c])->prstate == PR_FREE || !(prptr = &proctab[e])->prstate == PR_FREE || !(prptr = &proctab[d])->prstate == PR_FREE || !(prptr = &proctab[f])->prstate == PR_FREE)
			{
				if(counter++ >20000){
					counter =0;
					process_state();
				}
			}
	}
	else{
	kprintf("Must set LAB2FLAG to 3/4 in main.c");
	}
	/* Wait for shell to exit and recreate it */
	return OK;
}
