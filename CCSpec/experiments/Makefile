all: chaselev cliffc hwqueue iqueue kfIFO msqueue priority treiber

chaselev: 
	$(MAKE) -C chase-lev-deque-bugfix

cliffc: 
	$(MAKE) -C cliffc-hashtable

hwqueue:
	$(MAKE) -C HWQueue

iqueue:
	$(MAKE) -C IQueue

kfIFO:
	$(MAKE) -C kFIFO

msqueue:
	$(MAKE) -C ms-queue

priority:
	$(MAKE) -C priority-queue

treiber:
	$(MAKE) -C treiber-stack

PHONY += clean
clean:
	$(MAKE) -C chase-lev-deque-bugfix clean
	$(MAKE) -C cliffc-hashtable clean
	$(MAKE) -C HWQueue clean
	$(MAKE) -C IQueue clean
	$(MAKE) -C kFIFO clean
	$(MAKE) -C ms-queue clean
	$(MAKE) -C priority-queue clean
	$(MAKE) -C treiber-stack clean
