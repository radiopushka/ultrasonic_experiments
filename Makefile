all:
	cc iface.c Utransmitter.c alsa/alsa.c -lm -lasound -o utx
