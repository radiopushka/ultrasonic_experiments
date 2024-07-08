all:
	cc test.c Utransmitter.c alsa/alsa.c -lm -g -lasound
