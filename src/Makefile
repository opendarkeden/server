#----------------------------------------------------------------------
#
# Filename    : Makefile
# Written By  : Reiot
#
#----------------------------------------------------------------------

#----------------------------------------------------------------------
# Directories Setting
#----------------------------------------------------------------------
VSHOME    = ..
BINDIR    = $(VSHOME)/bin
LIBDIR    = $(VSHOME)/lib
LOGDIR    = $(VSHOME)/log
TEMPDIR   = $(VSHOME)/temp

#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
all :
	$(MAKE) -C Core
	$(MAKE) -C server
#	$(MAKE) -C util

allgameserver :
	$(MAKE) -C Core allgameserver
	$(MAKE) -C server allgameserver
#	$(MAKE) -C util

allloginserver :
	$(MAKE) -C Core allloginserver
	$(MAKE) -C server allloginserver
#	$(MAKE) -C util

allsharedserver :
	$(MAKE) -C Core allsharedserver
	$(MAKE) -C server allsharedserver

alltheoneserver :
	$(MAKE) -C Core alltheoneserver
	$(MAKE) -C server alltheoneserver

clean :
	$(MAKE) -C Core clean
	$(MAKE) -C server clean
#$(MAKE) -C util clean

cleanloginserver :
	$(MAKE) -C Core cleanloginserver
	$(MAKE) -C server cleanloginserver
#	$(MAKE) -C util cleanloginserver

cleangameserver :
	$(MAKE) -C Core cleangameserver
	$(MAKE) -C server cleangameserver
#	$(MAKE) -C util cleangameserver

cleanall :
	make cleanbin
	make cleanlib
	make cleanlog
	$(MAKE) -C Core cleanall
	$(MAKE) -C server cleanall
#	$(MAKE) -C util cleanall

depall :
	$(MAKE) -C Core depall
	$(MAKE) -C server depall

cleanbin :
	rm -rf $(BINDIR)/gameserver $(BINDIR)/loginserver $(BINDIR)/gameclient \
			$(BINDIR)/updateserver $(BINDIR)/updateclient

cleanlib :
	rm -rf $(LIBDIR)/*.a $(LIBDIR)/st*

cleanlog :
	rm -rf $(LOGDIR)/*.log 

wc :
	wc `find . -name "*.h" -o -name "*.cpp"`
